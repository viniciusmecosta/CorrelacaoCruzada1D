#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cross_correlation.h"

float s_a[SIGNAL_SIZE];
float s_b[SIGNAL_SIZE];
float res[CORRELATION_SIZE];

int main(void) {
    FILE *index_file = fopen("sinais/index.txt", "r");
    char prefix[256];
    char filepath_a[512], filepath_b[512], filepath_out[512];
    FILE *fa, *fb, *fout;
    int i;

    if (!index_file) {
        return 1;
    }

    while (fscanf(index_file, "%255s", prefix) == 1) {
        sprintf(filepath_a, "sinais/%s_a.txt", prefix);
        sprintf(filepath_b, "sinais/%s_b.txt", prefix);
        sprintf(filepath_out, "saidas_c/%s_out.txt", prefix);

        fa = fopen(filepath_a, "r");
        fb = fopen(filepath_b, "r");

        if (!fa || !fb) {
            if (fa) fclose(fa);
            if (fb) fclose(fb);
            continue;
        }

        for (i = 0; i < SIGNAL_SIZE; i++) {
            if (fscanf(fa, "%f", &s_a[i]) != 1) {
                s_a[i] = 0.0f;
            }
            if (fscanf(fb, "%f", &s_b[i]) != 1) {
                s_b[i] = 0.0f;
            }
        }
        fclose(fa);
        fclose(fb);

        calcular_correlacao_cruzada(s_a, s_b, res);

        fout = fopen(filepath_out, "w");
        if (fout) {
            for (i = 0; i < CORRELATION_SIZE; i++) {
                fprintf(fout, "%.6f\n", res[i]);
            }
            fclose(fout);
        }
    }

    fclose(index_file);
    return 0;
}