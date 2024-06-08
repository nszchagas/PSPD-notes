/*
	ALUNOS
	
Gabriela da Gama Pivetta - 180052845
Murilo Gomes de Souza - 180025601

*/

#include <stdio.h>
#include <string.h>
#include <mpi.h>
#include <stdlib.h>

int main(int argc, char ** argv) {
	int rank, proc_count;
	MPI_Status st;
	
	MPI_Init(&argc, &argv);	
	
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &proc_count);
	if (rank != 0) {
		int v[15];
		MPI_Recv(v, 15, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &st);
		while (v[0] != -1) {
			int offset = rand() % 15;
			for (int i = 0; i < offset && v[i] != 100 ; i++) {
				printf("%d ", v[i]);
			}
			printf("\n");
			MPI_Send(&offset, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
			MPI_Recv(v, 15, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &st);
		}
	}
	else {
		int v[101];
		for (int i =0; i< 101 ; i++) {
			v[i] = i;
		}
		int index = 0;
		int proc = 0;
		while (index < 100) {
			int offset = 0;
			proc = (proc + 1) % proc_count;
			if (proc == 0) proc++;
			MPI_Send(v + index, 15, MPI_INT, proc, 0, MPI_COMM_WORLD);
			MPI_Recv(&offset, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &st);
			index += offset;
		}
		// Send -1 to sinalize that printing has ended
		for (int i = 1; i < proc_count; i++) {
			int endFlag = -1;
			MPI_Send(&endFlag, 15, MPI_INT, i, 0, MPI_COMM_WORLD);
		}
	}
	
	MPI_Finalize();
}
