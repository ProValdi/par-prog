#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "omp.h"

void printToFile(FILE *file, int **matrix, int x, int y);

void print(int **matrix, int x, int y) {
    for(int i = 0; i < x; i++) {
        for(int j = 0; j < y; j++)
            printf("%d ", matrix[i][j]);
        printf("\n");
    }
    printf("\n");
}

// this app depends on a parallel task so it should be launched last
int main (int argc, char** argv) {

    int N1x = 0, N1y = 0; // size for 1st matrix
    int N2x = 0, N2y = 0; // size for 2nd matrix

    int **matrix1;
    int **matrix2;
    int **result;
    
    FILE *file;

    // scan for matrix1 -------------------|
    file = fopen("matrix1.txt","r");
    fscanf(file, "%d %d", &N1x, &N1y);

    // callocate mem
    matrix1 = (int**)calloc(N1x, sizeof(int*));
    for(int i = 0; i < N1x; i++) 
        matrix1[i] = (int*)calloc(N1y, sizeof(int));

    // scan file
    for(int i = 0; i < N1x; i++)
        for (int j = 0; j < N1y; j++)
            fscanf(file, "%d ", &matrix1[i][j]);
    fclose(file);
    // ------------------------------------|

    

    // scan for matrix2 -------------------|
    file = fopen("matrix2.txt","r");
    fscanf(file, "%d %d", &N2x, &N2y);

    // callocate mem
    matrix2 = (int**)calloc(N2x, sizeof(int*));
    for(int i = 0; i < N2x; i++) 
        matrix2[i] = (int*)calloc(N2y, sizeof(int));

    // scan file
    for(int i = 0; i < N2x; i++)
        for (int j = 0; j < N2y; j++)
            fscanf(file, "%d ", &matrix2[i][j]);
    fclose(file);
    // ------------------------------------|

    // callocate result
    result = (int**)calloc(N1x, sizeof(int*));
    for(int i = 0; i < N1x; i++) 
        result[i] = (int*)calloc(N2y, sizeof(int));

    double timeStart = omp_get_wtime();

    for(int i = 0; i < N1x; i++)
        for(int j = 0; j < N2y; j++)
            for(int k = 0; k < N1y; k++)
                result[i][j] += (matrix1[i][k] * matrix2[k][j]);
                
    printf("Summary spent time not-parallel: %lf\n", omp_get_wtime() - timeStart);

    file = fopen("./not-parallel-result.txt", "w");
    printToFile(file, result, N1x, N2y);
    fclose(file);


    // // neatly free a memory
    // for(int i = 0; i < N1x; i++)
    //     free(matrix1[i]);
    // free(matrix1);

    // for(int i = 0; i < N2x; i++)
    //     free(matrix2[i]);
    // free(matrix2);

    // for(int i = 0; i < N1x; i++)
    //     free(result[i]);
    // free(result);
    return 0;
}

void printToFile(FILE *file, int **matrix, int x, int y) {
    fprintf(file, "%d %d\n", x, y);
    for(int i = 0; i < x; i++) {
        for(int j = 0; j < y; j++)
            fprintf(file,"%d ", matrix[i][j]);
        fprintf(file, "\n");
    }
}