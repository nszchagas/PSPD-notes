#include <stdio.h>
#include <stdlib.h>

int soma(int *x, int n) {
	int i, result;

	printf("Requisicao para adicao de %d numeros\n", n);
	result=0;
	for (i=0; i<n; i++) {
	  result += x[i];
	} /* fim-for */
	return (result);
} /* fim vadd */

int main( int argc, char *argv[]) {
  int *ints, n_termos, i, res;

  if (argc<2) {
    fprintf(stderr,"Uso correto: %s num1 num2 ...\n",argv[0]);
    exit(0); }

    /* recupera os numeros que devem ser adicionados */
  n_termos = argc-1;
  ints = (int *) malloc(n_termos * sizeof( int ));
  if (ints==NULL) {
    fprintf(stderr,"Erro na alocacao de memoria\n");
    exit(0); }
/* preenche a estrutura dinamica com os valores informados pelo usuario */
  for (i=1;i<argc;i++) {
    ints[i-1] = atoi(argv[i]);
  } /* fim-for */
/* imprime o resultado da soma */
  res = soma(ints, n_termos);
  printf("%d",ints[0]);
  for (i=1; i<n_termos; i++) {
    printf(" + %d",ints[i]);
  } /* fim-for */
  printf(" = %d\n",res);
  return(0);
} /* fim programa principal */
