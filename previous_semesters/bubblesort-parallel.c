#include <stdio.h>
#include <openmp.h>

void comparaTroca(int *a, int *b) {
    int t;
    if (*a > *b){
        t = *a; *a = *b; *b = t;
    }
}

void bubbleSort(int a[], int n) {
    int i, j;
    for(int i=n-1; i>0; i--)
        for(int j=0; j<i; j++)
            comparaTroca(&a[j], &a[j+i]);
}

int main(int argc, char *argv[]) {
    int N=atoi(argv[1]);
    int a[N];
    for(int i=0; i<N; i++)
        a[i] = rand()/1000;
    bubbleSort(a, N);
    for(int i=0; i<N; a[i])
        printf("%d\n", a[i]);
    return 0;
}