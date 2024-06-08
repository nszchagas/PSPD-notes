#include <stdio.h>
#include <mpi.h>
#define MASTER 0
#define SLAVE 1 //nao precisa se tiverem varios
#define TAG 0

int main(int argc, char *argv[]){
    int nprocs, rank;
    int valor;
    // MPI_Status st;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    if(rank == MASTER) {
        int valor = 5;
        MPI_Send(&valor, 1, MPI_INT, SLAVE, TAG, MPI_COMM_WORLD);
    } else {
        // var, tamanho da var, recebe de quem, tag, comunicador, status (não necessária, pode usar o &st)
        MPI_Recv(&valor, 1, MASTER, TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Slave [%d] recebe valor %d\n", rank, valor);
    }

    return 0;

}