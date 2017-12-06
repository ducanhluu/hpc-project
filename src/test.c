// #include <stdio.h>
#include <stdio.h>
#include <stdlib.h>

// int* UTIL_genArray(int x, int y, int min, int max){
//     int* arr_out = malloc(sizeof(int)*x*y);
//     int i, j;
//     for (i = 0; i < x; i++) {
//         for (j = 0; j < y; j++) {
//             arr_out[x*i+j] = min + rand()%(max-min);
//         }
//     }
//     return arr_out;
// }

// void UTIL_printArray(int x, int y, int* arr){
//     int i, j;
//     printf("Array of size %dx%d\n", x, y);
//     for (i = 0; i < x; i++){
//         for (j = 0; j < y; j++) {
//             printf("%d ", arr[x*i+j]);
//         }
//         printf("\n");
//     }
// }

double **UTIL_maxPooling(double **data, int w, int h, int f_size, int stride) {
	double **output;
    int i, j, k, l;
    int max;

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
            max = 0;
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
    int x, y, min, max;
    if (argc < 5) return 1;
    x = atoi(argv[1]);
    y = atoi(argv[2]);
    min = atoi(argv[3]);
    max = atoi(argv[4]);
    // int* arr = UTIL_genArray(x, y, min, max);
    // UTIL_printArray(x, y, arr);
    double **data;
    data = (double **)malloc(4 * sizeof(double *));
    for (int i = 0; i < 4; i++) {
		data[i] = (double *)malloc(4 * sizeof(double));
    }
    
    int k = 0;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            data[i][j] = k;
            k++;
        }
    } 
   
    for (int i = 0; i< 4;i++)
    {
        for ( int j = 0;j< 4;j++)
        {
            printf("%f\t",data[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    double **res = UTIL_maxPooling(data, 4, 4, 2, 2);

    //printf("Hello World %f\n", data[1][1]);
    return 0;
}
