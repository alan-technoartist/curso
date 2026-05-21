import numpy as np
import subprocess, sys
import tensorflow as tf
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense
from tensorflow.keras.optimizers import Adam

print("[INFO] Construyendo modelo optimizado (ReLU + Adam + Keras)...")

# ==========================================
# 1. DATOS DE ENTRENAMIENTO (XOR)
# ==========================================
X = np.array([[0, 0], 
              [0, 1], 
              [1, 0], 
              [1, 1]], dtype=np.float32)

T = np.array([[0], 
              [1], 
              [1], 
              [0]], dtype=np.float32)

# ==========================================
# 2. ARQUITECTURA (El estandar de la industria)
# ==========================================
model = Sequential([
    # Capa Oculta: ReLU para aprender rapido. Subimos a 8 neuronas para darle mas capacidad.
    Dense(8, activation='relu', input_shape=(2,)),
    
    # Capa de Salida: Sigmoide estricto para obtener probabilidades (0 al 1)
    Dense(1, activation='sigmoid')
])

# ==========================================
# 3. COMPILACIoN
# ==========================================
# Usamos Adam (mejor que SGD) y binary_crossentropy (mejor que MSE para clasificacion)
model.compile(optimizer=Adam(learning_rate=0.05), 
              loss='binary_crossentropy',
              metrics=['binary_accuracy'])

# ==========================================
# 4. ENTRENAMIENTO
# ==========================================
print("[INFO] Entrenando el modelo...")
# Gracias a las optimizaciones, converge en muchas menos apocas (500 en lugar de 5000)
model.fit(X, T, epochs=300, verbose=0)

# ==========================================
# 5. INFERENCIA Y UMBRAL (Thresholding)
# ==========================================
print("\n[INFO] Entrenamiento finalizado. Predicciones:")

# Hacemos el Forward Pass final
probabilidades = model.predict(X)

for i in range(4):
    prob = probabilidades[i][0]
    
    # Aplicamos la regla logica: Si es >= 50%, es clase 1, si no, es clase 0
    clase_final = 1 if prob >= 0.5 else 0
    
    print(f"Entrada: {X[i]} -> Target: {T[i][0]} | Prob: {prob:.4f} | Prediccion Final: {clase_final}")


print("[INFO] Convirtiendo el modelo a formato LiteRT (.tflite)...")

# 1. Crear el convertidor usando tu modelo de Keras
converter = tf.lite.TFLiteConverter.from_keras_model(model)

# 2. (Opcional pero recomendado) Optimizar el modelo para que sea mas rapido
converter.optimizations = [tf.lite.Optimize.DEFAULT]

# 3. Realizar la conversion
tflite_model = converter.convert()

# 4. Guardar el archivo binario
with open("modelo_xor.tflite", "wb") as f:
    f.write(tflite_model)

# 5. Exportar a formato savedmodel
print("[INFO] Exportando a SavedModel...")
model.export("modelo_xor_sm")

# 6. Convertir a ONNX
print("[INFO] Convirtiendo SavedModel a ONNX...")
subprocess.run([
    sys.executable, "-m", "tf2onnx.convert",
    "--saved-model", "modelo_xor_sm",
    "--output", "modelo_xor.onnx"
], check=True)

print("[INFO] Modelo ONNX guardado en modelo_xor.onnx")