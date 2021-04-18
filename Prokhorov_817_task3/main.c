#include "mpi.h"
#include "stdio.h"
#include "stdlib.h"

#define ANSI_COLOR_BLUE  "\x1b[34m"
#define ANSI_COLOR_RED   "\x1b[31m"
#define ANSI_COLOR_RESET "\x1b[0m"

const int PRINT_TAG = 1;
const int CONFIRM_TAG = 0;
const int MASTER_PROCESS = 0;

int main(int argc, char** argv) {
        int commSize = -1;
        int procRank = -1;

        MPI_Init(&argc, &argv);
        MPI_Comm_size(MPI_COMM_WORLD, &commSize);
        MPI_Comm_rank(MPI_COMM_WORLD, &procRank);

        if (!procRank) { // ветка основных процессов

                printf("master: commSize is [%d] + {1} = %d\n", commSize-1, commSize); 
                int* message = (int*) calloc(commSize, sizeof(int)); 
                int i = 1; 
                for (; i < argc; i++) 
                        message[i-1] = atoi(argv[i]); 
 
                // Пока номер процесса меньше чем максимальное количество процессов 
                int activeProc = 1; 
                int buff = 0; 
                MPI_Status status; 
                while (activeProc < commSize) { 
 
                        // Отсылаем сообщение дочерним процессам
                        MPI_Send(&message[activeProc-1], 1, MPI_INT, activeProc, PRINT_TAG, MPI_COMM_WORLD); 
 
                        // Получаем подтверждение
                        MPI_Recv(&buff, 1, MPI_INT, activeProc, CONFIRM_TAG, MPI_COMM_WORLD, &status); 
                        activeProc++; 
                } 
 
        } else { // ветка дочерних процессов
                int data = 0; 
                MPI_Status status; 
 
                // Ждём пока придёт команда печати от главного процесса
                MPI_Recv(&data, 1, MPI_INT, MASTER_PROCESS, PRINT_TAG, MPI_COMM_WORLD, &status); 
 
                printf(ANSI_COLOR_RED "process[%d]: %d\n" ANSI_COLOR_RESET, procRank, data); 
 
                // Отсылаем обратно результат работы программы
                MPI_Send(&data, 1, MPI_INT, MASTER_PROCESS, CONFIRM_TAG, MPI_COMM_WORLD); 
        } 
        MPI_Finalize(); 
} 

