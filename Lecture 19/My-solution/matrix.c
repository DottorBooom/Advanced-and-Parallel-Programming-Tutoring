#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "matrix.h"

float * random_matrix(int n)
{
  float * m = (float *)malloc(n * n * sizeof(float));
  for (int i = 0; i < n*n; i++) {
    m[i] = (float) rand() / RAND_MAX;
  }
  // azzeramento della diagonale
  for (int i = 0; i < n; i++) {
    m[i * n + i] = 0;
  }
  return m;
}

float * to_column_major(float * M, int n)
{
  float * MT = zero_matrix(n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      MT[j * n + i] = M[i * n + j];
    }
  }
  return MT;
}

float * zero_matrix(int n)
{
  float * m = (float *)malloc(n * n * sizeof(float));
  for (int i = 0; i < n*n; i++) {
    m[i] = 0.0;
  }
  return m;
}

void print_matrix(float * M, int n, bool column_major)
{
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (column_major) {
	printf("%2.3f ", M[j * n + i]);
      } else {
	printf("%2.3f ", M[i * n + j]);
      }
    }
    printf("\n");
  }
}
