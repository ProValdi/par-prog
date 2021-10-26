#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "omp.h"

int main (int argc, char** argv) {

    int N = 0;
    N = atoi(argv[1]);

    if (N == 0) {
        printf("wrong input\n");
        return -1;
    }
    
    int sum = 0;

    #pragma omp parallel for reduction(+:sum) schedule(auto)
    for (int i = 1; i <= N; i++) 
        sum+=i;
    printf("result of sum 1 to %d: %d \n", N, sum);
}