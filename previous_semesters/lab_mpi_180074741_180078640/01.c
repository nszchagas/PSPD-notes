// Caio Martins - 180074741
// Yuri Alves - 180078640

#include <stdio.h>
#include <mpi.h>
#include <unistd.h>
#include <sys/types.h>

#define TAG 0
#define MESTRE 0

int main(int argc, char **argv) {

        int rank, size;
        int valor = 505050;
        int resp;
        char hostname[10];
        int hostname_len;

        MPI_Init(&argc, &argv);

        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Get_processor_name(hostname, &hostname_len);

        //printf("Processo [%d/%d] ---> hello world\n", rank, size);

        if(rank == 0) {
                printf("Rank[0/'%s']: sending token to 1\n", hostname);
                MPI_Send(&valor, 1, MPI_INT, 1 , TAG, MPI_COMM_WORLD); //(mens>
                MPI_Recv(&resp, 1, MPI_INT, size - 1, TAG, MPI_COMM_WORLD, MPI>
                printf("[%d/'%s'] Mestre -> recv: %d\n", rank, hostname, resp);

        } else {

                int recebe_rank = rank - 1;

                int envia_rank = rank + 1;

                if(rank == size -1)
                        envia_rank = 0;

                MPI_Recv(&valor, 1, MPI_INT, recebe_rank, TAG, MPI_COMM_WORLD,>
                printf("Rank[%d/'%s']: recebeu o token e está enviando para %d>


                MPI_Send(&valor, 1, MPI_INT, envia_rank, TAG, MPI_COMM_WORLD);
        }

        MPI_Finalize();
        return 0;
}


