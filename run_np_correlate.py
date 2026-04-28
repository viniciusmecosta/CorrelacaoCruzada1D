import os
import numpy as np


def main():
    os.makedirs("saidas_py", exist_ok=True)
    if not os.path.exists("sinais/index.txt"):
        return

    with open("sinais/index.txt", "r") as f:
        prefixes = [line.strip() for line in f if line.strip()]

    for prefix in prefixes:
        try:
            a = np.loadtxt(f"sinais/{prefix}_a.txt")
            b = np.loadtxt(f"sinais/{prefix}_b.txt")
        except FileNotFoundError:
            continue

        res = np.correlate(a, b, mode='full')
        np.savetxt(f"saidas_py/{prefix}_out.txt", res, fmt="%.6f")


if __name__ == "__main__":
    main()