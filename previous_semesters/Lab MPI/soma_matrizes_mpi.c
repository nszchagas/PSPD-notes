/*
	ALUNOS
	
Gabriela da Gama Pivetta - 180052845
Murilo Gomes de Souza - 180025601

*/


#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mpi.h"

int main(int argc, char **argv )
{
	char message[20];
	int i, j,rank, size, type=99;
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
 	int hostname_len = 20;
 	char hostname[20];
 	MPI_Get_processor_name(hostname, &hostname_len);
 	
 	if (size != 5) {
 		printf("Numero de processos invalidos (deve ser 5)\n");
 		MPI_Finalize();
 	}
 	
 	int mat1[4][4], mat2[4][4], mat3[4][4];
 	
 	for (i = 0; i < 4; i = i + 1)
 	       for (j = 0; j < 4; j = j + 1){
 	       		mat1[i][j] = rand() % 100;
 	       		mat2[i][j] = rand() % 100;
 	       }
 	       
 	
	if(rank == 0) {
		for (i = 0; i < 4; i = i + 1) {
	 	       for (j = 0; j < 4; j = j + 1){
	 	       		printf("%d ", mat1[i][j]);
	 	       }
	 	       printf("\n");
	 	}
	 	printf("\n");
	 	
	 	for (i = 0; i < 4; i = i + 1) {
	 	       for (j = 0; j < 4; j = j + 1){
	 	       		printf("%d ", mat2[i][j]);
	 	       }
	 	       printf("\n");
	 	}
	 	printf("\n");
	
		MPI_Recv(mat3[0], 4, MPI_INT, 1,type, MPI_COMM_WORLD, &status);
		MPI_Recv(mat3[1], 4, MPI_INT, 2,type, MPI_COMM_WORLD, &status);
		MPI_Recv(mat3[2], 4, MPI_INT, 3,type, MPI_COMM_WORLD, &status);
		MPI_Recv(mat3[3], 4, MPI_INT, 4,type, MPI_COMM_WORLD, &status);
		for (i = 0; i < 4; i = i + 1) {
	 	       for (j = 0; j < 4; j = j + 1){
	 	       		printf("%d ", mat3[i][j]);
	 	       }
	 	       printf("\n");
	 	}
	}
 	else {
 		int vec[4];
 		for (i = 0; i < 4; i++) {
 			vec[i] = mat1[rank-1][i] + mat2[rank-1][i];
 		}
		MPI_Send(vec, 4, MPI_INT, 0, type, MPI_COMM_WORLD);
 	}

	MPI_Finalize();
	
// para rodar
// mpicc soma_matrizes_mpi.c -o matriz
// mpirun -np 5 ./matriz

}
