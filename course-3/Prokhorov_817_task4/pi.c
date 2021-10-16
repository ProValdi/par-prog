#include "mpi.h"
#include "stdio.h"
#include "stdlib.h"
#include <math.h>

// подынтегральная функция для вычисления числа pi
double f(double a) { 
	return (4.0 / (1.0 + a*a)); 
} 

int main(int argc, char *argv[]) {

	int procRank, procNum;

	double PI25DT = 3.141592653589793238462643; 
	double mypi, pi, h, sum, x, t1, t2; 

	MPI_Init(&argc, &argv); 
	MPI_Comm_size(MPI_COMM_WORLD, &procNum); 
	MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
	double timeStart = MPI_Wtime();
	
	int n = 2;
		if (argc > 1) 
			n = atoi(argv[1]); // считываем количество слагаемых суммы


	if ( procRank == 0) {
		t1 = MPI_Wtime(); 
	} 

	MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD); 

	// вычисление локальных сумм
	
	h = 1.0 / (double) n; 
	sum = 0.0; 
	for (int i = procRank + 1; i <= n; i += procNum) { 
		x = h * ((double)i - 0.5); 
		sum += f(x); 
	} 
	// сложение локальных сумм (редукция)
	mypi = h * sum; 
	MPI_Reduce(&mypi, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
	// вывод результатов в мастер-процессе
	if (!procRank) {
		t2 = MPI_Wtime(); 
		printf("pi is approximately %.16f, Error is %.16f\n", pi, fabs(pi - PI25DT)); 
		printf("wall clock time = %f\n",t2 - t1); 
	} else {
		printf("employee[%d]: wall time %lf\n", procRank, MPI_Wtime() - timeStart);
	}
	MPI_Finalize(); 
}