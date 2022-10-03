#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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
  int size = n;

  // Initialising the augmented matrix
  // https://en.wikipedia.org/wiki/Augmented_matrix

  double **augMatrix = (double **)malloc(sizeof(double *) * size);

  for (int i = 0; i < n; i++)
  {
    augMatrix[i] = (double *)malloc(sizeof(double) * 2 * size);
  }

  // Filling the augmented matrix from the arrays A and B
  
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
    {
      augMatrix[i][j] = a[i * n + j];
    }

  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
    {
      augMatrix[i][n + j] = b[i * n + j];
    }

  // Gauss Jordan Elimination

  for (int i = 0; i < n; i++)
  {
    if (augMatrix[i][i] == 0.0)
    {
      printf("Mathematical Error! The zero is located at the element index %d in the diagonal of matrix A \n", i);
      exit(0);
    }
    for (int j = 0; j < n; j++)
    {
      if (i != j)
      {
        // Calculating the ratio or the pivot

        double ratio = augMatrix[j][i] / augMatrix[i][i];

        // Actualising the values

        for (int k = 0; k < 2 * n; k++)
        {
          augMatrix[j][k] = augMatrix[j][k] - ratio * augMatrix[i][k];
        }
      }
    }
  }

  // Unique solution

  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
    {
      b[i * n + j] = augMatrix[i][n + j] / augMatrix[i][i];
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
  my_dgesv(n, a, b);
  printf("Time taken by my implementation: %.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);

  if (check_result(bref, b, size) == 1)
    printf("Result is ok!\n");
  else
    printf("Result is wrong!\n");
}
