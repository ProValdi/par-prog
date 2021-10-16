#include "mpi.h"
#include "stdio.h"

int main(int argc, char** argv) {
	int commSize = 0;
	int rank = 0;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &commSize);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	printf("Hello World!");
	printf("My id is [ %d ] and my communicator size is %d\n\n", rank, commSize);
	MPI_Finalize();
}
