#include <iostream>

using namespace std;

void printt(double **A, size_t m, size_t n)
{
	//std::copy
	
    for(size_t i=0; i<m; i++)
    {
        for(size_t j=0; j<n; j++)
        {
            printf("%-5.1f ", A[i][j]);
        }
        printf("\n");
    }
	//printf("\n"); 
}

void init(double **A, size_t m, size_t n)
{
	A[0][0] = 10;
	A[m][0] = 20;
	A[0][n] = 0;
	A[m][n] = 10;

	

}

int main()
{
    cout << "Hello World!" << endl;

    size_t iter_max = 5;
    const size_t m = 3;
    const size_t n = 3;

    double **A = new double* [m];
    double **Anew = new double* [m];

    for(size_t i=0; i<m; i++)
    {
        A[i] = new double [n];
        Anew[i] = new double [n];
    }


	/*
    for(size_t i=0; i<m; i++)
    {
        for(size_t j=0; j<n; j++)
        {
            cout << Anew[i][j] << " ";
        }
        cout << endl;
    } */

	printf("default\n");
	init(A, m, n);
	init(Anew, m, n);

	printt(A, m, n);
    printf("\n");
 

	// return 0;
    //#pragma acc data copy(A) create(Anew)
    size_t iter = 0;
    double tol = 1e-5;
    double err = tol+1.;
    while((err>tol) && (iter<iter_max))
    {
        iter++;
		err = 0;
        //#pragma acc kernels
        for(size_t i=1; i<m-1; i++)
        {
            for(size_t j=1; j<n-1; j++)
            {
                Anew[i][j] = 0.25 * (A[i+1][j] + A[i-1][j] + A[i][j-1] + A[i][j+1]);
                err = max(err, Anew[i][j] - A[i][j]);
            }

            // A = Anew;
			printt(Anew, m, n); 

            for(size_t ii=0; ii<m; ii++)
            {
                for(size_t jj=0; jj<n; jj++)
                {
                    A[ii][jj] = Anew[ii][jj];
                }
            }
			printt(A, m, n); 
			printf("\n");

            //if (iter % 100 == 0 || iter == 1)
            {
                printf("iter %-5d; err %-10.6f\n", iter, err);
            }

				
        }
    }


    return 0;
}
