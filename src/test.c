#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double **UTIL_genArray(int height, int width) {
    double **arr_out;
    int i, j;

    //-- Allocate the array
	arr_out = (double **)malloc(height * sizeof(double *));
    for (i = 0; i < height; i++) {
		arr_out[i] = (double *)malloc(width * sizeof(double));
	}
    
    srand ( time ( NULL));
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            //arr_out[x*i+j] = min + rand()%(max-min);
            arr_out[i][j] = (double)rand()/RAND_MAX*2.0-1.0;
        }
    }
    return arr_out;
}

void UTIL_printArray(int height, int width, double** arr){
    int i, j;
    printf("Array of size %dx%d\n", height, width);
    for (i = 0; i < height; i++){
        for (j = 0; j < width; j++) {
            printf("%2.5f \t", arr[i][j]);
        }
        printf("\n");
    }
}

double **UTIL_maxPooling(double **data, int w, int h, int f_size, int stride) {
	double **output;
    int i, j, k, l;
    double max;

	//-- Compute size of output
	int o_h = (h - f_size) / stride + 1;
	int o_w = (w - f_size) / stride + 1;
	
	//-- Allocate the array
	output = (double **)malloc(o_h * sizeof(double *));
    for (i = 0; i < o_h; i++) {
		output[i] = (double *)malloc(o_w * sizeof(double));
	}

    //-- Initialize the array
    for (int i = 0; i< o_h;i++)
    {
        for ( int j = 0;j< o_w;j++)
        {
            output[i][j] = 0.0;
        }
    }

    for (i = 0; i < o_h; i++) {
        for (j = 0; j < o_w; j++) {
            max = -100000.0;
            for (k = 0; k < f_size; k++) {
                for (l = 0; l < f_size; l++) {
                    if (data[i * stride + k][j * stride + l] >= max) {
                        //printf("%f\n", data[k][l]);
                        max = data[i * stride + k][j * stride + l];
                    }
                }
            }
            output[i][j] = max;
        }
    }

    printf("Output of data of shape (%d, %d), filter_size = %d, stride = %d\n", h, w, f_size, stride);
    for (int i = 0; i< o_h;i++)
    {
        for ( int j = 0;j< o_w;j++)
        {
            printf("%f\t",output[i][j]);
        }
        printf("\n");
    }

    return output;
}




int main(int argc, char *argv[]) {
    int height, width, f_size, stride;
    if (argc != 5) {
        printf("./executed_file height width filter_size stride \n");
        return 1;
    }
    
    height = atoi(argv[1]);
    width = atoi(argv[2]);
    f_size = atoi(argv[3]);
    stride = atoi(argv[4]);

    double** data = UTIL_genArray(height, width);
    UTIL_printArray(height, width, data);
    
    printf("\n");

    double **res = UTIL_maxPooling(data, height, width, f_size, stride);
    
    return 0;
}
