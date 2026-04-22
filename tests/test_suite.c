#include <stdio.h>
#include "cross_correlation.h"

float s_a[SIGNAL_SIZE];
float s_b[SIGNAL_SIZE];
float res[CORRELATION_SIZE];

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

    printf("CASO A:\n");
    printf("Vetor s_a: 1.0 no indice 500 (resto 0.0)\n");
    printf("Vetor s_b: 1.0 no indice 550 (resto 0.0)\n");
    printf("Pico esperado: Posicao 949\n");
    imprimir_janela_vetor(949, res);

    zerar_sinais();
    s_a[550] = 1.0f;
    s_b[500] = 1.0f;
    calcular_correlacao_cruzada(s_a, s_b, res);

    printf("CASO B:\n");
    printf("Vetor s_a: 1.0 no indice 550 (resto 0.0)\n");
    printf("Vetor s_b: 1.0 no indice 500 (resto 0.0)\n");
    printf("Pico esperado: Posicao 1049\n");
    imprimir_janela_vetor(1049, res);

    zerar_sinais();
    s_a[500] = 1.0f;
    s_b[500] = 1.0f;
    calcular_correlacao_cruzada(s_a, s_b, res);

    printf("CASO C:\n");
    printf("Vetor s_a: 1.0 no indice 500 (resto 0.0)\n");
    printf("Vetor s_b: 1.0 no indice 500 (resto 0.0)\n");
    printf("Pico esperado: Posicao 999\n");
    imprimir_janela_vetor(999, res);
}

void testar_sinais_constantes(void) {
    int i;
    printf("--- 2. SINAIS CONSTANTES ---\n");
    zerar_sinais();
    for (i = 0; i < SIGNAL_SIZE; i++) {
        s_a[i] = 1.0f;
        s_b[i] = 1.0f;
    }
    calcular_correlacao_cruzada(s_a, s_b, res);

    printf("Vetor s_a: 1.0 preenchido em todos os %d indices\n", SIGNAL_SIZE);
    printf("Vetor s_b: 1.0 preenchido em todos os %d indices\n", SIGNAL_SIZE);

    printf("Borda Esquerda:\n");
    imprimir_janela_vetor(0, res);

    printf("Centro:\n");
    imprimir_janela_vetor(SIGNAL_SIZE - 1, res);

    printf("Borda Direita:\n");
    imprimir_janela_vetor(CORRELATION_SIZE - 1, res);
}

void testar_bordas(void) {
    printf("--- 3. BORDAS ---\n");

    zerar_sinais();
    s_a[0] = 1.0f;
    s_b[SIGNAL_SIZE - 1] = 1.0f;
    calcular_correlacao_cruzada(s_a, s_b, res);

    printf("CASO A:\n");
    printf("Vetor s_a: 1.0 no indice 0 (resto 0.0)\n");
    printf("Vetor s_b: 1.0 no indice %d (resto 0.0)\n", SIGNAL_SIZE - 1);
    printf("Extremo Esquerdo (Pico esperado em 0):\n");
    imprimir_janela_vetor(0, res);
    printf("Extremo Direito (Deve ser 0.00):\n");
    imprimir_janela_vetor(CORRELATION_SIZE - 1, res);

    zerar_sinais();
    s_a[SIGNAL_SIZE - 1] = 1.0f;
    s_b[0] = 1.0f;
    calcular_correlacao_cruzada(s_a, s_b, res);

    printf("CASO B:\n");
    printf("Vetor s_a: 1.0 no indice %d (resto 0.0)\n", SIGNAL_SIZE - 1);
    printf("Vetor s_b: 1.0 no indice 0 (resto 0.0)\n");
    printf("Extremo Esquerdo (Deve ser 0.00):\n");
    imprimir_janela_vetor(0, res);
    printf("Extremo Direito (Pico esperado em %d):\n", CORRELATION_SIZE - 1);
    imprimir_janela_vetor(CORRELATION_SIZE - 1, res);
}

int main(void) {
    testar_impulso();
    testar_sinais_constantes();
    testar_bordas();
    return 0;
}
