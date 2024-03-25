#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]){

	MPI_Init(&argc, &argv);
	int meurank, size;
	MPI_Comm_rank(MPI_COMM_WORLD, &meurank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	if(meurank == 0){
		for(int i=1; i<size; i++){
			int send_var = i * 10;
			printf("send var = %d\n", send_var);
			MPI_Send(&send_var, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
			printf("Enviado do %d para o %d\n", meurank, i);
		}
	}
	else {	
		int recebido;
		MPI_Recv(&recebido, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		printf("Recebido no %d, o valor %d\n", meurank, recebido);
	
	}
	
	
	printf("Ola mundo %d\n", meurank);
	

	return 0;
}
