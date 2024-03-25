#include <stdio.h>
#include <omp.h>
#include <string.h>

int main(void) {

	// omp_set_num_threads(x);

	#pragma omp parallel
	{
		printf("Thread: %d\n", omp_get_thread_num());	
	}
	
	
	int n=100;
	int vetor[omp_get_max_threads()];
	memset(vetor, 0, 4*omp_get_max_threads());
	
	#pragma omp parallel for // private(vetor, n) ou shares(vetor, n)
		for(int i=0;i<n;i++)
			vetor[omp_get_thread_num()]++;
			
		// esse for não está paralelizado
		for(int i=0;i<omp_get_max_threads(); i++)
			printf("thread %d, executou %d iterações\n", i, vetor[i]);
}
