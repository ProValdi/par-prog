all:
	gcc -fopenmp not-parallel-task3.c -o ./not-parallel-task3.exe
	./not-parallel-task3.exe
	gcc -fopenmp task3.c -o task3.exe
	OMP_NUM_THREADS=8 ./task3.exe
	diff parallel.txt not-parallel.txt

clean:
	rm -f *.exe
	rm -f *.txt