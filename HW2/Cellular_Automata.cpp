

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

void printing(vector<int> &vec) {
    
    for (int i = 0; i < vec.size(); i++) {
            printf("%d ", vec[i]);
    }
    printf("\n");
}

void periodic_cond(vector<int> &array){
    vector<int> new_array = array;

    if ( (array[array.size()-1] == 0 and array[0] == 1 and  array[1] == 0)  or (array[array.size()-1] == 1 and array[0] == 0 and  array[1] == 1) or\
         (array[array.size()-1] == 0 and array[0] == 0 and  array[1] == 0)  or (array[array.size()-1] == 1 and array[0] == 1 and  array[1] == 1)) {
        new_array[0] = 0;
    } else {
        new_array[0] = 1;
    }
    
    for (int i = 1; i < array.size(); i++) {
        if ((array[i-1] == 0 and array[i] == 1 and  array[i+1] == 0)  | (array[i-1] == 1 and array[i] == 0 and  array[i+1] == 1) | \
            (array[i-1] == 0 and array[i] == 0 and  array[i+1] == 0) |  (array[i-1] == 1 and array[i] == 1 and  array[i+1] == 1)){
          new_array[i] = 0;
        } else {
           new_array[i] = 1;
        }
    }
   
   if ((array[array.size()-2] == 0 and array[array.size()-1] == 1 and  array[0] == 0)  | (array[array.size()-2] == 1 and array[array.size()-1] == 0 and  array[0] == 1) |\
       (array[array.size()-2] == 0 and array[array.size()-1] == 0 and  array[0] == 0)  | (array[array.size()-2] == 1 and array[array.size()-1] == 1 and  array[0] == 1)) {
        new_array[array.size()-1] = 0;
    } else {
        new_array[array.size()-1] = 1;
    }
    array = new_array;
    //printing(new_array);
    
}

void const_cond(vector<int> &array) {
    vector<int> new_array = array;
    for (int i = 1; i < array.size()-1; i++) {
        if ((array[i-1] == 1 and array[i+1] == 1) or (array[i-1] == 1 and array[i] == 0) or (array[i-1]==0 and array[i] == 0 and array[i+1] == 0) or (array[i-1]==0 and array[i] == 1 and array[i+1] == 0)){
          new_array[i] = 1;
    } else {
        new_array[i] = 0;
    }
    }  
    array = new_array;  
}




int main(){
    ofstream res;          // поток для записи
    res.open("./aut_1.txt");
   
    vector<int> init = {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1};
    int N ;
    printing(init);
    N = init.size();

    for (int k = 0; k < N; k++) {
        periodic_cond(init);
        printing(init);
    }
    res.close();
    return 0;
}