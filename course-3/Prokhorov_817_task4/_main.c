#include "mpi.h"
#include "stdio.h"
#include "stdlib.h"

const int MASTER = 0;

int main(int argc, char* argv[]) {
	int commSize = 0;
	int procRank = 0;
	int np = 0;
	int span = 0;
	
	MPI_Init(&argc, &argv);

	MPI_Comm_size(MPI_COMM_WORLD, &commSize);
	MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
	double timeStart = MPI_Wtime();
	/* 	distribution of operands to sum is the same as
		the parallel sum task: 
	 */

	int n = 2;
	if (argc > 1) 
		n = atoi(argv[1]);

	np = commSize;
	
	/* making sure that every process gets to sum at least 2 numbers */
	if (n / 2 < commSize)
		np = n / 2;

	span = n / np;

	double localSum = 0;
	/* Only participate if you're needed */
	if (procRank < np) {
		int l = 0, m = 0;
		if ( (procRank == np-1) && n % span != 0) {
			l = n;
			m = span * procRank + 1;
		} else {	
			l = span * (procRank+1);
			m = span * procRank + 1;
		}
		/* 	this cycle sums specified terms of the series
			with number m through l
			
			e^x = sum(x^n/n!);
			e^1 = sum(1/n!);
			
			expCtr
		*/
		
		for (int expCtr = m; expCtr <= l; expCtr++) {
			/* nested circle calculates factorial */
			
			double termDenominator = 1;
			for (int i = 2; i <= expCtr; i++)
				termDenominator *= i;
			localSum += 1 / termDenominator;
		}
	}

	/* all processes call Reduce and sum their terms */
	double globalSum = 0;
	MPI_Reduce(&localSum, &globalSum, 1, MPI_DOUBLE, MPI_SUM, MASTER, MPI_COMM_WORLD);

	if (!procRank) {
		printf("master: calculated e: %lf; Wall time: %lf\n", globalSum+1, MPI_Wtime() - timeStart);
	} else {
		printf("employee[%d]: wall time %lf\n", procRank, MPI_Wtime() - timeStart);
	}
	MPI_Finalize();
}
