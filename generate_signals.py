import os
import numpy as np

def save_signal(prefix, a, b):
    np.savetxt(f"sinais/{prefix}_a.txt", a, fmt="%.6f")
    np.savetxt(f"sinais/{prefix}_b.txt", b, fmt="%.6f")
    with open("sinais/index.txt", "a") as f:
        f.write(f"{prefix}\n")

def main():
    os.makedirs("sinais", exist_ok=True)
    if os.path.exists("sinais/index.txt"):
        os.remove("sinais/index.txt")

    size = 1000

    a, b = np.zeros(size), np.zeros(size)
    a[500] = 1.0; b[550] = 1.0
    save_signal("test1_impulso_a", a, b)

    a, b = np.zeros(size), np.zeros(size)
    a[550] = 1.0; b[500] = 1.0
    save_signal("test1_impulso_b", a, b)

    a, b = np.zeros(size), np.zeros(size)
    a[500] = 1.0; b[500] = 1.0
    save_signal("test1_impulso_c", a, b)

    a, b = np.ones(size), np.ones(size)
    save_signal("test2_constantes", a, b)

    a, b = np.zeros(size), np.zeros(size)
    a[0] = 1.0; b[size - 1] = 1.0
    save_signal("test3_bordas_a", a, b)

    a, b = np.zeros(size), np.zeros(size)
    a[size - 1] = 1.0; b[0] = 1.0
    save_signal("test3_bordas_b", a, b)

    a, b = np.zeros(size), np.zeros(size)
    a[size // 2:] = 1.0
    b[size // 4:] = 1.0
    save_signal("test4_degrau", a, b)

    idx = np.arange(size)
    a = np.exp(-0.01 * idx)
    b = np.exp(-0.02 * idx)
    save_signal("test5_exponencial", a, b)

    for i in range(20):
        t = np.linspace(0, 10, size)
        freq1 = (i % 5) + 1
        freq2 = ((i + 2) % 5) + 1
        a = np.sin(2 * np.pi * freq1 * t) + np.random.normal(0, 0.1, size)
        b = np.sin(2 * np.pi * freq1 * t + (i * 0.1)) + np.random.normal(0, 0.1, size)
        save_signal(f"test6_sinal_real_{i+1:03d}", a, b)

if __name__ == "__main__":
    main()