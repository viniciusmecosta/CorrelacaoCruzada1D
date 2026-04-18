#include <stdio.h>
#include "cross_correlation.h"

float s_a[SIGNAL_SIZE];
float s_b[SIGNAL_SIZE];
float res[CORRELATION_SIZE];

int main(void) {
    int larguras[4] = {10, 50, 100, 200};
    int i, j, k, w;
    int pico_idx;
    float max_val;

    printf("--- TESTE 3: SINAIS CONTINUOS (BLOCOS DE LEITURA) ---\n");

    for (w = 0; w < 4; w++) {
        for (i = 0; i < SIGNAL_SIZE; i++) {
            s_a[i] = 0.0f;
            s_b[i] = 0.0f;
        }

        for (k = 400; k < 400 + larguras[w]; k++) {
            s_a[k] = 2.0f;
        }
        for (k = 420; k < 420 + larguras[w]; k++) {
            s_b[k] = 2.0f;
        }

        calcular_correlacao_cruzada(s_a, s_b, res);

        pico_idx = 0;
        max_val = -1.0f;

        for (j = 0; j < CORRELATION_SIZE; j++) {
            if (res[j] > max_val) {
                max_val = res[j];
                pico_idx = j;
            }
        }

        printf("Largura %3d | Esperado: 979 | Resultado: %3d | Valor Max: %.2f\n", larguras[w], pico_idx, max_val);
    }

    return 0;
}