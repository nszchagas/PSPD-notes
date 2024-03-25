# Fractal - Cuda - MPI - OMP

## Executando o fractal com cuda

Para executar o código do fractal com o cuda é necessário estar logado em uma máquina da chococino que possua uma __GPU__ (gpu1, gpu2 ou gpu3).

```
$ ssh gpu1
```

Após logado em uma dessas máquinas, é necessário rodar o seguinte comando para compilar seu código cuda:

```
$ nvcc fractal.cu -o fractal
```

Com seu código compilado, basta executar o binário que foi gerado:

```
$ ./fractal 500
```

O fractal será escrito no arquivo `out_julia_normal_cuda.bmp`

## Executando o fractal com cuda, mpi e openmp

Para compilar o código do fractal com o cuda, mpi e openmp é necessário estar logado em uma máquina da chococino que possua uma __GPU__ (gpu1, gpu2 ou gpu3).

```
$ ssh gpu1
```

Após logado em uma dessas máquinas, é necessário rodar o seguinte comando para compilar seu código cuda com o mpi e openmp:

```
$ nvcc -Xcompiler -fopenmp -I/usr/lib/x86_64-linux-gnu/openmpi/include -L/usr/lib/x86_64-linux-gnu/openmpi/lib -lmpi -lgomp fractal_mpi_omp.cu -o fractal
```

Com seu código compilado, basta executar o binário que foi gerado:

```
$ OMP_NUM_THREADS=8 mpirun --host gpu1,gpu2,gpu3,cm1,cm2,cm3,cm4,pos1,pos2 -np 9 fractal 1000
```

O fractal será escrito no arquivo `out_julia_normal_mpi_omp_cuda.bmp`

## Monitoramento

Para monitoriar o funcionamento da aplicação na gpu, é sugerido utilizar o comando `nvidia-smi`

```
$ nvidia-smi
```

Para monitorar de forma contínua, utilize o comando `watch`

```
$ watch -n 1 nvidia-smi
```

## Copiando a imagem

Para extrair a imagem da chococino para seu computador, após a execução do binário, é necessário rodar o seguinte comando:

```
$ scp -P 13508 a<sua_matricula>@chococino.naquadah.com.br:<seu_arquivo>
```

### Referências

> Introdução ao CUDA. Disponível em: https://edisciplinas.usp.br/pluginfile.php/4146828/mod_resource/content/1/MaterialCUDA.pdf
> Documentação CUDA pela NVIDIA. Disponível em: https://docs.nvidia.com/cuda/cuda-c-programming-guide/
> Writing Code That Runs FAST on a GPU. Disponível em: https://www.youtube.com/watch?v=8sDg-lD1fZQ&ab_channel=LowLevelLearning