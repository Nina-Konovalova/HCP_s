
#include <stdio.h>
// kernel

const long int size = 600;
const long int N = size*size;


__global__ void Init(long int n, float * d_a)
{
    int globalIdx = threadIdx.z * blockDim.x * blockDim.y + threadIdx.y * blockDim.x + threadIdx.x;

    if(globalIdx < n) d_a[globalIdx] = globalIdx;
}


__global__ void Blur(long int n,  float * d_old, float * d_new)
{
    int x = blockIdx.x;
    int y = threadIdx.x;
    int globalIdx = x * blockDim.x + y;
    int up, down, right, left;
    int u_l, d_l, u_r, d_r;

    if(globalIdx < n)
    { 
        if((x != 0) && (x !=  size-1))
        {
            if((y != 0) && (y !=  size-1))
            {
                d_r   = (x + 1) * blockDim.x + y - 1;
                right = (x + 1) * blockDim.x + y;
                u_r   = (x + 1) * blockDim.x + y + 1;
                
                d_l =  (x - 1) * blockDim.x + y - 1;
                left = (x - 1) * blockDim.x + y;
                u_l =  (x - 1) * blockDim.x + y + 1;

                up = x * blockDim.x + y+1;
                down = x * blockDim.x + y-1;
                                
                d_new[globalIdx] = (d_old[globalIdx] + d_old[up] + d_old[down] + d_old[left] +\
                                    d_old[right] + d_old[u_l] + d_old[d_l] + d_old[u_r] + d_old[d_r]) / 9.0;
                d_old[globalIdx] = d_new[globalIdx];
            }
        }
    }  
}



int main()
{
    float * d_r;
    float * d_g;
    float * d_b;
    float * d_new;
   
    cudaMalloc(&d_r, sizeof(float)*N);
    cudaMalloc(&d_g, sizeof(float)*N);
    cudaMalloc(&d_b, sizeof(float)*N);
    cudaMalloc(&d_new, sizeof(float)*N);

    float * h_r = (float *)malloc(sizeof(float)*N);
    float * h_g = (float *)malloc(sizeof(float)*N);
    float * h_b = (float *)malloc(sizeof(float)*N);


    FILE *init_r, *init_g, *init_b, *out_r, *out_g, *out_b;
    init_r = fopen("cat_r.txt","r");
    init_g = fopen("cat_g.txt","r");
    init_b = fopen("cat_b.txt","r");

    out_r = fopen("blur_cat_r.txt","w");
    out_g = fopen("blur_cat_g.txt","w");
    out_b = fopen("blur_cat_b.txt","w");


    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            fscanf(init_r, "%f", &h_r[i*size + j]);
            fscanf(init_g, "%f", &h_g[i*size + j]);
            fscanf(init_b, "%f", &h_b[i*size + j]);
        }
    }

    cudaMemcpy(d_r, h_r, sizeof(float)*N, cudaMemcpyHostToDevice);
    cudaMemcpy(d_g, h_g, sizeof(float)*N, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, h_b, sizeof(float)*N, cudaMemcpyHostToDevice);


    for(int i = 0; i < 250; i++) {
        
        Blur<<<size,size>>>(N, d_r, d_new);
 
        Blur<<<size,size>>>(N, d_g, d_new);

        Blur<<<size,size>>>(N, d_b, d_new);

    }

    cudaMemcpy(h_r, d_r, sizeof(float)*N, cudaMemcpyDeviceToHost);
    cudaMemcpy(h_g, d_g, sizeof(float)*N, cudaMemcpyDeviceToHost);
    cudaMemcpy(h_b, d_b, sizeof(float)*N, cudaMemcpyDeviceToHost);

    cudaDeviceSynchronize();

    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            fprintf(out_r, "%f ", h_r[i*size + j]);
            fprintf(out_g, "%f ", h_g[i*size + j]);
            fprintf(out_b, "%f ", h_b[i*size + j]);
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

    free(h_r);
    free(h_g);
    free(h_b);

    return 0;
}