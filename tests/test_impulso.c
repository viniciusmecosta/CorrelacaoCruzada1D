#include <stdio.h>
#include "cross_correlation.h"

float s_a[SIGNAL_SIZE];
float s_b[SIGNAL_SIZE];
float res[CORRELATION_SIZE];

int main(void) {
    int i;
    int pico_idx = 0;
    float max_val = -1.0f;

    for (i = 0; i < SIGNAL_SIZE; i++) {
        s_a[i] = 0.0f;
        s_b[i] = 0.0f;
    }

    s_a[500] = 1.0f;
    s_b[500] = 1.0f;

    calcular_correlacao_cruzada(s_a, s_b, res);

    for (i = 0; i < CORRELATION_SIZE; i++) {
        if (res[i] > max_val) {
            max_val = res[i];
            pico_idx = i;
        }
    }

    printf("--- TESTE 1: IMPULSO UNITARIO (ALINHAMENTO ZERO) ---\n");
    printf("Esperado: Pico na posicao 999\n");
    printf("Resultado: Pico na posicao %d com valor %.2f\n", pico_idx, max_val);

    return 0;
}