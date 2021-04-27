

#include <mpi.h>
#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include <time.h>
#include <unistd.h>
#include<algorithm>

using namespace std;



// const_cond rule
void periodic_cond(vector<int> &array, vector<int> &rule){
    vector<int> new_array = array;
    for (int i = 1; i < array.size()-1; i++) {
        if (array[i - 1] == 1 and array[i] == 1 and array[i + 1] == 1) {
                new_array[i] = rule[0];
        }
        else if (array[i - 1] == 1 and array[i] == 1 and array[i + 1] == 0) {
                new_array[i] = rule[1];
        }
        else if (array[i - 1] == 1 and array[i] == 0 and array[i + 1] == 1) {
                new_array[i] = rule[2];
        }
        else if (array[i - 1] == 1 and array[i] == 0 and array[i + 1] == 0) {
                new_array[i] = rule[3];
        }
        else if (array[i - 1] == 0 and array[i] == 1 and array[i + 1] == 1) {
                new_array[i] = rule[4];
        }
        else if (array[i - 1] == 0 and array[i] == 1 and array[i + 1] == 0) {
                new_array[i] = rule[5];
        }
        else if (array[i - 1] == 0 and array[i] == 0 and array[i + 1] == 1) {
                new_array[i] = rule[6];
        }
        else if (array[i - 1] == 0 and array[i] == 0 and array[i + 1] == 0) {
                new_array[i] = rule[7];
        }
    }
    array = new_array;
    array.pop_back();
    array.erase(array.begin());
   
    
}



void printing(int *vec, int N) {
    
    for (int i = 0; i < N; i++) {
            printf("%d ", vec[i]);
    }
    printf("\n");
}

void initialization (vector<int>& init, int N) {
    init.resize(N);
    for (int i = 0; i < N; i++) {
        if (i < N/2 ) {
            init[i] = 0;
        } else {
           init[i] = 1;
        }
    }
}





int main(int argc, char ** argv) {
    int world_size;
    int world_rank;
    ofstream res;          // поток для записи
    res.open("./aut_5.txt");
    
    MPI_Status status;

    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
 

    int iterations = 24;
    int N = 24;
    int n_prank = N/world_size;

    vector<int> init;
   
    initialization (init, n_prank);
    string sLine = "";
    ifstream read;

    read.open("./ca.txt");

    int line_no = 0;
    char strr[16];
    char s[8];

    int r = 19;

    for (int i = 0; i < 256; i++ ) {
         read.getline(strr, 16);
         if (i == r){
            for (int l = 0; l < 16; l++) {
                
                s[l] = strr[l]; 
                
                
            }
           
         }
         
    }
    vector<int> rule(8);
    read.close();
    int k = 0;
    for (int l = 0; l < 16; l++) {
          if (l % 2 == 0) {
          rule[k] = (int)s[l] - 48;
          //cout << l << ' ' << vec[k] << endl; 
          k += 1;
          }
         
    }

    
    for (int i = 0; i < iterations; i++) {    
           

	    init.insert(init.cbegin(),1);
      init.push_back(1);

      if (world_rank == 0) {
          MPI_Send(&init[1],             1, MPI_INT, world_size - 1, 5, MPI_COMM_WORLD);
		      MPI_Recv(&init[init.size()-1], 1, MPI_INT, world_rank + 1, 5, MPI_COMM_WORLD, &status);
	    } else if (world_rank == world_size - 1) {
          MPI_Send(&init[1],             1, MPI_INT, world_rank-1, 5, MPI_COMM_WORLD);
		      MPI_Recv(&init[init.size()-1], 1, MPI_INT, 0,            5, MPI_COMM_WORLD, &status);
	    } else {
          MPI_Send(&init[1],             1, MPI_INT, world_rank - 1, 5, MPI_COMM_WORLD);
		      MPI_Recv(&init[init.size()-1], 1, MPI_INT, world_rank + 1, 5, MPI_COMM_WORLD, &status);
	    }
	    

	    if (world_rank == 0) {
          MPI_Send(&init[init.size()-2], 1, MPI_INT, world_rank + 1, 3, MPI_COMM_WORLD);
		      MPI_Recv(&init[0],             1, MPI_INT, world_size - 1, 3, MPI_COMM_WORLD, &status);
	    } else if (world_rank == world_size - 1) {
          MPI_Send(&init[init.size()-2], 1, MPI_INT, 0,              3, MPI_COMM_WORLD);
		      MPI_Recv(&init[0],             1, MPI_INT, world_rank - 1, 3, MPI_COMM_WORLD, &status);
	    } else {
          MPI_Send(&init[init.size()-2], 1, MPI_INT, world_rank + 1, 3, MPI_COMM_WORLD);
		      MPI_Recv(&init[0],             1, MPI_INT, world_rank - 1, 3, MPI_COMM_WORLD, &status);
	    }
	    


	       
	    //periodic_cond(init);
	    periodic_cond(init, rule);
	    
	    int * all_answer;
	    
	    if (world_rank == 0) {
          all_answer = (int *) malloc(n_prank * world_size * sizeof(int)); 
	    }

	    int *new_init;
	    new_init = (int *) malloc(n_prank * sizeof(int));  
	    for (int i = 0; i < n_prank; i++) {
          new_init[i] = init[i];
	    }
	    
	    MPI_Gather(&init[0],n_prank, MPI_INT, all_answer, n_prank, MPI_INT, 0, MPI_COMM_WORLD);
		       
	    if (world_rank == 0) {
          printing(all_answer, n_prank * world_size);
      }
    }
    
    
    MPI_Finalize();
    res.close();
    return 0;

}