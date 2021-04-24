#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[])
{
    const size_t N = 10;
    const size_t chunk = 3;

    int i, tid;
    float a[N], b[N], c[N];
    omp_set_dynamic(0);
    omp_set_num_threads(5);

#pragma omp parallel for  schedule (static)
    for (i = 0; i < N; ++i)
    {   
//	tid = omp_get_thread_num();
        a[i] = b[i] = (float)i;
    }

    omp_set_dynamic(0);
    omp_set_num_threads(2);
     
       
#pragma omp parallel for// schedule (static)
	for (i = 0; i < N; ++i)
        {   
            tid = omp_get_thread_num();
            c[i] = a[i] + b[i];
            printf("tid = %d, c[%d] = %f\n", tid, i, c[i]);
        }
      
    return 0;
}
