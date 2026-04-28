import os
import numpy as np


def main():
    if not os.path.exists("sinais/index.txt"):
        return

    with open("sinais/index.txt", "r") as f:
        prefixes = [line.strip() for line in f if line.strip()]

    sucessos = 0
    falhas = 0
    report_lines = []

    print("=" * 75)
    print(f"{'Validação de Correlação Cruzada 1D':^75}")
    print("=" * 75)
    print(f"{'Cenário':<25} | {'Status':<15} | {'Erro Máx':<10} | {'Observação'}")
    print("-" * 75)

    for prefix in prefixes:
        try:
            res_c = np.loadtxt(f"saidas_c/{prefix}_out.txt")
            res_py = np.loadtxt(f"saidas_py/{prefix}_out.txt")
        except FileNotFoundError:
            continue

        diff = np.abs(res_py - res_c)
        erro_maximo = np.max(diff)
        passou = np.allclose(res_py, res_c, atol=1e-3)

        if passou:
            status = "\033[92m[✓] Aprovado\033[0m"
            sucessos += 1
            obs = "Exato" if erro_maximo == 0 else "Desvio float32"
        else:
            status = "\033[91m[✗] Reprovado\033[0m"
            falhas += 1
            obs = "Resultado Divergente"

        print(f"{prefix[:25]:<25} | {status:<24} | {erro_maximo:<10.6f} | {obs}")

        if erro_maximo > 0:
            report_lines.append(
                f"Teste: {prefix} | Status: {'Aprovado' if passou else 'Reprovado'} | Erro Máximo: {erro_maximo:.6f}")
            report_lines.append(f"{'Índice':<10} | {'Valor C':<15} | {'Valor Python':<15} | {'Diferença':<15}")
            report_lines.append("-" * 65)

            indices_ordenados = np.argsort(diff)[::-1]
            top_10 = indices_ordenados[:10]

            for idx in top_10:
                if diff[idx] > 0:
                    report_lines.append(f"{idx:<10} | {res_c[idx]:<15.6f} | {res_py[idx]:<15.6f} | {diff[idx]:<15.6f}")
            report_lines.append("\n")

    print("=" * 75)
    print(f"Resultado Final: \033[92m{sucessos} Aprovados\033[0m | \033[91m{falhas} Reprovados\033[0m")
    print("=" * 75)

    if report_lines:
        with open("report_errors.txt", "w") as f:
            f.write("\n".join(report_lines))


if __name__ == "__main__":
    main()