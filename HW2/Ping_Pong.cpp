
#include <mpi.h>
#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <cmath>
#include <string>
#include <fstream>

using namespace std;


void arrray(vector<int> &b,const int &N){
   for (int i = 0; i < N; i++) {
           b.push_back(i);
   }
}



int random_index(int aray_size, unsigned int &seed){
   int elem = rand_r(&seed) % aray_size;
   return elem;
}

void creating_mess(vector<int> &b, vector<int> &pass_mess, int &elem, int &i) {
    // choosing random element from array
   unsigned int seed = 0;
   pass_mess[i] = (b[elem]);
  // b.erase(b.begin() + elem);
}

void printing(vector<int> &vec, string &name) {
    cout << name << endl;
    for (int i = 0; i < vec.size(); i++) {
            printf("%d ", vec[i]);
    }
    printf("\n");
}
int main(int argc, char ** argv) {
    int world_rank;
    int world_size;
    MPI_Status status;
    int ierr;

    //FILE *res;
    //res = fopen("./results1.txt", "a");
    ofstream res;          // поток для записи
    res.open("./results.txt");

    double start, end, last;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    
    start = MPI_Wtime();
   // num of itterations 
   int N = 20;
   
   // size of sent message
   int sizze = 10000000;

   unsigned int seed = 0;

   // vector of processed
   vector<int> b;
   arrray(b,world_size);
   unsigned int aray_size = b.size();

   // vector of message
   vector<int> message(sizze);
   vector<vector<int>> message1(N);

   string a;


   int sender, reciver;
   sender = random_index(aray_size, seed);
   aray_size = b.size();

   int m = 0;
   creating_mess(b, message, sender,m);

  for (m = 0; m < N; m++) {
  //while (b.size() > 0) {
     aray_size = b.size();
     do {
        reciver = random_index(aray_size, seed);
        //cout << reciver << ' ' << sender << endl;
     } while (reciver == sender);
     
     if (world_rank == sender){

       MPI_Ssend(&message[0], message.size(), MPI_INT, b[reciver], 12, MPI_COMM_WORLD);
      

     } else if (world_rank == b[reciver]) {
       message1[b[reciver]].resize(sizze);
       MPI_Recv(&message1[b[reciver]][0], message.size(), MPI_INT, sender, 12, MPI_COMM_WORLD, &status);
       
     }

   creating_mess(b, message, reciver, m);
   sender = message[m];
   
   }
   //printf("Hello! size %d rank %d\n", world_size, world_rank);
   //a = "Message";
   //printing(message1[world_rank],a);
   end = MPI_Wtime();
   int arr_size = sizeof(std::vector<int>) + (sizeof(int) * sizze);//(int)sizeof(buffer[0])*steps;
   last = end - start;
   double mess_time = last/N;
   //printf("Size of message: %d\t Iterations: %d\t Total time:%f\t Message time:%f\t Bandwidth:%f\n", arr_size, N, last, mess_time , arr_size/mess_time);
   cout << arr_size << "\t" << N << "\t" << last << "\t" << mess_time << "\t" << arr_size/mess_time << endl;
   //fclose(res);
   res.close();
   MPI_Finalize();
   return 0;
}                              