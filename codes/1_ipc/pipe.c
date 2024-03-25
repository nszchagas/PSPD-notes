#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

int main () {

int fd[2], nbytes;
pid_t pid;
char string[] = "Olá mundo";
char readbuffer[80];

pipe(fd);

if ((pid = fork()) == -1){
    perror("Fork");
    exit(1);
}
if (pid==0) {
        close(fd[0]);
        printf("Processo [%d]", getpid());

} else {

}

} 
