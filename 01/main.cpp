#include <math.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstdlib>

int main(int argc, char *argv[])
{
    const int N = 1e6;
    //float *a = new float[N];
    float *a = (float*)malloc(N * sizeof(float));

#pragma acc kernels
    for(int i=0; i<N; i++)
    {
        a[i] = sin(i*M_PI/180.0);
    }

    float s = 0.0;
    for(int i=0; i<N; i++)
    {
        s += abs(a[i] - sin(i*M_PI/180.0));
    }
    float e=0.0;
    e = s / N;
    printf("%f\n", e);

    return 0;
}
