#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <math.h>
#include <cstdio>

#define N 1e8

int main(int argc, char *argv[])
{
    float *a;
    a = (float*)malloc(N * sizeof(float));

#pragma acc kernels
    for(int i=0; i<N; i++)
    {
        a[i] = sinf((i*M_PI)/180.0);
    }

    float s = 0;
    for(int i=0; i<N; i++)
    {
          s += a[i] - sinf((i*M_PI)/180.0);
    }
    float e=s/100000000.0;
    printf("e = %f.10\n", e);

    return 0;
}
