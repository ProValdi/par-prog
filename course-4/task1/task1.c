#include "omp.h"
#include <stdio.h>

int main (int argc, char** argv) {

	printf("Hello, world! from main thread [%d]\n", omp_get_thread_num());

	#pragma omp parallel 
	{
		printf("Hello, world! from parallel thread [%d]\n", omp_get_thread_num());
	}

}