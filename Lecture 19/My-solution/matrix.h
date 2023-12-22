#ifndef MATRIX_H
#define MATRIX_H

float * random_matrix(int n);

float * to_column_major(float * M, int n);

float * zero_matrix(int n);

void print_matrix(float * M, int n, bool column_major);

#endif
