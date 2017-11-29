#include "util.h"

int main(int argc, char **argv){
    int x, y, min, max;
    if (argc < 5) return 1;
    x = atoi(argv[1]);
    y = atoi(argv[2]);
    min = atoi(argv[3]);
    max = atoi(argv[4]);
    int* arr = UTIL_genArray(x, y, min, max);
    UTIL_printArray(x, y, arr);
    return 0;
}
