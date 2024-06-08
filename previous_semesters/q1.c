#include <stdio.h>
#include <mpi.h>
#define NUM_STEPS 8000000

int main(int argc, char** argv) {
    int i, rank, size;
    double x, pi, sum = 0.0, step, partial_sum = 0.0;

    step = 1.0/(double) NUM_STEPS;

    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &size);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    for (i = rank; i < NUM_STEPS; i += size) {
        x = (i+0.5)*step;
        partial_sum += 4.0/(1.0+x*x);
    }

    MPI_Reduce(&partial_sum, &sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        pi = sum*step;
        printf("Pi = %f\n", pi);
    }

    MPI_Finalize();

    return 0;
}
