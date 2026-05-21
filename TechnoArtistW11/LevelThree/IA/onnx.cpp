#include <iostream>
#include <vector>
#include <thread>

// Cabecera principal de ONNX Runtime para C++
#include <onnxruntime_cxx_api.h>

void testONNX() {
    std::cout << "[INFO] Iniciando Inferencia con ONNX Runtime en C++..." << std::endl;

    // 1. Inicializar el entorno (Controla el registro de errores y telemetría)
    Ort::Env env(ORT_LOGGING_LEVEL_WARNING, "ModeloXOR");
    Ort::SessionOptions session_options;

    // 2. Cargar el modelo .onnx
    // IMPORTANTE: En Windows, ONNX Runtime espera arreglos de caracteres anchos (wchar_t / L"")
    const wchar_t* model_path = L"modelo_xor.onnx";

    Ort::Session session(env, model_path, session_options);

    // 3. Obtener dinámicamente los nombres de entrada y salida
    // (A diferencia de LiteRT, ONNX requiere saber cómo se llaman los nodos internamente)
    Ort::AllocatorWithDefaultOptions allocator;

    Ort::AllocatedStringPtr input_name_ptr = session.GetInputNameAllocated(0, allocator);
    Ort::AllocatedStringPtr output_name_ptr = session.GetOutputNameAllocated(0, allocator);

    const char* input_names[] = { input_name_ptr.get() };
    const char* output_names[] = { output_name_ptr.get() };

    // 4. Preparar los datos de entrada (Probaremos XOR con [1.0, 0.0])
    std::vector<float> input_data = { 1.0f, 0.0f };
    std::vector<int64_t> input_shape = { 1, 2 }; // Lote de 1 ejemplo, 2 características

    // 5. Crear el Tensor de ONNX apuntando directamente a nuestra memoria en C++
    auto memory_info = Ort::MemoryInfo::CreateCpu(OrtArenaAllocator, OrtMemTypeDefault);
    Ort::Value input_tensor = Ort::Value::CreateTensor<float>(
        memory_info, input_data.data(), input_data.size(), input_shape.data(), input_shape.size());

    // 6. EJECUTAR LA INFERENCIA (Forward Pass)
    std::cout << "[INFO] Ejecutando el modelo..." << std::endl;
    auto output_tensors = session.Run(
        Ort::RunOptions{ nullptr },
        input_names,
        &input_tensor,
        1,
        output_names,
        1
    );

    // 7. Leer los resultados del Tensor de Salida
    float* output_data = output_tensors.front().GetTensorMutableData<float>();
    float probabilidad = output_data[0];

    // Aplicamos el umbral (Threshold)
    int clase_final = (probabilidad >= 0.5f) ? 1 : 0;

    // Mostrar el resultado
    std::cout << "-----------------------------------" << std::endl;
    std::cout << "Entrada: [1.0, 0.0]" << std::endl;
    std::cout << "Probabilidad (Cruda): " << probabilidad << std::endl;
    std::cout << "Predicción Lógica: " << clase_final << std::endl;
    std::cout << "-----------------------------------" << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(10));
}