#include "cross_correlation.h"

void calcular_correlacao_cruzada(float x[], float y[], float resultado[]) {
    int i;
    int j;
    int deslocamento;
    int amostras_sobrepostas;
    int inicio_x;
    int inicio_y;
    float soma;

    for (i = 0; i < SIGNAL_SIZE - 1; i++) {
        deslocamento = (SIGNAL_SIZE - 1) - i;
        amostras_sobrepostas = i + 1;
        inicio_x = 0;
        inicio_y = deslocamento;
        soma = 0.0f;

        for (j = 0; j < amostras_sobrepostas; j++) {
            soma += x[inicio_x + j] * y[inicio_y + j];
        }

        resultado[i] = soma;
    }

    amostras_sobrepostas = SIGNAL_SIZE;
    inicio_x = 0;
    inicio_y = 0;
    soma = 0.0f;

    for (j = 0; j < amostras_sobrepostas; j++) {
        soma += x[inicio_x + j] * y[inicio_y + j];
    }

    resultado[SIGNAL_SIZE - 1] = soma;

    for (i = SIGNAL_SIZE; i < CORRELATION_SIZE; i++) {
        deslocamento = i - (SIGNAL_SIZE - 1);
        amostras_sobrepostas = SIGNAL_SIZE - deslocamento;
        inicio_x = deslocamento;
        inicio_y = 0;
        soma = 0.0f;

        for (j = 0; j < amostras_sobrepostas; j++) {
            soma += x[inicio_x + j] * y[inicio_y + j];
        }

        resultado[i] = soma;
    }
}
