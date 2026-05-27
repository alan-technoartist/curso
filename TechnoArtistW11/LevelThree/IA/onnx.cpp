#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <thread>
#include <filesystem>

// Cabecera principal de ONNX Runtime (Instalada vía NuGet)
#include <onnxruntime_cxx_api.h>

void procesarBMP(std::ifstream& archivo, std::vector<float>& input_data) {
    // El formato BMP guarda en el byte 10 un número (entero de 4 bytes) 
    // que indica exactamente dónde empiezan los píxeles.
    uint32_t offset_pixeles;
    archivo.seekg(10, std::ios::beg);
    archivo.read(reinterpret_cast<char*>(&offset_pixeles), sizeof(offset_pixeles));

    // Saltamos exactamente hasta donde empiezan los datos visuales
    archivo.seekg(offset_pixeles, std::ios::beg);

    std::vector<unsigned char> pixeles_crudos(28 * 28 * 3);
    archivo.read(reinterpret_cast<char*>(pixeles_crudos.data()), pixeles_crudos.size());
    archivo.close();

    // =================================================================
    // 3. PREPROCESAMIENTO Y NORMALIZACIÓN MATEMÁTICA EN C++
    // =================================================================
    //std::vector<float> input_data(784); // 28 * 28 = 784 entradas

    for (int y = 0; y < 28; ++y) {
        for (int x = 0; x < 28; ++x) {
            // Los archivos BMP se guardan de abajo hacia arriba; invertimos el eje Y
            int y_invertido = 27 - y;

            // Cada píxel ocupa 3 bytes (B, G, R). Saltamos de 3 en 3.
            int indice_bmp = (y_invertido * 28 + x) * 3;

            // Extraemos un canal (como es blanco y negro, B, G y R valen lo mismo)
            unsigned char valor_pixel = pixeles_crudos[indice_bmp];

            // NORMALIZACIÓN: Pasamos el byte (0 a 255) a flotante (0.0 a 1.0)
            float pixel_normalizado = valor_pixel / 255.0f;

            // Inversion de color (opcional)
            input_data[y * 28 + x] = 1.0f - pixel_normalizado;
        }
    }
    std::cout << "[INFO] Imagen BMP procesada, invertida y normalizada correctamente." << std::endl;
}

void testONNX() {
    std::cout << "[INFO] Iniciando Aplicacion MNIST (C++ Puro + ONNX Runtime)..." << std::endl;

    std::string archivo_bmp = "digito3.bmp";
    std::string archivo_onnx = "modelo_mnist.onnx";

    // =================================================================
    // 2. LECTURA INTELIGENTE DEL ARCHIVO BMP
    // =================================================================
    std::ifstream archivo(archivo_bmp, std::ios::binary);
    std::vector<float> input_data(784); // 28 * 28 = 784 entradas

    procesarBMP(archivo, input_data);

    // =================================================================
    // 4. INICIALIZACIÓN DE ONNX RUNTIME
    // =================================================================
    Ort::Env env(ORT_LOGGING_LEVEL_WARNING, "ModeloMNIST");
    Ort::SessionOptions session_options;
    std::unique_ptr<Ort::Session> session;

    // Configuración para soportar rutas en Windows
    std::wstring model_path_w(archivo_onnx.begin(), archivo_onnx.end());
    const wchar_t* model_path = model_path_w.c_str();

    session = std::make_unique<Ort::Session>(env, model_path, session_options);

    // =================================================================
    // 5. PREPARACIÓN DE TENSORES DINÁMICOS
    // =================================================================
    Ort::AllocatorWithDefaultOptions allocator;
    Ort::AllocatedStringPtr input_name_ptr = session->GetInputNameAllocated(0, allocator);
    Ort::AllocatedStringPtr output_name_ptr = session->GetOutputNameAllocated(0, allocator);
    const char* input_names[] = { input_name_ptr.get() };
    const char* output_names[] = { output_name_ptr.get() };

    std::vector<int64_t> input_shape = { 1, 28, 28, 1 }; // forma del tensor de entrada (num imagenes, tamano, canales)

    // Vinculamos el tensor de ONNX directamente a nuestro vector 'input_data' (cero copias)
    auto memory_info = Ort::MemoryInfo::CreateCpu(OrtArenaAllocator, OrtMemTypeDefault);

    Ort::Value input_tensor = Ort::Value::CreateTensor<float>(
        memory_info, input_data.data(), input_data.size(), input_shape.data(), input_shape.size());

    // =================================================================
    // 6. EJECUCIÓN DE LA INFERENCIA (FORWARD PASS)
    // =================================================================
    std::cout << "[INFO] Evaluando la imagen en la red neuronal..." << std::endl;
    std::vector<Ort::Value> output_tensors;

    output_tensors = session->Run(
        Ort::RunOptions{ nullptr }, input_names, &input_tensor, 1, output_names, 1);


    // =================================================================
    // 7. EXTRACCIÓN DE RESULTADOS (ARGMAX)
    // =================================================================
    float* output_data = output_tensors.front().GetTensorMutableData<float>();

    // Buscamos cuál de las 10 neuronas de salida tiene la probabilidad más alta
    int digito_predicho = 0;
    float prob_maxima = output_data[0];

    for (int i = 1; i < 10; ++i) {
        if (output_data[i] > prob_maxima) {
            prob_maxima = output_data[i];
            digito_predicho = i;
        }
    }

    // =================================================================
    // 8. IMPRESIÓN DEL RESULTADO FINAL
    // =================================================================
    std::cout << "\n=========================================" << std::endl;
    std::cout << "          RESULTADO DE LA INFERENCIA      " << std::endl;
    std::cout << "=========================================" << std::endl;
    std::cout << " Archivo evaluado: " << archivo_bmp << std::endl;
    std::cout << " Prediccion Final: ¡Es un " << digito_predicho << "!" << std::endl;
    std::cout << " Probabilidad de certeza: " << (prob_maxima * 100.0f) << "%" << std::endl;
    std::cout << "=========================================\n" << std::endl;

    return;
}