#ifndef CROSS_CORRELATION_H
#define CROSS_CORRELATION_H

#define SIGNAL_SIZE 1000
#define CORRELATION_SIZE (SIGNAL_SIZE + SIGNAL_SIZE - 1)

void calcular_correlacao_cruzada(float x[], float y[], float resultado[]);

#endif
