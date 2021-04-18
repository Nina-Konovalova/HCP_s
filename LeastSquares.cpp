
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <cmath>
#include <random>
#include <iterator>



using namespace std;

void data(double *x, double *y, int N, double a, double b) {
  double eps = 1e-15;

 // double a = 3.27;
 // double b = -2.2;
  
 // cout << "a:" << ' ' << a << endl;
 // cout << "b:" << ' ' << b << endl;
  // adding gaussian noise
  
  const double mean = 0;
  const double sttd = 0.5;
  std::default_random_engine generator;
  std::normal_distribution<double> dist(mean, sttd);

  //generating data
  for (int i = 0; i < N; i++) {
    
     y[i] = a*x[i] + b + dist(generator);
  }


}

void rand_init_vector(double * vector, size_t N) {
    srand(time(NULL));

    for (int i = 0; i < N; i++) {
        vector[i] = 10.0*(double)rand() / RAND_MAX;
     }

}

double * malloc_vector(size_t N)
{
    double * vector = (double *)malloc(N * sizeof(double));

    return vector;
}




int main() {
   int N = 1e5;

   
   double* y = new double[N];
   double* x = new double[N];
   double a = 3.3;
   double b = 2.2;

   x =  malloc_vector(N);
   rand_init_vector(x,N);

   
   data(x,y,N, a,b );

  // for (int i = 0; i < N; i++) {
//	   cout << x[i] << ' ';
 //  }
 //  cout << endl;
   double a_pred = 0, b_pred = 0;
   double start, end;
   double x_1 = 0, y_1 = 0; 
   double x2_1 = 0, xy_1 = 0;
   
   start = omp_get_wtime();
#pragma omp parallel for reduction (+:x_1,y_1,x2_1,xy_1)
   for (int i = 0; i < N; i++) {
	   x_1 += x[i];
	   y_1 += y[i];
	   x2_1 += x[i]*x[i];
	   xy_1 += x[i]*y[i];
   }
  // cout << x_1 << ' ' << y_1 << endl;
   x_1 = x_1/double(N);
   y_1 = y_1/double(N);
   x2_1 = x2_1/double(N);
   xy_1 = xy_1/double(N);

   a_pred = (xy_1 - x_1*y_1) / (x2_1 - x_1*x_1);

   b_pred = y_1 - a_pred*x_1;
   end = omp_get_wtime();

   cout << "Predicted:a " << a_pred << " " << "Real a: "<< a << endl;
   cout << "Predicted:b " << b_pred << " " << "Real b: "<< b << endl;
   cout << "Time ellapsed " << (end - start) << endl;


return 0;
}
