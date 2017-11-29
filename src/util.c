#include "util.h"

double **max_pooling(double data**, int w, int h, double filter**, int f_size, int stride) {
	double **output;

	//-- Compute size of output
	int o_h = (h - f_size) / stride;
	int o_w = (w - f_size) / stride;
	
	//-- Allocate the array
	output = (double **)malloc(o_h * sizeof(double *));
    for (i=0; i < o_h; i++) {
		output[i] = (double *)malloc(o_w * sizeof(double));
	}

	

}