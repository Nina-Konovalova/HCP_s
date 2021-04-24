#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
//#include <chrono>
//#include <iostream>

//using namespace std;
//using namespace std::chrono;




void zero_init_matrix(double ** matrix, size_t N)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            matrix[i][j] = 0.0;
        }
    }
}

void rand_init_matrix(double ** matrix, size_t N)
{
    srand(time(NULL));
    unsigned int seed = 0;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            matrix[i][j] = rand_r(&seed) / RAND_MAX;
        }
    }
}

double ** malloc_matrix(size_t N)
{
    double ** matrix = (double **)malloc(N * sizeof(double *));
    
    for (int i = 0; i < N; ++i)
    {   
        matrix[i] = (double *)malloc(N * sizeof(double));
    }
    
    return matrix;
}

void free_matrix(double ** matrix, size_t N)
{
    for (int i = 0; i < N; ++i)
    {   
        free(matrix[i]);
    }
    
    free(matrix);
}

int main()
{
  // omp_set_dynamic(0);
  // omp_set_num_threads(1);

    unsigned int seed = 0;
    const size_t N = 1000; // size of an array

    double start, end;   
 
    double ** A, ** B, ** C; // matrices

   // printf("Starting:\n");

  



    A = malloc_matrix(N);
    B = malloc_matrix(N);
    C = malloc_matrix(N);    

    rand_init_matrix(A, N);
    rand_init_matrix(B, N);
    zero_init_matrix(C, N);

  

//
//  matrix multiplication algorithm
//

    int i,j,k;
    


/////////////////////////////////////////////////////////////////////

    
    zero_init_matrix(C, N);

    omp_set_dynamic(0);
    omp_set_num_threads(3);

    //ijk parallel algorithm
    start = omp_get_wtime();
#pragma omp parallel for collapse (3) num_threads(10) shared(A,B,C)// schedule (static)
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
	    for (k =0; k < N; k++) {
		    C[i][j] += A[i][k]*B[k][j];
	    }
        }
    }
    

    end = omp_get_wtime();
    zero_init_matrix(C, N);
   printf("%d", omp_get_num_threads());
   printf("Time elapsed (ijk) parallel: %f seconds.\n", (double)(end - start));
   
   
    zero_init_matrix(C, N);

    //kji parallel algorithm
   double  start1 = omp_get_wtime();
#pragma omp parallel for collapse (3) num_threads(10) shared(A,B,C)// schedule (static)
            for (k = 0; k < N; k++) {
                    for (j = 0; j < N; j++) {
                            for (i =0; i < N; i++) {
                                    C[i][j] += A[i][k]*B[k][j];
                            }
                    }
            }
    
   double  end1 = omp_get_wtime();

    printf("Time elapsed (kij) parallel: %f seconds.\n", (double)(end1 - start1));

     

    zero_init_matrix(C, N);

    //kji parallel algorithm
    start = omp_get_wtime();


    #pragma omp parallel shared(A,B,C) num_threads(10)  private(j,i,k)
    {
    #pragma omp for collapse (3)//  schedule(static)
           // auto start = high_resolution_clock::now()
           // start = clock();
            for (j = 0; j < N; j++) {
                    for (i = 0; i < N; i++) {
                            for (k =0; k < N; k++) {
                                    C[i][j] += A[i][k]*B[k][j];
                            }
                    }
            }
    }
    end = omp_get_wtime();

    printf("Time elapsed (jik) parallel: %f seconds.\n", (double)(end - start));

    free_matrix(A, N);
    free_matrix(B, N);
    free_matrix(C, N);

    return 0;
}
