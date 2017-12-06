#include "util.h"

int* UTIL_genArray(int x, int y, int min, int max){
    int* arr_out = malloc(sizeof(int)*x*y);
    int i, j;
    for (i = 0; i < x; i++) {
        for (j = 0; j < y; j++) {
            arr_out[x*i+j] = min + rand()%(max-min);
        }
    }
    return arr_out;
}

void UTIL_printArray(int x, int y, int* arr){
    int i, j;
    printf("Array of size %dx%d\n", x, y);
    for (i = 0; i < x; i++){
        for (j = 0; j < y; j++) {
            printf("%d ", arr[x*i+j]);
        }
        printf("\n");
    }
}

double **UTIL_maxPooling(double **data, int w, int h, int f_size, int stride) {
	double **output;
    int i, j;
    int max;

	//-- Compute size of output
	int o_h = (h - f_size) / stride;
	int o_w = (w - f_size) / stride;
	
	//-- Allocate the array
	output = (double **)malloc(o_h * sizeof(double *));
    for (i = 0; i < o_h; i++) {
		output[i] = (double *)malloc(o_w * sizeof(double));
	}

    for (i = 0; i + stride < o_h; i += stride) {
        for (j = 0; j + stride < o_w; j += stride) {
            max = 0;
            for (k = 0; k < stride; k++) {
                for (l = 0; l < stride; l++) {
                    if (data[k][l] >= max) {
                        max = data[k][l];
                    }
                }
            }
            output[i][j] = max;
        }
    }

    return output;
}
