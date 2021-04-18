#include <stdio.h>
#include <time.h>
#include <omp.h>
int main()
{
    const size_t N = 100000;
    double step;
    double start,end;
    double x, pi, sum = 0.;

    step = 1. / (double)N;
  //  omp_set_dynamic(0);
  //  omp_set_num_threads(4);
    int i;
    start = omp_get_wtime();
    #pragma omp parallel private(i,x)
    {
    #pragma omp for reduction (+:sum) schedule (static)

    for (int i = 0; i < N; ++i)
    {
        x = (i + 0.5) * step;
        sum += 4.0 / (1. + x * x);
    }
    }
    pi = step * sum;
    end = omp_get_wtime();
    printf("pi = %.16f\n", pi);
    printf("Time elapsed: %f seconds.\n", (double)(end - start));

    return 0;
}
