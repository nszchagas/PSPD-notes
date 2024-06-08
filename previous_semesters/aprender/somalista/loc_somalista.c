#include <stdio.h>
#include <stdlib.h>
/* lista_encadeada local - ll_loc.c */
struct lista {
  	int		num;
	struct lista	*prox;
};
typedef struct lista lista;

void imprime_lista(lista *ap_lista) {

  while (ap_lista) {
    printf("%d ",ap_lista->num);
    ap_lista =ap_lista->prox;
  } /* fim-while */
  printf("\n");
} /* fim procedure */

void imprime_soma(lista *ap_lista) {
  int result = 0;
	while (ap_lista) {
	   result   += ap_lista->num;
	   ap_lista  = ap_lista->prox;
	} /* fim-while */
	printf("A soma eh ... %d\n",result);
} /* fim - print_sum */

int main( int argc, char *argv[]) {
  int 		n_termos,i;
  lista 	*ap, *inicio_lista, *apaux;

  if (argc<2) {
    fprintf(stderr,"Uso correto: %s num1 num2 ...\n",argv[0]);
    exit(0); }

  n_termos = argc-1;
  inicio_lista = (lista *) malloc(sizeof(lista));
  ap = inicio_lista;
  for (i=0; i<n_termos; i++) {
     ap->num  = atoi(argv[i+1]);
     ap->prox = (lista *) malloc(sizeof(lista));
     apaux    = ap;
     ap       = ap->prox;
  } /* fim-for */

  free(apaux->prox);
  apaux->prox=NULL;

  imprime_lista(inicio_lista);
  imprime_soma(inicio_lista);
  return(0);
} /* fim programa */
