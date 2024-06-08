#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main () {
    int i = 0, total=100000000, wait=200000, ini=0, pid, fim=total;
    
    long np = sysconf(_SC_NPROCESSORS_ONLN);
    
    printf("%ld processors\n\n", np);


    pid = fork(); // pid = 0 => processo filho

    if (pid < 0) 
    {
	    printf("Não teve sucesso ao criar outro processo");
	    return 1; 

    }
    if (pid == 0) { // filho
	    ini=0;
	    fim = total / 2;

        printf("Filho começando com ini=%d e fim=%d\n", ini, fim);
    }
    else {
	    ini = total /2;
	    fim = total;

        printf("Pai começando com ini=%d e fim=%d\n", ini, fim);
    }
        

    while (ini++<fim) 
    	for (int j=0; j++; j<2000);

    printf("end all\n");

return 0;
} 
