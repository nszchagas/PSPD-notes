#include "somavet.h"

int * somav_1_svc(vetint *argp, struct svc_req *rqstp) {
	static int  result;
	int 		 i;

	printf("Requisicao de soma de um vetor de inteiros... \n");
	result = 0;
	for (i=0; i < argp->vetint_len; i++) {
		result += argp->vetint_val[i];
	} /* fim-for */
	printf("Soma = %d\n", result);
	return &result;
} /* fim somav_1_svc */
