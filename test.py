import glob
import numpy as np
import os

def main():
    os.makedirs("saidas_py", exist_ok=True)

    print("=" * 75)
    print(f"{'Validação de Correlação Cruzada 1D':^75}")
    print("=" * 75)
    print(f"{'Cenário':<25} | {'Status':<15} | {'Erro Máx':<10} | {'Observação'}")
    print("-" * 75)

    arquivos_saida = glob.glob("saidas_c/*_out.txt")
    prefixes = sorted([os.path.basename(f).replace("_out.txt", "") for f in arquivos_saida])

    if not prefixes:
        print("Nenhum teste encontrado. Execute o binário em C primeiro.")
        return

    sucessos = 0
    falhas = 0

    for prefix in prefixes:
        try:
            s_a = np.loadtxt(f"sinais/{prefix}_a.txt")
            s_b = np.loadtxt(f"sinais/{prefix}_b.txt")
            res_c = np.loadtxt(f"saidas_c/{prefix}_out.txt")
        except FileNotFoundError:
            continue

        res_py = np.correlate(s_a, s_b, mode='full')
        np.savetxt(f"saidas_py/{prefix}_out.txt", res_py, fmt="%.6f")

        erro_maximo = np.max(np.abs(res_py - res_c))

        if np.allclose(res_py, res_c, atol=1e-3):
            status = "\033[92m[✓] Aprovado\033[0m"
            sucessos += 1
            obs = "Exato" if erro_maximo == 0 else "Desvio float32"
        else:
            status = "\033[91m[✗] Reprovado\033[0m"
            falhas += 1
            obs = "Divergência algorítmica"

        print(f"{prefix[:25]:<25} | {status:<24} | {erro_maximo:<10.6f} | {obs}")

    print("=" * 75)
    print(f"Resultado Final: \033[92m{sucessos} Aprovados\033[0m | \033[91m{falhas} Reprovados\033[0m")
    print("=" * 75)

if __name__ == "__main__":
    main()