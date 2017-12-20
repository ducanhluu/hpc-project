#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double **UTIL_genArray(int n_h, int n_w) {
    double **arr_out;
    int i, j;

    //-- Allocate the array
	arr_out = (double **)malloc(n_h * sizeof(double *));
    for (i = 0; i < n_h; i++) {
		arr_out[i] = (double *)malloc(n_w * sizeof(double));
	}
    
    srand ( time ( NULL));
    for (i = 0; i < n_h; i++) {
        for (j = 0; j < n_w; j++) {
            //arr_out[x*i+j] = min + rand()%(max-min);
            arr_out[i][j] = (double)rand()/RAND_MAX*2.0-1.0;
        }
    }
    return arr_out;
}

double ***UTIL_genVolume(int n_c, int n_h, int n_w) {
    double ***vol_out;

    //-- Allocate the volume
    vol_out = (double ***)malloc(n_c * sizeof(double **));
    for (int i = 0; i < n_c; i++) {
        vol_out[i] = UTIL_genArray(n_h, n_w);
    }

    return vol_out;
}


void UTIL_printArray(double **arr, int n_h, int n_w){
    int i, j;
    printf("Array of size %dx%d\n", n_h, n_w);
    for (i = 0; i < n_h; i++){
        for (j = 0; j < n_w; j++) {
            printf("%2.5f \t", arr[i][j]);
        }
        printf("\n");
    }
}

void UTIL_printVolume(double ***vol, int n_c, int n_h, int n_w) {
    for (int i = 0; i < n_c; i++) {
        printf("Channel %d\n", i);
        UTIL_printArray(vol[i], n_h, n_w);
        printf("\n");
    }
}

double **UTIL_maxPooling(double **data, int n_h, int n_w, int f_size, int stride) {
	double **output;
    int i, j, k, l;
    double max;

	//-- Compute size of output
	int o_h = (n_h - f_size) / stride + 1;
	int o_w = (n_w - f_size) / stride + 1;
	
	//-- Allocate the array
	output = (double **)malloc(n_h * sizeof(double *));
    for (i = 0; i < n_h; i++) {
		output[i] = (double *)malloc(n_w * sizeof(double));
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

    // printf("Output of data of shape (%d, %d), filter_size = %d, stride = %d\n", n_h, n_w, f_size, stride);
    // for (int i = 0; i< o_h;i++)
    // {
    //     for ( int j = 0;j< o_w;j++)
    //     {
    //         printf("%2.5f \t",output[i][j]);
    //     }
    //     printf("\n");
    // }

    return output;
}

double ***UTIL_maxPoolingLayer(double ***vol, int n_c, int n_h, int n_w, int f_size, int stride) {
    double ***vol_out;
    
    //-- Allocate the volume
    vol_out = (double ***)malloc(n_c * sizeof(double **));
    for (int i = 0; i < n_c; i++) {
        vol_out[i] = UTIL_maxPooling(vol[i], n_h, n_w, f_size, stride);
    }
    
    return vol_out;
}




int main(int argc, char *argv[]) {
    int n_c, n_h, n_w, f_size, stride;
    if (argc != 6) {
        printf("./executed_file n_c n_h n_w filter_size stride \n");
        return 1;
    }
    
    n_c = atoi(argv[1]);
    n_h = atoi(argv[2]);
    n_w = atoi(argv[3]);
    f_size = atoi(argv[4]);
    stride = atoi(argv[5]);

    // double** data = UTIL_genArray(n_h, n_w);
    // UTIL_printArray(data, n_h, n_w);
    
    // printf("\n");

    // double **res = UTIL_maxPooling(data, n_h, n_w, f_size, stride);
    
    double ***vol = UTIL_genVolume(n_c, n_h, n_w);
    UTIL_printVolume(vol, n_c, n_h, n_w);

    int o_h = (n_h - f_size) / stride + 1;
	int o_w = (n_w - f_size) / stride + 1;
    double ***vol_res = UTIL_maxPoolingLayer(vol, n_c, n_h, n_w, f_size, stride);
    printf("Data shape (%d, %d, %d), filter_size = %d, stride = %d\n", n_c, n_h, n_w, f_size, stride);
    printf("=> Output shape: (%d, %d, %d)\n", n_c, o_h, o_w);
    UTIL_printVolume(vol_res, n_c, o_h, o_w);
    return 0;
}
