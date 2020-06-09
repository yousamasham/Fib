#include "bmp.h"
#include <stdio.h>
#include <stdlib.h>


int fib(int n, int x, int y, int step, RGB b, RGB f, int w, int h, RGB* image);
double getTime(int);

int main(int argc, char** argv)
{
    if (argc != 8) {
        printf("Usage: ./fib n x y step  width height filename\n");
        return -1;
    }

    int n, x, y, step, width, height;

    n = atoi(argv[1]);
    x = atoi(argv[2]);
    y = atoi(argv[3]);
    step = atoi(argv[4]);
    width = atoi(argv[5]);
    height = atoi(argv[6]);
    if (n < 3) {
        printf("n must be >= 3\n");
        return -2;
    }
    if (step < 2) {
        printf("step must be >= 2\n");
        return -3;
    }
    if (x < 0 || x > width) {
        printf("x must be in [0,%d]\n", width - 1);
        return -4;
    }
    if (y < 0 || y > height) {
        printf("y must be in [0,%d]\n", height - 1);
        return -5;
    }
    char* file = argv[7];

    printf("n=%d, x,y=%d,%d, step=%d, %dX%d -> %s\n",
        n, x, y, step, width, height, file);

    RGB* image = malloc(sizeof(RGB) * width * height);
    if (!image) {
        printf("malloc failed to allocate image memory\n");
        return -3;
    }

    RGB  bcolor = {255,255,255}; /* background color */
    RGB  fcolor = {0,0, 0} ;  /* foreground color */
    double time = getTime(2);
    int steps = fib(n, x, y, step, bcolor, fcolor, width, height, image);
    time = getTime(2)-time;
    if (time < 0.01)
        printf("fib(%d) done in < 0.01 seconds\n", n);
    else
      printf("fib(%d) done in %.1f s,  %d steps/sec\n", n, time, (int)(steps/time));
    if (!steps)
      printf("fib failed\n");
    else
        saveBMP(file, width, height, image);
    free(image);
    return !steps;
}
