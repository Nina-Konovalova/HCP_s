#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

float dotprod(float * a, float * b, size_t N)
{
    int i, tid;
    float sum;
    omp_set_dynamic(0);
    omp_set_num_threads(5);
 //   tid = omp_get_thread_num();

#pragma omp parallel for private(tid) reduction(+:sum) schedule(static)

    for (i = 0; i < N; ++i)
    {   
	tid = omp_get_thread_num();
        sum += a[i] * b[i];
  //      printf("tid = %d i = %d\n", tid, i);
	printf("Num of thread %d\n", tid);
    }

    return sum;
}

int main (int argc, char *argv[])
{
    const size_t N = 10;
    int i,tid;
    float sum;
    float a[N], b[N];

    omp_set_dynamic(0);
    omp_set_num_threads(3);

    sum = 0.0;
#pragma omp parallel for schedule(static) //private(a,b)
    for (i = 0; i < N; ++i)
    {
	    tid = omp_get_thread_num();
            printf("tid = %d i = %d\n", tid, i);
	    a[i] = b[i] = (double)i;
    }
//#pragma opm end parallel
    

//#pragma omp parallel shared(sum)
    sum = dotprod(a, b, N);

    printf("Sum = %f\n",sum);

    return 0;
}
