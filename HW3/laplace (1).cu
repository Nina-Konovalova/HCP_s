

#include <stdio.h>



const long int N = 1<<8;
const long int L = N * N;


__global__ void Init(long int n, float * d_a, float heat)
{
    int x = blockIdx.x, y = threadIdx.x;
    int globalIdx = x * blockDim.x + y;

    if(globalIdx < n) { 
        if(x != 0) {
            d_a[globalIdx] = 0;
        }
        else {
            
            if((y == 0) | (y ==  N-1)) {
                d_a[globalIdx] = 0;
            }
            else {
                d_a[globalIdx] = heat;
            }
        }
    }  
}



__global__ void Step(long int n, float * d_old, float * d_new)
{
    int x = blockIdx.x, y = threadIdx.x;
    int globalIdx = x * blockDim.x + y;
    int upper, down, right, left;

    if(globalIdx < n)
    { 
        if((x != 0) && (x !=  N-1))
        {
            if((y != 0) && (y !=  N-1))
            {
                right = (x + 1) * blockDim.x + y;
                left = (x - 1) * blockDim.x + y;
             
                upper = x * blockDim.x + y+1;
                down = x * blockDim.x + y-1;
             
                d_new[globalIdx] = (d_old[upper] + d_old[down] + d_old[right] + d_old[left]) / 4;
                d_old[globalIdx] = d_new[globalIdx];
            }
        }
    }  
}



// CPU code
int main()
{
    float * d_old;
    float * d_new;



    FILE *fp;
    fp = fopen("heatmap.txt","w");

    cudaMallocManaged(&d_old, sizeof(float)*L);
    cudaMallocManaged(&d_new, sizeof(float)*L);


    Init<<<N,N>>>(L, d_old, 1);
    Init<<<N,N>>>(L, d_new, 1);


    for(int step=0; step < 100000; step++) 

        {
            if (step % 100 == 0) {
                cudaDeviceSynchronize();
            }   
         Step<<<N,N>>>(L, d_old, d_new);   
        }
        
        

    

    cudaDeviceSynchronize();

    for(int j=0; j<N; j++)
    {
        for (int i=0; i<N; i++)
        {
            fprintf(fp, "%f ", d_new[i + j*N]);
        }
        fprintf(fp, "\n");
    }

    cudaDeviceSynchronize();

    cudaFree(d_new);
    cudaFree(d_old);

    fclose(fp);
    return 0;
}