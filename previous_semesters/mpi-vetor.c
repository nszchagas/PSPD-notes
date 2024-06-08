#include <stdio.h>
#include <mpi.h>
#define MASTER 0
#define SLAVE 1 //nao precisa se tiverem varios
#define TAG 0

int main(int argc, char *argv[]){
    int nprocs, rank;
    int vet[5];
    // MPI_Status st;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    if(rank == MASTER) {
        for(int i=0; i<5; i++)
            vet[i] = i*2;
        MPI_Send(vet, 5, MPI_INT, SLAVE, TAG, MPI_COMM_WORLD);
    } else {
        // var, tamanho da var, recebe de quem, tag, comunicador, status (não necessária, pode usar o &st)
        MPI_Recv(vet, 5, MPI_INT, MASTER, TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Valores recebidos");
        for(int i = 0; i < 5; i++) {
            printf(" Slave [%d] recebe valor %d\n", rank, vet[i]);
        }
        // printf("\nSlave [%d] recebe valor %d\n", rank, vet);
    }
    MPI_Finalize();
    return 0;

}
