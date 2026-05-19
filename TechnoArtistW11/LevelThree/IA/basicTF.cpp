#include <iostream>
#include <vector>
#include <tensorflow/cc/client/client_session.h>
#include <tensorflow/cc/ops/standard_ops.h>
#include <tensorflow/core/framework/tensor.h>

using namespace tensorflow;
using namespace tensorflow::ops;

void testMLP() {
    std::cout << "[INFO] Construyendo Perceptron Multicapa (1 Capa Oculta)..." << std::endl;
    Scope root = Scope::NewRootScope();

    // ==========================================
    // 1. FORWARD PASS
    // ==========================================
    // Entradas y Targets (Lote de 4 ejemplos)
    auto X = Placeholder(root, DT_FLOAT, Placeholder::Shape({4, 2}));
    auto T = Placeholder(root, DT_FLOAT, Placeholder::Shape({4, 1}));

    // --- CAPA OCULTA (2 Neuronas) ---
    auto W1 = Variable(root, {2, 2}, DT_FLOAT);
    auto b1 = Variable(root, {1, 2}, DT_FLOAT); // Vector fila para broadcasting
    auto assign_W1 = Assign(root, W1, RandomNormal(root, {2, 2}, DT_FLOAT));
    auto assign_b1 = Assign(root, b1, Const(root, 0.0f, {1, 2}));

    // H = Sigmoid(X * W1 + b1)
    auto H_logits = Add(root, MatMul(root, X, W1), b1);
    auto H = Sigmoid(root, H_logits);

    // --- CAPA DE SALIDA (1 Neurona) ---
    auto W2 = Variable(root, {2, 1}, DT_FLOAT);
    auto b2 = Variable(root, {1, 1}, DT_FLOAT);
    auto assign_W2 = Assign(root, W2, RandomNormal(root, {2, 1}, DT_FLOAT));
    auto assign_b2 = Assign(root, b2, Const(root, 0.0f, {1, 1}));

    // Y = Sigmoid(H * W2 + b2)
    auto Y_logits = Add(root, MatMul(root, H, W2), b2);
    auto Y = Sigmoid(root, Y_logits);

    // ==========================================
    // 2. BACKWARD PASS (Calculo Manual de Gradientes)
    // ==========================================
    auto const_one = Const(root, 1.0f);
    auto perm_trans = Const(root, {1, 0}); // Para transponer matrices 2D

    // --- Gradientes de la Capa de Salida ---
    auto error_Y = Sub(root, Y, T);
    auto deriv_Y = Mul(root, Y, Sub(root, const_one, Y));
    auto delta_2 = Mul(root, error_Y, deriv_Y); // delta_2 = (Y-T) * Y*(1-Y)

    auto H_T = Transpose(root, H, perm_trans);
    auto grad_W2 = MatMul(root, H_T, delta_2);
    auto grad_b2 = ReduceSum(root, delta_2, Const(root, {0})); // Suma sobre el eje de ejemplos

    // --- Gradientes de la Capa Oculta ---
    auto W2_T = Transpose(root, W2, perm_trans);
    auto error_H = MatMul(root, delta_2, W2_T); // Propagar el error hacia atrás
    auto deriv_H = Mul(root, H, Sub(root, const_one, H));
    auto delta_1 = Mul(root, error_H, deriv_H);

    auto X_T = Transpose(root, X, perm_trans);
    auto grad_W1 = MatMul(root, X_T, delta_1);
    auto grad_b1 = ReduceSum(root, delta_1, Const(root, {0}));

    // ==========================================
    // 3. OPTIMIZADOR (Descenso del Gradiente)
    // ==========================================
    // Aumentamos un poco la tasa de aprendizaje para XOR
    auto alpha = Const(root, 0.5f); 
    
    auto update_W2 = AssignSub(root, W2, Mul(root, alpha, grad_W2));
    auto update_b2 = AssignSub(root, b2, Mul(root, alpha, grad_b2));
    auto update_W1 = AssignSub(root, W1, Mul(root, alpha, grad_W1));
    auto update_b1 = AssignSub(root, b1, Mul(root, alpha, grad_b1));

    // ==========================================
    // 4. EJECUCIÓN (Datos y Bucle)
    // ==========================================
    ClientSession session(root);
    TF_CHECK_OK(session.Run({assign_W1, assign_b1, assign_W2, assign_b2}, nullptr));

    // Datos XOR (OR Exclusivo: salida 1 solo si las entradas son diferentes)
    Tensor x_data(DT_FLOAT, TensorShape({4, 2}));
    x_data.matrix<float>()(0, 0) = 0.0f; x_data.matrix<float>()(0, 1) = 0.0f;
    x_data.matrix<float>()(1, 0) = 0.0f; x_data.matrix<float>()(1, 1) = 1.0f;
    x_data.matrix<float>()(2, 0) = 1.0f; x_data.matrix<float>()(2, 1) = 0.0f;
    x_data.matrix<float>()(3, 0) = 1.0f; x_data.matrix<float>()(3, 1) = 1.0f;

    Tensor t_data(DT_FLOAT, TensorShape({4, 1}));
    t_data.matrix<float>()(0, 0) = 0.0f; // 0 XOR 0 = 0
    t_data.matrix<float>()(1, 0) = 1.0f; // 0 XOR 1 = 1
    t_data.matrix<float>()(2, 0) = 1.0f; // 1 XOR 0 = 1
    t_data.matrix<float>()(3, 0) = 0.0f; // 1 XOR 1 = 0

    std::cout << "[INFO] Iniciando entrenamiento (5000 epocas)..." << std::endl;

    for (int epoch = 0; epoch <= 5000; ++epoch) {
        std::vector<Tensor> outputs;
        
        // Ejecutamos las 4 actualizaciones y pedimos el error de la capa final
        TF_CHECK_OK(session.Run(
            {{X, x_data}, {T, t_data}}, 
            {update_W1, update_b1, update_W2, update_b2, error_Y}, 
            &outputs
        ));

    }

    // ==========================================
    // 5. EVALUACIÓN (Prueba Final)
    // ==========================================
    std::vector<Tensor> final_predictions;
    TF_CHECK_OK(session.Run({{X, x_data}}, {Y}, &final_predictions));

    std::cout << "\n[INFO] Evaluacion final del modelo XOR:" << std::endl;
    auto preds = final_predictions[0].matrix<float>();
    for (int i = 0; i < 4; ++i) {
        std::cout << "Entrada: [" << x_data.matrix<float>()(i,0) << ", " << x_data.matrix<float>()(i,1) 
                  << "] -> Target: " << t_data.matrix<float>()(i,0) 
                  << " | Prediccion: " << preds(i, 0) << std::endl;
    }

}

void testPerceptron() {
    std::cout << "[INFO] Construyendo el Grafo del Perceptron..." << std::endl;

    Scope root = Scope::NewRootScope();

    // ==========================================
    // 1. FORWARD PASS (Inferencias)
    // ==========================================
    auto X = Placeholder(root, DT_FLOAT, Placeholder::Shape({ 4, 2 })); // 4 ejemplos, 2 características
    auto T = Placeholder(root, DT_FLOAT, Placeholder::Shape({ 4, 1 })); // 4 etiquetas/targets

    auto W = Variable(root, { 2, 1 }, DT_FLOAT);
    auto b = Variable(root, { 1 }, DT_FLOAT);

    auto assign_W = Assign(root, W, RandomNormal(root, { 2, 1 }, DT_FLOAT));
    auto assign_b = Assign(root, b, Const(root, 0.0f, { 1 }));

    auto matmul = MatMul(root, X, W);
    auto add_bias = Add(root, matmul, b);
    auto Y = Sigmoid(root, add_bias); // Predicción

    // ==========================================
    // 2. BACKWARD PASS (Cálculo de Gradientes)
    // ==========================================
    // Error = Y - T
    auto error = Sub(root, Y, T);

    // Derivada = Y * (1 - Y)
    auto one_minus_Y = Sub(root, Const(root, 1.0f), Y);
    auto derivative = Mul(root, Y, one_minus_Y);

    // Delta = Error * Derivada
    auto delta = Mul(root, error, derivative);

    // X_T = Transpuesta de X
    auto perm = Const(root, { 1, 0 }); // Permutar dimensiones 0 y 1
    auto X_T = Transpose(root, X, perm);

    // Gradientes: grad_W = X_T * Delta  |  grad_b = Suma(Delta)
    auto grad_W = MatMul(root, X_T, delta);
    auto grad_b = ReduceSum(root, delta, Const(root, { 0 })); // Suma sobre el eje 0 (lote)

    // ==========================================
    // 3. OPTIMIZADOR (Descenso del Gradiente)
    // ==========================================
    auto alpha = Const(root, 0.5f); // Tasa de aprendizaje (Learning Rate)

    // Actualización: W = W - (alpha * grad_W)
    auto update_W = AssignSub(root, W, Mul(root, alpha, grad_W));
    auto update_b = AssignSub(root, b, Mul(root, alpha, grad_b));

    // ==========================================
    // 4. EJECUCIÓN DEL ENTRENAMIENTO
    // ==========================================
    ClientSession session(root);

    // Inicializar variables
    TF_CHECK_OK(session.Run({ assign_W, assign_b }, nullptr));

    // Datos de Entrenamiento (Compuerta Lógica OR)
    Tensor x_data(DT_FLOAT, TensorShape({ 4, 2 }));
    x_data.matrix<float>()(0, 0) = 0.0f; x_data.matrix<float>()(0, 1) = 0.0f;
    x_data.matrix<float>()(1, 0) = 0.0f; x_data.matrix<float>()(1, 1) = 1.0f;
    x_data.matrix<float>()(2, 0) = 1.0f; x_data.matrix<float>()(2, 1) = 0.0f;
    x_data.matrix<float>()(3, 0) = 1.0f; x_data.matrix<float>()(3, 1) = 1.0f;

    Tensor t_data(DT_FLOAT, TensorShape({ 4, 1 }));
    t_data.matrix<float>()(0, 0) = 0.0f; // 0 OR 0 = 0
    t_data.matrix<float>()(1, 0) = 1.0f; // 0 OR 1 = 1
    t_data.matrix<float>()(2, 0) = 1.0f; // 1 OR 0 = 1
    t_data.matrix<float>()(3, 0) = 1.0f; // 1 OR 1 = 1

    std::cout << "[INFO] Iniciando entrenamiento (1000 epocas)...\n" << std::endl;

    for (int epoch = 0; epoch <= 1000; ++epoch) {
        std::vector<Tensor> outputs;
        // Ejecutamos las operaciones de actualización y pedimos el error
        TF_CHECK_OK(session.Run({ {X, x_data}, {T, t_data} }, { update_W, update_b, error }, &outputs));

    }

    // ==========================================
    // 5. EVALUACIÓN (Test)
    // ==========================================
    std::vector<Tensor> final_predictions;
    TF_CHECK_OK(session.Run({ {X, x_data} }, { Y }, &final_predictions));

    std::cout << "\n[INFO] Entrenamiento finalizado. Predicciones finales:" << std::endl;
    auto preds = final_predictions[0].matrix<float>();
    for (int i = 0; i < 4; ++i) {
        std::cout << "Entrada: [" << x_data.matrix<float>()(i, 0) << ", " << x_data.matrix<float>()(i, 1)
            << "] -> Target: " << t_data.matrix<float>()(i, 0)
            << " | Prediccion: " << preds(i, 0) << std::endl;
    }

}