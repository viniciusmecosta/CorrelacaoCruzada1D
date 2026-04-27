#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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

void exportar_arquivos_teste(const char *prefix) {
    char filename[256];
    int i;
    FILE *f;

    sprintf(filename, "sinais/%s_a.txt", prefix);
    f = fopen(filename, "w");
    if (f) {
        for (i = 0; i < SIGNAL_SIZE; i++) {
            fprintf(f, "%.6f\n", s_a[i]);
        }
        fclose(f);
    }

    sprintf(filename, "sinais/%s_b.txt", prefix);
    f = fopen(filename, "w");
    if (f) {
        for (i = 0; i < SIGNAL_SIZE; i++) {
            fprintf(f, "%.6f\n", s_b[i]);
        }
        fclose(f);
    }

    sprintf(filename, "saidas_c/%s_out.txt", prefix);
    f = fopen(filename, "w");
    if (f) {
        for (i = 0; i < CORRELATION_SIZE; i++) {
            fprintf(f, "%.6f\n", res[i]);
        }
        fclose(f);
    }
}

void testar_impulso(void) {
    zerar_sinais();
    s_a[500] = 1.0f;
    s_b[550] = 1.0f;
    calcular_correlacao_cruzada(s_a, s_b, res);
    exportar_arquivos_teste("test1_impulso_a");

    zerar_sinais();
    s_a[550] = 1.0f;
    s_b[500] = 1.0f;
    calcular_correlacao_cruzada(s_a, s_b, res);
    exportar_arquivos_teste("test1_impulso_b");

    zerar_sinais();
    s_a[500] = 1.0f;
    s_b[500] = 1.0f;
    calcular_correlacao_cruzada(s_a, s_b, res);
    exportar_arquivos_teste("test1_impulso_c");
}

void testar_sinais_constantes(void) {
    int i;
    zerar_sinais();
    for (i = 0; i < SIGNAL_SIZE; i++) {
        s_a[i] = 1.0f;
        s_b[i] = 1.0f;
    }
    calcular_correlacao_cruzada(s_a, s_b, res);
    exportar_arquivos_teste("test2_constantes");
}

void testar_bordas(void) {
    zerar_sinais();
    s_a[0] = 1.0f;
    s_b[SIGNAL_SIZE - 1] = 1.0f;
    calcular_correlacao_cruzada(s_a, s_b, res);
    exportar_arquivos_teste("test3_bordas_a");

    zerar_sinais();
    s_a[SIGNAL_SIZE - 1] = 1.0f;
    s_b[0] = 1.0f;
    calcular_correlacao_cruzada(s_a, s_b, res);
    exportar_arquivos_teste("test3_bordas_b");
}

void testar_degrau(void) {
    int i;
    zerar_sinais();
    for (i = SIGNAL_SIZE / 2; i < SIGNAL_SIZE; i++) {
        s_a[i] = 1.0f;
    }
    for (i = SIGNAL_SIZE / 4; i < SIGNAL_SIZE; i++) {
        s_b[i] = 1.0f;
    }
    calcular_correlacao_cruzada(s_a, s_b, res);
    exportar_arquivos_teste("test4_degrau");
}

void testar_exponencial(void) {
    int i;
    zerar_sinais();
    for (i = 0; i < SIGNAL_SIZE; i++) {
        s_a[i] = exp(-0.01f * i);
        s_b[i] = exp(-0.02f * i);
    }
    calcular_correlacao_cruzada(s_a, s_b, res);
    exportar_arquivos_teste("test5_exponencial");
}

void testar_n_aleatorios(int n) {
    int k, i;
    char prefix[256];

    for (k = 0; k < n; k++) {
        zerar_sinais();
        for (i = 0; i < SIGNAL_SIZE; i++) {
            s_a[i] = ((float) rand() / RAND_MAX) * 2.0f - 1.0f;
            s_b[i] = ((float) rand() / RAND_MAX) * 2.0f - 1.0f;
        }
        calcular_correlacao_cruzada(s_a, s_b, res);
        sprintf(prefix, "test6_rand_lote_%03d", k + 1);
        exportar_arquivos_teste(prefix);
    }
}

int main(void) {
    srand(42);

    testar_impulso();
    testar_sinais_constantes();
    testar_bordas();
    testar_degrau();
    testar_exponencial();

    testar_n_aleatorios(20);

    return 0;
}
