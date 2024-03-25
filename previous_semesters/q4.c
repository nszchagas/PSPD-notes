// q4.c

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

#define VECTOR_SIZE 100

int main(int argc, char **argv) {
    int vector[VECTOR_SIZE];
    int meurank, nprocs;
    int offset, start, end, chunk;
    MPI_Status st;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &meurank);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

    if (meurank == 0) {

        for (int i = 0; i < VECTOR_SIZE; i++) {
            vector[i] = i;
        }

        chunk = VECTOR_SIZE / (nprocs - 1);

        for (int i = 1; i < nprocs; i++) {
            offset = rand() % 15;  
            start = (i - 1) * chunk;
            end = start + chunk;

            if (i == nprocs - 1) {
                end = VECTOR_SIZE;
            }

            MPI_Send(&offset, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
            MPI_Send(&start, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
            MPI_Send(&end, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
        }

        offset = rand() % 15;
        start = (nprocs - 1) * chunk;
        end = VECTOR_SIZE;

        for (int i = start; i < end; i++) {
            printf("Process 0: vector[%d] = %d\n", i, vector[i]);
        }
    } else {

        MPI_Recv(&offset, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &st);
        MPI_Recv(&start, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &st);
        MPI_Recv(&end, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &st);

        for (int i = start; i < end; i++) {
            printf("Process %d: vector[%d] = %d\n", meurank, i, vector[i + offset]);
        }
    }

    MPI_Finalize();
    return 0;
}
