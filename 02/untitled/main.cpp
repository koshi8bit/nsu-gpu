#include <iostream>

using namespace std;

int main()
{
    cout << "Hello World!" << endl;

    size_t iter_max = 10000;
    const size_t m = 100;
    const size_t n = 200;

    double **A = new double* [m];
    double **Anew = new double* [m];

    for(size_t i=0; i<m; i++)
    {
        A[i] = new double [n];
        Anew[i] = new double [n];
    }

    for(size_t i=0; i<m; i++)
    {
        for(size_t j=0; j<n; j++)
        {
            A[i][j] = i*n + j;
            cout << A[i][j] << " ";
        }
        cout << endl;
    }

    // #pragma acc data copy(A) create(Anew)
    size_t iter = 0;
    double err = 0;
    double tol = 1e-5;
    while(err<tol && iter < iter_max)
    {
        iter++;
        // #pragma acc kernels
        for(size_t i=1; i<m-1; i++)
        {
            for(size_t j=1; j<n-1; j++)
            {
                Anew[i][j] = 0.25 * (A[i+1][j] + A[i-1][j] + A[i][j-1] + A[i][j+1]);
                err = max(err, Anew[i][j] - A[i][j]);
            }

            A = Anew;

            if (iter % 100 == 0 || iter == 1)
            {
                cout << iter << err << endl;
            }
        }
    }


    return 0;
}
