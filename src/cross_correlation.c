#include "cross_correlation.h"

void calcular_correlacao_cruzada(const float x[], const float y[], float resultado[]) {
    int i;
    int j;
    int deslocamento;
    float soma;

    const float *ptr_x;
    const float *ptr_y;

    for (i = 0; i < SIGNAL_SIZE - 1; i++) {
        deslocamento = (SIGNAL_SIZE - 1) - i;
        soma = 0.0f;
        ptr_x = x;
        ptr_y = y + deslocamento;

        for (j = 0; j <= i; j++) {
            soma += (*ptr_x++) * (*ptr_y++);
        }

        resultado[i] = soma;
    }

    soma = 0.0f;
    ptr_x = x;
    ptr_y = y;

    for (j = 0; j < SIGNAL_SIZE; j++) {
        soma += (*ptr_x++) * (*ptr_y++);
    }

    resultado[SIGNAL_SIZE - 1] = soma;

    for (i = SIGNAL_SIZE; i < CORRELATION_SIZE; i++) {
        deslocamento = i - (SIGNAL_SIZE - 1);
        soma = 0.0f;
        ptr_x = x + deslocamento;
        ptr_y = y;

        for (j = deslocamento; j < SIGNAL_SIZE; j++) {
            soma += (*ptr_x++) * (*ptr_y++);
        }

        resultado[i] = soma;
    }
}
