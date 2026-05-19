# -*- coding: utf-8 -*-

import numpy as np
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
# 2. ARQUITECTURA (El estándar de la industria)
# ==========================================
model = Sequential([
    # Capa Oculta: ReLU para aprender rápido. Subimos a 8 neuronas para darle más capacidad.
    Dense(8, activation='relu', input_shape=(2,)),
    
    # Capa de Salida: Sigmoide estricto para obtener probabilidades (0 al 1)
    Dense(1, activation='sigmoid')
])

# ==========================================
# 3. COMPILACIÓN
# ==========================================
# Usamos Adam (mejor que SGD) y binary_crossentropy (mejor que MSE para clasificación)
model.compile(optimizer=Adam(learning_rate=0.05), 
              loss='binary_crossentropy',
              metrics=['binary_accuracy'])

# ==========================================
# 4. ENTRENAMIENTO
# ==========================================
print("[INFO] Entrenando el modelo...")
# Gracias a las optimizaciones, converge en muchas menos épocas (500 en lugar de 5000)
model.fit(X, T, epochs=500, verbose=0)

# ==========================================
# 5. INFERENCIA Y UMBRAL (Thresholding)
# ==========================================
print("\n[INFO] Entrenamiento finalizado. Predicciones:")

# Hacemos el Forward Pass final
probabilidades = model.predict(X)

for i in range(4):
    prob = probabilidades[i][0]
    
    # Aplicamos la regla lógica: Si es >= 50%, es clase 1, si no, es clase 0
    clase_final = 1 if prob >= 0.5 else 0
    
    print(f"Entrada: {X[i]} -> Target: {T[i][0]} | Prob: {prob:.4f} | Prediccion Final: {clase_final}")