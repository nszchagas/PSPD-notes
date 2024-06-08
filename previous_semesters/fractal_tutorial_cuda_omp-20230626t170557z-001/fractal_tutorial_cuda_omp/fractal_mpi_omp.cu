#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <cuda.h>
#include <cuda_runtime.h>
#include <string.h>

#define OUTFILE "out_julia_normal_mpi_omp_cuda.bmp"


__device__ void compute_julia_pixel(int x, int y, int largura, int altura, float tint_bias, unsigned char *pixel_array, int index)
{
  // "Zoom in" to a pleasing view of the Julia set
  float X_MIN = -1.6, X_MAX = 1.6, Y_MIN = -0.9, Y_MAX = +0.9;
  float float_y = (Y_MAX - Y_MIN) * (float)y / altura + Y_MIN;
  float float_x = (X_MAX - X_MIN) * (float)x / largura + X_MIN;
  // Point that defines the Julia set
  float julia_real = -.79;
  float julia_img = .15;
  // Maximum number of iteration
  int max_iter = 300;
  // Compute the complex series convergence
  float real = float_y, img = float_x;
  int num_iter = max_iter;
  while ((img * img + real * real < 2 * 2) && (num_iter > 0))
  {
    float xtemp = img * img - real * real + julia_real;
    real = 2 * img * real + julia_img;
    img = xtemp;
    num_iter--;
  }

  // Paint pixel based on how many iterations were used, using some funky colors
  float color_bias = (float)num_iter / max_iter;
  pixel_array[index] = (num_iter == 0 ? 200 : (char)(-500.0 * pow(tint_bias, 1.2) * pow(color_bias, 1.6)));
  pixel_array[index + 1] = (num_iter == 0 ? 100 : (char)(-255.0 * pow(color_bias, 0.3)));
  pixel_array[index + 2] = (num_iter == 0 ? 100 : (char)(255 - 255.0 * pow(tint_bias, 1.2) * pow(color_bias, 3.0)));
} /*fim compute julia pixel */

void compute_julia_pixel2(int x, int y, int largura, int altura, float tint_bias, unsigned char *rgb)
{
  // "Zoom in" to a pleasing view of the Julia set
  float X_MIN = -1.6, X_MAX = 1.6, Y_MIN = -0.9, Y_MAX = +0.9;
  float float_y = (Y_MAX - Y_MIN) * (float)y / altura + Y_MIN;
  float float_x = (X_MAX - X_MIN) * (float)x / largura + X_MIN;
  // Point that defines the Julia set
  float julia_real = -.79;
  float julia_img = .15;
  // Maximum number of iteration
  int max_iter = 300;
  // Compute the complex series convergence
  float real = float_y, img = float_x;
  int num_iter = max_iter;
  while ((img * img + real * real < 2 * 2) && (num_iter > 0))
  {
    float xtemp = img * img - real * real + julia_real;
    real = 2 * img * real + julia_img;
    img = xtemp;
    num_iter--;
  }

  // Paint pixel based on how many iterations were used, using some funky colors
  float color_bias = (float)num_iter / max_iter;
  rgb[0] = (num_iter == 0 ? 200 : (char)(-500.0 * pow(tint_bias, 1.2) * pow(color_bias, 1.6)));
  rgb[1] = (num_iter == 0 ? 100 : (char)(-255.0 * pow(color_bias, 0.3)));
  rgb[2] = (num_iter == 0 ? 100 : (char)(255 - 255.0 * pow(tint_bias, 1.2) * pow(color_bias, 3.0)));
} /*fim compute julia pixel */

__global__ void compute(int altura_inicio, int largura, int altura_total, unsigned char *pixel_array)
{
  int i = blockIdx.x + altura_inicio;
  unsigned char rgb1, rgb2, rgb3;
  int index = blockIdx.x * largura * 3;

  if (blockIdx.x >= altura_total) {
    return;
  }

  for (int j = 0; j < largura * 3; j += 3)
  {
    compute_julia_pixel(j / 3, i, largura, altura_total, 1.0, pixel_array, index + j);
  }
}

int write_bmp_header(MPI_File file, int largura, int altura)
{

  unsigned int row_size_in_bytes = largura * 3 +
                                   ((largura * 3) % 4 == 0 ? 0 : (4 - (largura * 3) % 4));

  // Define all fields in the bmp header
  char id[3] = "BM";
  unsigned int filesize = 54 + (int)(row_size_in_bytes * altura * sizeof(char));
  short reserved[2] = {0, 0};
  unsigned int offset = 54;

  unsigned int size = 40;
  unsigned short planes = 1;
  unsigned short bits = 24;
  unsigned int compression = 0;
  unsigned int image_size = largura * altura * 3 * sizeof(char);
  int x_res = 0;
  int y_res = 0;
  unsigned int ncolors = 0;
  unsigned int importantcolors = 0;

  // Write the bytes to the file, keeping track of the
  // number of written "objects"
  size_t ret = 0;
  MPI_Status status;
  ret += MPI_File_write(file, id, 2, MPI_CHAR, &status);
  ret += MPI_File_write(file, &filesize, 1, MPI_INT, &status);
  ret += MPI_File_write(file, reserved, 2, MPI_SHORT, &status);
  ret += MPI_File_write(file, &offset, 1, MPI_INT, &status);
  ret += MPI_File_write(file, &size, 1, MPI_INT, &status);
  ret += MPI_File_write(file, &largura, 1, MPI_INT, &status);
  ret += MPI_File_write(file, &altura, 1, MPI_INT, &status);
  ret += MPI_File_write(file, &planes, 1, MPI_SHORT, &status);
  ret += MPI_File_write(file, &bits, 1, MPI_SHORT, &status);
  ret += MPI_File_write(file, &compression, 1, MPI_INT, &status);
  ret += MPI_File_write(file, &image_size, 1, MPI_INT, &status);
  ret += MPI_File_write(file, &x_res, 1, MPI_INT, &status);
  ret += MPI_File_write(file, &y_res, 1, MPI_INT, &status);
  ret += MPI_File_write(file, &ncolors, 1, MPI_INT, &status);
  ret += MPI_File_write(file, &importantcolors, 1, MPI_INT, &status);
 
  // Success means that we wrote 17 "objects" successfully
  return (ret != 17);
} /* fim write bmp-header */

int main(int argc, char *argv[])
{
  int n;
  char hostname[100];
  unsigned char *pixel_array, rgb[3], *pixel_array_dev;
  int area = 0, largura = 0, altura = 0;
  int altura_node, altura_inicio, altura_fim;
  MPI_File file;

  int rank, group_size;

  if ((argc <= 1) || (atoi(argv[1]) < 1))
  {
    fprintf(stderr, "Entre 'N' como um inteiro positivo! \n");
    return -1;
  }

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &group_size);
  printf("%d\n", MPI_File_open(MPI_COMM_WORLD, OUTFILE, MPI_MODE_WRONLY | MPI_MODE_CREATE, MPI_INFO_NULL, &file));

  n = atoi(argv[1]);

  altura_node = n / group_size;
  altura_inicio = rank * altura_node;
  altura_fim = (rank + 1) == group_size ? n : altura_inicio + altura_node;
  altura = altura_fim - altura_inicio;
  largura = 2 * n;
  area = altura * largura * 3;

  pixel_array = (unsigned char *)malloc(area * sizeof(unsigned char));

  int hostname_len = 0;
  MPI_Get_processor_name(hostname, &hostname_len);
  printf("%s: Computando linhas de pixel %d até %d, para uma área total de %d\n",hostname, 0, n - 1, area);

  if (strstr(hostname, "gpu")) {
    cudaMalloc(&pixel_array_dev, area * sizeof(unsigned char));

    compute<<<altura, 1>>>(altura_inicio, largura, n, pixel_array_dev);

    cudaMemcpy(pixel_array, pixel_array_dev, area * sizeof(unsigned char), cudaMemcpyDeviceToHost);
  } else {
#pragma omp parallel for shared(pixel_array) private(rgb)
    for (int i = altura_inicio; i < altura_fim; i++)
    {
      int index = (i - altura_inicio) * largura * 3;
      for (int j = 0; j < largura * 3; j += 3)
      {
        compute_julia_pixel2(j / 3, i, largura, n, 1.0, rgb);

        pixel_array[index + j] = rgb[0];
        pixel_array[index + j + 1] = rgb[1];
        pixel_array[index + j + 2] = rgb[2];
      }
    }
  }

  // escreve o cabeçalho do arquivo
  MPI_Status status;
  MPI_Offset offset = 54;

  if (rank == 0)
  {
    write_bmp_header(file, largura, n);
    MPI_File_write_at(file, offset, pixel_array, area, MPI_CHAR, &status);
  }
  else
  {
    offset += (altura_inicio - 1) * largura * 3;
    MPI_File_write_at(file, offset, pixel_array, area, MPI_CHAR, &status);
  }

  free(pixel_array);
  if (strstr(hostname, "gpu")) {
    cudaFree(pixel_array_dev);
  }

  MPI_File_close(&file);
  MPI_Finalize();
  return 0;
}
