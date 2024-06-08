/*
	ALUNOS
	
Gabriela da Gama Pivetta - 180052845
Murilo Gomes de Souza - 180025601
Ítalo Alves Guimarães - 180113666 

*/


#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mpi.h"

int main(int argc, char **argv )
{
	char message[20];
	int i,rank, size, type=99;
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
 	int hostname_len = 20;
 	char hostname[20];
 	MPI_Get_processor_name(hostname, &hostname_len);
	if(rank == 0) {
		strcpy(message, "token");
		printf( "Rank[%d/%s]: sending token to 1\n", rank, hostname);
		MPI_Send(message, 13, MPI_CHAR, 1, type, MPI_COMM_WORLD);
		MPI_Recv(message, 13, MPI_CHAR, 3,type, MPI_COMM_WORLD, &status);
	}
 	else {
 		MPI_Recv(message, 13, MPI_CHAR, rank - 1,type, MPI_COMM_WORLD, &status);
		printf( "Rank[%d/%s]: sending token to %d\n", rank, hostname, (rank +1)%4);
		MPI_Send(message, 13, MPI_CHAR, (rank + 1)%4, type, MPI_COMM_WORLD);
 	}

	MPI_Finalize();



// para rodar
// mpicc ciclo_hosts_mpi.c -oversubscribe -o ciclo
// mpirun -np 4 -hosts cm1, cm2, cm3 ./ciclo

}
