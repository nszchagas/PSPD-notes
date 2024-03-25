//caio martins  - 180074741
//yuri alves    - 180078640

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MASTER 0
#define ARRAY_SIZE 16

int main (int argc, char *argv[])  {
	int * a;
	int * b; 
	int * c;
	
	int total_proc;
	int rank;
	float n_per_proc;
    int n_reminder;
	int n = ARRAY_SIZE;
		
	MPI_Init (&argc, &argv);
	MPI_Comm_size (MPI_COMM_WORLD, &total_proc);
	MPI_Comm_rank (MPI_COMM_WORLD, &rank);

   	int * a_divided;
	int * b_divided;
	int * c_divided;
	
	if (rank == MASTER)  {
		a = (int*) malloc(sizeof(int) * n);
		b = (int*) malloc(sizeof(int) * n);
		c = (int*) malloc(sizeof(int) * n);

		for(int i = 0; i < n; i++)
			a[i] = i;

		for(int i = 0; i < n; i++)
			b[i] = i;
	}
	
	n_per_proc = n / total_proc;
    n_reminder = n % total_proc;
    n_reminder = ceil(n_reminder);
	
	a_divided = (int*) malloc(sizeof(int) * n_per_proc);
	b_divided = (int*) malloc(sizeof(int) * n_per_proc);
	c_divided = (int*) malloc(sizeof(int) * n_per_proc);
	
	MPI_Scatter(a, n_per_proc, MPI_INT, a_divided, n_per_proc, MPI_INT, MASTER, MPI_COMM_WORLD); 
	MPI_Scatter(b, n_per_proc, MPI_INT, b_divided, n_per_proc, MPI_INT, MASTER, MPI_COMM_WORLD); 
	
	for(int i = 0 ; i < n_per_proc; i++)
		c_divided[i] = a_divided[i] + b_divided[i];
	
	MPI_Gather(c_divided, n_per_proc, MPI_INT, c, n_per_proc, MPI_INT, MASTER, MPI_COMM_WORLD);

	if (rank == MASTER)  {			
		for(int i = 0; i < n; i++) {
			printf ("%d ", a[i]);
		}

        printf("\n + \n");
		for(int i = 0; i < n; i++) {
			printf ("%d ", b[i]);
		}

        printf("\n = \n");

        if(n_reminder > 0) {
            int aux = n-n_reminder;

            for(int i = aux; i < n; i++) {
                c[i] = a[i] + b[i];
            }
        }

		for(int i = 0; i < n; i++) {
			printf ("%d ", c[i]);
		}
		free(a);  free(b); free(c);
	}

	free(a_divided);  free(b_divided); free(c_divided);
	MPI_Finalize();  
	
	return 0;
}