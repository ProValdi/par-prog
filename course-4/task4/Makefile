all:
	gcc -fopenmp task4.c -o task4.exe
	OMP_NUM_THREADS=8 ./task4.exe
	gcc -fopenmp not-parallel-task4.c -o ./not-parallel-task4.exe
	./not-parallel-task4.exe
	diff parallel-result.txt not-parallel-result.txt

clean:
	rm -f *.exe
	rm -f *.txt