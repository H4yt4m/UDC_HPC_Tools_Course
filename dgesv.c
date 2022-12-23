#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include <openblas/lapacke.h>
// #include <mkl_lapacke.h>

double *generate_matrix(int size)
{
  int i;
  double *matrix = (double *)malloc(sizeof(double) * size * size);

  srand(1);

  for (i = 0; i < size * size; i++)
  {
    matrix[i] = rand() % 100;
  }

  return matrix;
}

int is_nearly_equal(double x, double y)
{
  const double epsilon = 1e-5 /* some small number */;
  return abs(x - y) <= epsilon * abs(x);
  // see Knuth section 4.2.2 pages 217-218
}

int check_result(double *bref, double *b, int size)
{
  int i;

  for (i = 0; i < size * size; i++)
  {
    if (!is_nearly_equal(bref[i], b[i]))
      return 0;
  }

  return 1;
}

int my_dgesv(int n, double *a, double *b)

{
  int i, j, k;
  double ratio[n * n];

  // Initialising the augmented matrix
  // https://en.wikipedia.org/wiki/Augmented_matrix
  double augMatrix[n * 2 * n];

  // Filling the augmented matrix from the arrays A and B
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
    {
      augMatrix[i * n + j] = a[i * n + j];
      augMatrix[i * n + n + j] = b[i * n + j];
    }

#pragma omp parallel
  {

#pragma omp for private(j)

    // Gauss Jordan Elimination
    for (i = 0; i < n; i++)
    {
      for (j = 0; j < n; j++)
      {
        // Last minute idea : maybe I could've tried to split cases of j<i, j=i and j>i and then
        // loop unroll ?
        
        if (i != j)
        {
          ratio[i * n + j] = augMatrix[j * n + i] / augMatrix[i * n + i];

          // Actualising the values
          for (k = 0; k < 2 * n; k++)
          {
            augMatrix[j * n + k] += -ratio[i * n + j] * augMatrix[i * n + k];
          }
        }
      }
    }

#pragma omp for private(j)

    // Unique solution
    for (i = 0; i < n; i++)
      for (j = 0; j < n; j++)
      {
        b[i * n + j] = augMatrix[i * n + n + j] / augMatrix[i * n + i];
      }
  }

  return 0;
}

void main(int argc, char *argv[])
{
  int size = atoi(argv[1]);

  double *a, *aref;
  double *b, *bref;

  a = generate_matrix(size);
  aref = generate_matrix(size);
  b = generate_matrix(size);
  bref = generate_matrix(size);

  // Using LAPACK dgesv OpenBLAS implementation to solve the system
  int n = size, nrhs = size, lda = size, ldb = size, info;
  int *ipiv = (int *)malloc(sizeof(int) * size);

  clock_t tStart = clock();
  info = LAPACKE_dgesv(LAPACK_ROW_MAJOR, n, nrhs, aref, lda, ipiv, bref, ldb);
  printf("Time taken by OpenBLAS LAPACK: %.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);
  int *ipiv2 = (int *)malloc(sizeof(int) * size);

  tStart = clock();
  // double start = omp_get_wtime();
  my_dgesv(n, a, b);
  printf("Time taken by my sequential implementation: %.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);
  // printf("Time taken by my parallel implementation: %lfs\n", omp_get_wtime()-start);
  // printf("Time taken by my parallel implementation: %lfs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);

  if (check_result(bref, b, size) == 1)
    printf("Result is ok!\n");
  else
    printf("Result is wrong!\n");

  // To solve some Memcheck errors
  free(a);
  free(aref);
  free(b);
  free(bref);
  free(ipiv);
  free(ipiv2);
}
