// Caio Martins - 180074741
// Yuri Alves - 180078640

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define MATRIX_SIZE 4

void printMatrix(int matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    int i, j;
    for (i = 0; i < MATRIX_SIZE; i++) {
        for (j = 0; j < MATRIX_SIZE; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char *argv[]) {
    int rank, size, i, j;
    int A[MATRIX_SIZE][MATRIX_SIZE];
    int B[MATRIX_SIZE][MATRIX_SIZE];
    int C[MATRIX_SIZE][MATRIX_SIZE];
    int rows_per_worker, extra_rows;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size != 5) {
        printf("O número total de processos deve ser igual a 5 (1 mestre e 4 workers).\n");
        MPI_Finalize();
        return 0;
    }

    // Inicialização das matrizes A e B com números aleatórios
    srand(rank);
    for (i = 0; i < MATRIX_SIZE; i++) {
        for (j = 0; j < MATRIX_SIZE; j++) {
            A[i][j] = rand() % 10;
            B[i][j] = rand() % 10;
        }
    }

    if (rank == 0) {
        printf("Matriz A:\n");
        printMatrix(A);
        printf("\nMatriz B:\n");
        printMatrix(B);
        printf("\n");
    }

    // Cálculo das linhas que cada worker irá processar
    rows_per_worker = MATRIX_SIZE / 4;
    extra_rows = MATRIX_SIZE % 4;

    // Distribuição das linhas entre os workers
    int start_row = (rank - 1) * rows_per_worker + (rank - 1 < extra_rows ? rank - 1 : extra_rows);
    int end_row = start_row + rows_per_worker + (rank <= extra_rows ? 1 : 0);

    // Cada worker realiza a soma dos elementos das matrizes A e B
    for (i = start_row; i < end_row; i++) {
        for (j = 0; j < MATRIX_SIZE; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }

    // Coleta dos resultados parciais dos workers
    if (rank != 0) {
        MPI_Send(&C[start_row][0], rows_per_worker * MATRIX_SIZE, MPI_INT, 0, 0, MPI_COMM_WORLD);
    } else {
        // O mestre recebe os resultados parciais dos workers e os armazena na matriz C
        for (i = 1; i <= 4; i++) {
            int worker_start_row = (i - 1) * rows_per_worker + (i - 1 < extra_rows ? i - 1 : extra_rows);
            int worker_end_row = worker_start_row + rows_per_worker + (i <= extra_rows ? 1 : 0);
            MPI_Recv(&C[worker_start_row][0], (worker_end_row - worker_start_row) * MATRIX_SIZE, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }

        printf("Matriz C:\n");
        printMatrix(C);
    }

    MPI_Finalize();
    return 0;
}
