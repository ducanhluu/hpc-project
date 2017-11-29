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
