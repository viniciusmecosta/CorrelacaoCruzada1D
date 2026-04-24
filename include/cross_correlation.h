#ifndef CROSS_CORRELATION_H
#define CROSS_CORRELATION_H

#define SIGNAL_SIZE 1000
#define CORRELATION_SIZE (SIGNAL_SIZE + SIGNAL_SIZE - 1)

void calcular_correlacao_cruzada(const float x[], const float y[], float resultado[]);

#endif
