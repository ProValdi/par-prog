#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "omp.h"

#define N 100000

int main (int argc, char** argv) {

    unsigned long b[N] = {0};

    unsigned long a[N];
    memset(a, 0, (N + 1) * sizeof(unsigned long));

    // assuming a[0] is 1-st, a[1] is 2-nd and so on
    for (int i = 0; i < N; i++) a[i] = i + 1;

    int div = omp_get_max_threads();
    int partSize = N / div;

    double timeStart = omp_get_wtime();

    #pragma omp parallel for shared(a, b) schedule(static, partSize)
    for (int i = 1; i < N; i++)
        b[i] = a[i-1]*a[i]*a[i+1]/3;

    printf("Summary spent time parallel: %lf\n", omp_get_wtime() - timeStart);

    FILE *file;
    file = fopen("./parallel.txt", "w");

    for (int i = 0; i < N; i++) 
        fprintf(file,"%ld\n", b[i]);

    fclose(file);
}