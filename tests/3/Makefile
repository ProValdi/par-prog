all:
	gcc -fopenmp not-parallel-task3.c -o ./not-parallel-task3.exe
	./not-parallel-task3.exe
	./build.sh
	./job.sh
	diff parallel.txt not-parallel.txt

clean:
	rm *.exe