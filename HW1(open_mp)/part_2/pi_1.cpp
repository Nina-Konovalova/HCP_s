#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <vector>
#include <omp.h>
using namespace std;

const size_t N = 1e8;

vector<unsigned int> seeds(8);

void seedThreads() {
    int my_thread_id;
    unsigned int seed;
//    vector<unsigned int> seeds(8);
#pragma omp parallel private (seed, my_thread_id)
{
    my_thread_id = omp_get_thread_num();

//create seed on thread using current time
    unsigned int seed = (unsigned) time(NULL);

//munge the seed using our thread number so that each thread has its
//own unique seed, therefore ensuring it will generate a different set of numbers
    seeds[my_thread_id] = (seed & 0xFFFFFFF0) | (my_thread_id + 1);

    printf("Thread %d has seed %u\n", my_thread_id, seeds[my_thread_id]);
}

}


int main()
{

int i, throws = 1000000, insideCircle = 0;
double randX, randY, pi;
int tid;
unsigned int seed;
omp_set_num_threads(8);
seedThreads();

double start,end;

start = omp_get_wtime();

#pragma omp parallel shared(seeds,throws) private(randX,randY,seed) num_threads(8) reduction(+:insideCircle)
{
tid = omp_get_thread_num();
seed = seeds[tid];
srand(seed);

#pragma omp for
for (i = 0; i < throws; ++i)
{
randX = rand_r(&seed) / (double) RAND_MAX;
randY = rand_r(&seed) /(double) RAND_MAX;
if (randX * randX + randY * randY < 1) {
insideCircle += 1;
}
}
}

pi = 4.0 * insideCircle / throws;
end = omp_get_wtime();
cout << "pi = " << pi << endl;

printf("Time of parallel pi monte carlo is %lf\n", end - start);


return 0;
}
