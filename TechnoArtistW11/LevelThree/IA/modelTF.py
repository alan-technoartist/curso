import numpy as np
import tensorflow as tf
import tf2onnx
import subprocess, sys
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense, Flatten, Conv2D, MaxPooling2D
from tensorflow.keras.optimizers import Adam

print("[INFO] Construyendo modelo MNIST (CNN simple)...")

# ==========================================
# 1. DATOS (MNIST viene con Keras)
# ==========================================
(X_train, y_train), (X_test, y_test) = tf.keras.datasets.mnist.load_data()

# Normalizar pixeles a [0, 1] y agregar canal (28,28) -> (28,28,1)
X_train = X_train.astype(np.float32)[..., np.newaxis] / 255.0
X_test  = X_test.astype(np.float32)[..., np.newaxis]  / 255.0

# ==========================================
# 2. ARQUITECTURA
# ==========================================
model = Sequential([
    Conv2D(8, kernel_size=3, activation='relu', input_shape=(28, 28, 1)),
    MaxPooling2D(pool_size=2),
    Conv2D(16, kernel_size=3, activation='relu'),
    MaxPooling2D(pool_size=2),
    Flatten(),
    Dense(32, activation='relu'),
    Dense(10, activation='softmax'),   # 10 clases, no 1
])

# ==========================================
# 3. COMPILACION
# ==========================================
model.compile(
    optimizer = Adam(learning_rate=1e-3),
    loss      = 'sparse_categorical_crossentropy',
    metrics   = ['accuracy'],
)

# ==========================================
# 4. ENTRENAMIENTO
# ==========================================
print("[INFO] Entrenando...")
model.fit(X_train, y_train, epochs=5, batch_size=128,
          validation_split=0.1, verbose=1)

#loss, acc = model.evaluate(X_test, y_test, verbose=0)
#print(f"[INFO] Test accuracy: {acc:.4f}")

# ==========================================
# 5. INFERENCIA DE EJEMPLO
# ==========================================
probs = model.predict(X_test[:5], verbose=0)

for i in range(5):
    pred = np.argmax(probs[i])
    print(f"Real: {y_test[i]}  Prediccion: {pred}  "
          f"Confianza: {probs[i][pred]:.4f}")

# ==========================================
# 6. EXPORTACION A ONNX (identico a XOR)
# ==========================================
print("[INFO] Exportando a SavedModel...")
model.export("modelo_mnist_sm")

print("[INFO] Convirtiendo a ONNX...")
subprocess.run([
    sys.executable, "-m", "tf2onnx.convert",
    "--saved-model", "modelo_mnist_sm",
    "--output", "modelo_mnist.onnx",
    "--opset", "17",
], check=True)
print("[INFO] Modelo ONNX guardado en modelo_mnist.onnx")