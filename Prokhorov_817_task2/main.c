#include "mpi.h"
#include "stdio.h"
#include "stdlib.h"

const int SUM_TAG = 1;
const int MAIN_PROC = 0;

int main(int argc, char** argv) {
	int commSize = 0;
	int procRank = 0;
	int np = 0;
	int toCalculateNum = 0;
	
	MPI_Init(&argc, &argv);

	MPI_Comm_size(MPI_COMM_WORLD, &commSize);
	MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
	double timeStart = MPI_Wtime();

	// Переменная для входящего числа
	int n = 0;

	if (argc > 1) {
		n = atoi(argv[1]);
	}
	
	// удостоверимся, что каждый процесс получит для суммирования как минимум два числа
	if (n / 2 < commSize) {
		np = n / 2;
	} else { // если -np было задано слишком большим, указываем максимально доступное количество потоков (процессов)
		np = commSize;
	}

	// Количество чисел для суммирования на каждый процесс
	toCalculateNum = n / np;

	int localSum = 0;

	// Проверяем, есть ли для нас свободная задача
	if (procRank < np) {

		int l = 0, m = 0;
		/* 
 			Для вычислений используем формулу:
 			S(l,m) = (1/2) * (l + m) / (l - m + 1); 
 			l и m - границы вычисления

			m = toCalculateNum * procRank + 1
			l = toCalculateNum * (procRank + 1) 

			А для последнего процесса количество чисел может быть бОльшим из-за округлений, поэтому

			l = toCalculateNum * (procRank + 1) + n % toCalculateNum
			m = toCalculateNum * procRank */
		if ( (procRank == np - 1) && n % toCalculateNum != 0) {
			l = toCalculateNum * (procRank + 1) + n % toCalculateNum;
			m = toCalculateNum * procRank + 1;
		} else {	
			l = toCalculateNum * (procRank + 1);
			m = toCalculateNum * procRank + 1;
		}
		
		localSum = (l + m) * (l - m + 1) / 2;	
		if (procRank) {
			MPI_Send(&localSum, 1, MPI_INT, MAIN_PROC, SUM_TAG, MPI_COMM_WORLD); 
		}
	}


	// Главный процесс собирает значения дочерних
	if (!procRank) {
		int buff = 0;
		MPI_Status status;
		// ждём пока не соберутся значения суммирования каждого процесса и суммируем
		int ctr = 1;
		while (ctr < np) {
			MPI_Recv(&buff, 1, MPI_INT, MPI_ANY_SOURCE, SUM_TAG, MPI_COMM_WORLD, &status);
			localSum += buff;
			ctr++;
		}
		printf("Total sum is  %d\n", localSum);
	}

	printf("Process %d: spent time: %lf\n", procRank, MPI_Wtime() - timeStart);
	MPI_Finalize();
}