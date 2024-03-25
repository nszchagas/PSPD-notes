#include "somavet.h"

int somavet(CLIENT *clnt, int *x, int n) {
	int  *result;
	vetint  param;

	param.vetint_len = n;
	param.vetint_val = x;
	result = somav_1(&param, clnt);
	if (result == (int *) NULL) {
		clnt_perror (clnt, "falha na chamada");
	} /* fim-if */
	return (*result);
	clnt_destroy (clnt);
} /* fim-somavet */

int main (int argc, char *argv[]) {
	int *ints, n_termos, i, res;
	CLIENT *clnt;

	if (argc < 3) {
		printf ("uso correto: %s servidor num1 num2 ...\n", argv[0]);
		exit (1);
	}
	clnt = clnt_create(argv[1], SOMAVET_PROG, SOMAVET_VERSION, "udp");
	n_termos = argc - 2;
	ints = (int *) malloc(n_termos * sizeof (int));
	for (i=2; i<argc; i++) {
		ints[i-2] = atoi(argv[i]);
	} /* fim-for */
	res = somavet(clnt, ints, n_termos);
	printf("%d", ints[0]);
	for (i=1; i<n_termos; i++) {
		printf(" + %d", ints[i]);
	} /* fim-for */
	printf(" = %d\n", res);
	return(0);
} /* fim main */
