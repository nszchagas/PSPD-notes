#define VERSION_NUMBER 1

struct lista {
	int 		num;
	struct lista	*prox;
};
typedef struct lista lista;

program SOMALISTA_PROG {
   version SOMALISTA_VERSION {
     int SOMAL(lista) = 1;
   } = 1;
} = 0x5005;
