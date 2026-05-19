import numpy as np
import tensorflow as tf
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense

# ==========================================
# 1. DATOS DE ENTRENAMIENTO
# ==========================================
# En la industria solemos usar NumPy para manejar los datos crudos
X = np.array([[0, 0], 
              [0, 1], 
              [1, 0], 
              [1, 1]], dtype=np.float32)

T = np.array([[0], 
              [1], 
              [1], 
              [0]], dtype=np.float32)

# ==========================================
# 2. CONSTRUCCIÓN DEL MODELO (Arquitectura)
# ==========================================
# Sequential nos permite apilar capas fácilmente
model = Sequential([
    # Capa oculta: 2 neuronas, activación sigmoide, y definimos la forma de entrada
    Dense(2, activation='sigmoid', input_shape=(2,)),
    
    # Capa de salida: 1 neurona, activación sigmoide
    Dense(1, activation='sigmoid')
])

# ==========================================
# 3. COMPILACIÓN (El motor de la red)
# ==========================================
# Aquí le decimos CÓMO va a aprender. 
# Reemplaza todas nuestras derivadas y actualizaciones manuales.
model.compile(optimizer=tf.keras.optimizers.SGD(learning_rate=0.5), 
              loss='mean_squared_error',
              metrics=['binary_accuracy'])

# ==========================================
# 4. ENTRENAMIENTO
# ==========================================
print("[INFO] Entrenando el modelo...")
# model.fit hace TODO el ciclo: forward pass, backward pass y actualización de pesos.
# verbose=0 silencia la salida para no inundar la consola con 5000 líneas.
model.fit(X, T, epochs=5000, verbose=0)

# ==========================================
# 5. PREDICCIÓN / EVALUACIÓN
# ==========================================
print("\n[INFO] Entrenamiento finalizado. Predicciones:")
predicciones = model.predict(X)

for i in range(4):
    print(f"Entrada: {X[i]} -> Target: {T[i][0]} | Prediccion: {predicciones[i][0]:.4f}")