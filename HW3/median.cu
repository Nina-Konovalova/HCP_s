
#include <stdio.h>
// kernel

const long int size = 600;
const long int N = size*size;

__global__ void Hello(void)
{

    long int globalIdx = blockDim.x*threadIdx.y+ threadIdx.x;
    //printf("hello from bx = %d\tby = %d\ttx = %d\tty = %d\tgi = %d\n", 
    //    blockIdx.x, blockIdx.y, threadIdx.x, threadIdx.y, globalIdx);
    globalIdx += 1;
}

__global__ void Init(long int n, float * d_a)
{
    int globalIdx = threadIdx.z * blockDim.x * blockDim.y + threadIdx.y * blockDim.x + threadIdx.x;

    if(globalIdx < n) d_a[globalIdx] = globalIdx;
}





__global__ void Median(long int n, float * d_old, float * d_new, float * d_neigh)
{
    int x = blockIdx.x;
    int y = threadIdx.x;
    int globalIdx = x * blockDim.x + y;
    float stay;

    if(globalIdx < n)
    { 
        if((x != 0) && (x !=  size-1))
        {
            if((y != 0) && (y !=  size-1))
            {
                d_neigh[0] = d_old[globalIdx];
             
                d_neigh[1] = d_old[(x - 1) * blockDim.x + y];
             
                d_neigh[2] = d_old[(x - 1) * blockDim.x + y + 1];
                d_neigh[3] = d_old[x * blockDim.x + y + 1 ];
                d_neigh[4] = d_old[(x + 1) * blockDim.x + y + 1];
             
                d_neigh[5] = d_old[(x + 1) * blockDim.x + y ];
             
                d_neigh[6] = d_old[(x + 1) * blockDim.x + y - 1];
                d_neigh[7] = d_old[x * blockDim.x + y - 1];
                d_neigh[8] = d_old[(x - 1) * blockDim.x + y - 1];
             
                // подумать над сортировкой
                
                for(int i = 0; i < 9; ++i) // i - номер прохода
                {            
                    for(int j = 0; j < 9; ++j) // внутренний цикл прохода
                    {     
                        if (d_neigh[j + 1] < d_neigh[j]) 
                        {
                           stay = d_neigh[j];
                           d_neigh[j ] =  d_neigh[j+1];
                           d_neigh[j+1] = stay;
                        }
                   }
                 }
                
                d_new[globalIdx] = d_neigh[4];
                d_old[globalIdx] = d_new[globalIdx];
            }
        }
    }  
}

// CPU code
int main()
{

    float * h_r = (float *)malloc(sizeof(float)*N);
    float * h_g = (float *)malloc(sizeof(float)*N);
    float * h_b = (float *)malloc(sizeof(float)*N);

    float * d_r;
    float * d_g;
    float * d_b;
    float * d_new;
    float * d_neigh;

    cudaMalloc(&d_r, sizeof(float)*N);
    cudaMalloc(&d_g, sizeof(float)*N);
    cudaMalloc(&d_b, sizeof(float)*N);
    cudaMalloc(&d_new, sizeof(float)*N);
    cudaMalloc(&d_neigh, sizeof(float)*9);

    FILE *init_r, *init_g, *init_b, *out_r, *out_g, *out_b;
    init_r = fopen("cat_r.txt","r");
    init_g = fopen("cat_g.txt","r");
    init_b = fopen("cat_b.txt","r");

    out_r = fopen("med_cat_r.txt","w");
    out_g = fopen("med_cat_g.txt","w");
    out_b = fopen("med_cat_b.txt","w");

    
    for(int i=0; i<size; i++)
    {
        for(int j=0; j<size; j++)
        {
            fscanf(init_r, "%f", &h_r[i*size + j]);
            fscanf(init_g, "%f", &h_g[i*size + j]);
            fscanf(init_b, "%f", &h_b[i*size + j]);
        }
    }

    cudaMemcpy(d_r, h_r, sizeof(float)*N, cudaMemcpyHostToDevice);
    cudaMemcpy(d_g, h_g, sizeof(float)*N, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, h_b, sizeof(float)*N, cudaMemcpyHostToDevice);

    for(int i=0; i<500; i++)
    {
        Median<<<size,size>>>(N, d_r, d_new, d_neigh);
        
        Median<<<size,size>>>(N, d_g, d_new, d_neigh);
        
        Median<<<size,size>>>(N, d_b, d_new, d_neigh);
    }

    cudaMemcpy(h_r, d_r, sizeof(float)*N, cudaMemcpyDeviceToHost);
    cudaMemcpy(h_g, d_g, sizeof(float)*N, cudaMemcpyDeviceToHost);
    cudaMemcpy(h_b, d_b, sizeof(float)*N, cudaMemcpyDeviceToHost);

    cudaDeviceSynchronize();


    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            fprintf(out_r, "%f ", h_r[i*size+j]);
            fprintf(out_g, "%f ", h_g[i*size+j]);
            fprintf(out_b, "%f ", h_b[i*size+j]);
        }
        
        fprintf(out_r, "\n"); 
        fprintf(out_g, "\n"); 
        fprintf(out_b, "\n"); 
    }

    cudaDeviceSynchronize();
 
   
    fclose(init_r);
    fclose(init_g);
    fclose(init_b);
    
    fclose(out_r);
    fclose(out_g);
    fclose(out_b);
    
    cudaFree(d_r);
    cudaFree(d_g);
    cudaFree(d_b);
    cudaFree(d_new);
    cudaFree(d_neigh);
 
    free(h_r);
    free(h_g);
    free(h_b);


    return 0;
}