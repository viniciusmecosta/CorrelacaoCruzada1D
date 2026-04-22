#include <stdio.h>
#include "cross_correlation.h"

float s_a[SIGNAL_SIZE];
float s_b[SIGNAL_SIZE];
float res[CORRELATION_SIZE];
float res_secundario[CORRELATION_SIZE];

void zerar_sinais(void) {
    int i;
    for (i = 0; i < SIGNAL_SIZE; i++) {
        s_a[i] = 0.0f;
        s_b[i] = 0.0f;
    }
}

void imprimir_janela_vetor(int indice_central, float vetor[]) {
    int i;
    int inicio = indice_central - 2;
    int fim = indice_central + 2;

    if (inicio < 0) inicio = 0;
    if (fim >= CORRELATION_SIZE) fim = CORRELATION_SIZE - 1;

    for (i = inicio; i <= fim; i++) {
        printf("  res[%4d] = %9.2f\n", i, vetor[i]);
    }
    printf("\n");
}

void testar_impulso(void) {
    printf("--- 1. SINAL IMPULSO ---\n");
    zerar_sinais();
    s_a[500] = 1.0f;
    s_b[550] = 1.0f;
    calcular_correlacao_cruzada(s_a, s_b, res);

    printf("Entrada: s_a[500]=1.0 e s_b[550]=1.0 (resto 0.0)\n");
    printf("Pico esperado: 949\n");
    imprimir_janela_vetor(949, res);
}

void testar_autocorrelacao(void) {
    int i;
    printf("--- 2. AUTOCORRELACAO ---\n");
    zerar_sinais();
    for (i = 0; i < SIGNAL_SIZE; i++) {
        s_a[i] = (float)(i % 10);
        s_b[i] = s_a[i];
    }
    calcular_correlacao_cruzada(s_a, s_b, res);

    printf("Entrada: s_a e s_b recebem a mesma onda (i %% 10)\n");
    printf("Pico esperado: 999\n");
    imprimir_janela_vetor(999, res);
}

void testar_sinais_constantes(void) {
    int i;

    printf("--- 3. SINAIS CONSTANTES ---\n");
    zerar_sinais();
    for (i = 0; i < SIGNAL_SIZE; i++) {
        s_a[i] = 1.0f;
        s_b[i] = 1.0f;
    }
    calcular_correlacao_cruzada(s_a, s_b, res);

    printf("Entrada: s_a e s_b preenchidos totalmente com 1.0\n");
    printf("Borda Esquerda:\n");
    imprimir_janela_vetor(0, res);

    printf("Centro:\n");
    imprimir_janela_vetor(SIGNAL_SIZE - 1, res);

    printf("Borda Direita:\n");
    imprimir_janela_vetor(CORRELATION_SIZE - 1, res);
}

void testar_bordas(void) {
    printf("--- 4. BORDAS E EXTRAPOLACAO ---\n");

    zerar_sinais();
    s_a[0] = 1.0f;
    s_b[SIGNAL_SIZE - 1] = 1.0f;
    calcular_correlacao_cruzada(s_a, s_b, res);

    printf("Entrada A: s_a[0]=1.0 e s_b[%d]=1.0 (resto 0.0)\n", SIGNAL_SIZE - 1);
    printf("Extremo Esquerdo (Pico):\n");
    imprimir_janela_vetor(0, res);
    printf("Extremo Direito (Deve ser 0.00):\n");
    imprimir_janela_vetor(CORRELATION_SIZE - 1, res);

    zerar_sinais();
    s_a[SIGNAL_SIZE - 1] = 1.0f;
    s_b[0] = 1.0f;
    calcular_correlacao_cruzada(s_a, s_b, res);

    printf("Entrada B: s_a[%d]=1.0 e s_b[0]=1.0 (resto 0.0)\n", SIGNAL_SIZE - 1);
    printf("Extremo Esquerdo (Deve ser 0.00):\n");
    imprimir_janela_vetor(0, res);
    printf("Extremo Direito (Pico):\n");
    imprimir_janela_vetor(CORRELATION_SIZE - 1, res);
}

void testar_unitario_extremos(void) {
    printf("--- 5. SINAL UNITARIO SIMULTANEO ---\n");
    zerar_sinais();
    s_a[0] = 1.0f;
    s_a[SIGNAL_SIZE - 1] = 1.0f;
    s_b[0] = 1.0f;
    s_b[SIGNAL_SIZE - 1] = 1.0f;

    calcular_correlacao_cruzada(s_a, s_b, res);

    printf("Entrada: s_a e s_b com 1.0 em 0 e %d simultaneamente (resto 0.0)\n", SIGNAL_SIZE - 1);
    printf("Interseccao Extrema Esquerda:\n");
    imprimir_janela_vetor(0, res);

    printf("Alinhamento Perfeito (Centro):\n");
    imprimir_janela_vetor(SIGNAL_SIZE - 1, res);

    printf("Interseccao Extrema Direita:\n");
    imprimir_janela_vetor(CORRELATION_SIZE - 1, res);
}

void testar_antissimetria(void) {
    int i;
    int falhas = 0;
    int q1 = CORRELATION_SIZE / 4;
    int q2 = CORRELATION_SIZE / 2;
    int q3 = (CORRELATION_SIZE * 3) / 4;
    int fim = CORRELATION_SIZE - 1;

    printf("--- 6. ANTISSIMETRIA ---\n");
    zerar_sinais();
    for (i = 0; i < SIGNAL_SIZE; i++) {
        s_a[i] = (float)(i % 5);
        s_b[i] = (float)(i % 7);
    }

    calcular_correlacao_cruzada(s_a, s_b, res);
    calcular_correlacao_cruzada(s_b, s_a, res_secundario);

    for (i = 0; i < CORRELATION_SIZE; i++) {
        if (res[i] != res_secundario[fim - i]) {
            falhas++;
        }
    }

    printf("Entrada: s_a recebe (i %% 5) e s_b recebe (i %% 7)\n");
    printf("Divergencias identificadas: %d\n", falhas);
    printf("Amostragem estrutural corr(A,B) vs corr(B,A):\n");
    printf("  res_ab[%4d] = %9.2f  |  res_ba[%4d] = %9.2f\n", 0, res[0], fim, res_secundario[fim]);
    printf("  res_ab[%4d] = %9.2f  |  res_ba[%4d] = %9.2f\n", q1, res[q1], fim - q1, res_secundario[fim - q1]);
    printf("  res_ab[%4d] = %9.2f  |  res_ba[%4d] = %9.2f\n", q2, res[q2], fim - q2, res_secundario[fim - q2]);
    printf("  res_ab[%4d] = %9.2f  |  res_ba[%4d] = %9.2f\n", q3, res[q3], fim - q3, res_secundario[fim - q3]);
    printf("  res_ab[%4d] = %9.2f  |  res_ba[%4d] = %9.2f\n\n", fim, res[fim], 0, res_secundario[0]);
}

int main(void) {
    testar_impulso();
    testar_autocorrelacao();
    testar_sinais_constantes();
    testar_bordas();
    testar_unitario_extremos();
    testar_antissimetria();
    return 0;
}