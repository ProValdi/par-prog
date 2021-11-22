#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "omp.h"

void print(int **matrix, int x, int y);
void printToFile(FILE *file, int **matrix, int x, int y);
void randomize(int **matrix, int x, int y, int limit);

int main (int argc, char** argv) {

    /*  
    arr[X][Y]

        0-----> Y
        |
        |
        X
    */

    int N1x = 200, N1y = 50; // size for 1st matrix
    int N2x = 50, N2y = 200; // size for 2nd matrix
    int limit = 100; // max value of matrix element

    N2x = N1y; // sizes must be compatible in case of in-code changing of predefined N1x,y and N2x,y

    int **matrix1; // size 20 x 5
    int **matrix2; // size 5 x 20
    int **result; // size 20 x 20

    matrix1 = (int**)calloc(N1x, sizeof(int*));
    for(int i = 0; i < N1x; i++) 
        matrix1[i] = (int*)calloc(N1y, sizeof(int));

    matrix2 = (int**)calloc(N2x, sizeof(int*));
    for(int i = 0; i < N2x; i++) 
        matrix2[i] = (int*)calloc(N2y, sizeof(int));

    result = (int**)calloc(N1x, sizeof(int*));
    for(int i = 0; i < N1x; i++) 
        result[i] = (int*)calloc(N2y, sizeof(int));
    
    // set random values
    randomize(matrix1, N1x, N1y, limit);
    randomize(matrix2, N2x, N2y, limit);

    // save matrices to files to share them with not parallel programm
    FILE *file;
    file = fopen("./matrix1.txt", "w");
    printToFile(file, matrix1, N1x, N1y);
    fclose(file);

    file = fopen("./matrix2.txt", "w");
    printToFile(file, matrix2, N2x, N2y);
    fclose(file);

    double timeStart = omp_get_wtime();

    #pragma omp parallel for shared(matrix1, matrix2, result)
    for(int i = 0; i < N1x; i++)
        for(int j = 0; j < N2y; j++)
            for(int k = 0; k < N1y; k++)
                result[i][j] += (matrix1[i][k] * matrix2[k][j]);
                
    printf("Summary spent time parallel: %lf\n\n", omp_get_wtime() - timeStart);

    file = fopen("./parallel-result.txt", "w");
    printToFile(file, result, N1x, N2y);
    fclose(file);

    // neatly free a memory
    for(int i = 0; i < N1x; i++)
        free(matrix1[i]);
    free(matrix1);

    for(int i = 0; i < N2x; i++)
        free(matrix2[i]);
    free(matrix2);

    for(int i = 0; i < N1x; i++)
        free(result[i]);
    free(result);
    return 0;
}

void print(int **matrix, int x, int y) {
    for(int i = 0; i < x; i++) {
        for(int j = 0; j < y; j++)
            printf("%d ", matrix[i][j]);
        printf("\n");
    }
    printf("\n");
}

void printToFile(FILE *file, int **matrix, int x, int y) {
    fprintf(file, "%d %d\n", x, y);
    for(int i = 0; i < x; i++) {
        for(int j = 0; j < y; j++)
            fprintf(file,"%d ", matrix[i][j]);
        fprintf(file, "\n");
    }
}

void randomize(int **matrix, int x, int y, int limit) {
    #pragma omp parallel for
    for(int i = 0; i < x; i++) 
        for(int j = 0; j < y; j++) 
            matrix[i][j] = rand() % limit;
}