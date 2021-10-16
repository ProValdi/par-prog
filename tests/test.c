#include <stdio.h> 
#include <mpi.h> 
#include <unistd.h> 

int main (int argc, char** argv) {
int size = 0; int rank = 0; 
MPI_Init (&argc, &argv); 
MPI_Comm_size (MPI_COMM_WORLD, &size); 
MPI_Comm_rank (MPI_COMM_WORLD, &rank); 
double start = 0, end = 0; 
MPI_Barrier (MPI_COMM_WORLD); 
start = MPI_Wtime (); int buf [1]; 
MPI_Status status; 

if (rank != 0) 
	MPI_Recv (buf, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status); 
sleep (1); 
MPI_Send (buf, 1, MPI_INT, (rank + 1) % size, 0, MPI_COMM_WORLD); 
sleep (rank) ; 
MPI_Recv (buf, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status); 

sleep (1); 

if (rank != size-1) 
	MPI_Send (buf, 1, MPI_INT, (rank + 1) % size, 0, MPI_COMM_WORLD); 
MPI_Barrier (MPI_COMM_WORLD); 
end = MPI_Wtime (); 
if (rank == 0) 
	printf(" [TIME] %lf sec\n", end - start); 
MPI_Finalize ();
return 0;
}


/*int main(int argc, char** argv) {
	int hello_number = 0;
	int world_size = 0;
	int world_rank = 0;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
	double timeStart = MPI_Wtime();

	int n = 2; 
	if (argc > 1) 
		n = atoi(argv[1]);

	struct {
		int proc_num;
		int y;
		int z;
	} sum_vector;



	if (world_rank == 0) {

		MPI_Bcast(void *buf, int count, MPI_Datatype type, int root, MPI_COMM_WORLD);
		/*
		printf("My id is [ %d ] and my communicator size is %d\n\n", world_rank, world_size);
		MPI_Status status;
		for (int i = 1; i < world_size; i++) {
			// MPI_INT - тип передаваемого сообщения
			// i - ранг (номер процесса)
			MPI_Recv(&hello_number, 1, MPI_INT, i, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
			printf("Hello world from process [%d]. Time elapsed: %lf\n", hello_number, MPI_Wtime() - timeStart);
		}*/
	/*} else {
		MPI_Send(&world_rank, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
	}
	
	MPI_Finalize();
}
*/