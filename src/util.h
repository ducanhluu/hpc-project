#ifndef __UTIL_H__
#define __UTIL_H__
#include <stdio.h>
#include <stdlib.h>

// Params: x is number of lines - y is number of columns
int* UTIL_genArray(int x, int y, int min, int max);
void UTIL_printArray(int x, int y, int* arr);

double **UTIL_maxPooling(double **data, int w, int h, int f_size, int stride);

#endif
