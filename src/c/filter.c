#include <pebble.h>
#include "filter.h"
#include "data_acc.h"
#define DIST_PER_STEP 0.5
static int n_steps;
static double distance;
  
  
static void handle_acc_data(){
  n_steps += find_nb_steps();
  distance += n_steps*DIST_PER_STEP;
}


static int find_nb_steps(){
  int nb_steps = 0;
  //do filter 1
  
  //do norm
  
  //do filter 2
  
  //findpeaks
  
  //return nb of steps found
  return nb_steps;
}
 
static double filter_lowpass(char STRUCT_TODO,int time){
 double             //10^-5*
  a1=0.0000000495, //0.0495
  a2=0.000002972, //0.2972
  a3=0.00000743,  //0.743
  a4=0.000009907, //0.9907
  a5=0.000007430, //0.7430
  a6=0.000002972, //0.2972
  a7=0.000000495, //0.0495
  b1=-5.2719,
  b2=11.6199,
  b3=-13.7027,
  b4=9.1161,
  b5=-3.2434,
  b6=0.4821;
  
return a1 * newInput + a2 * newInput + a3 * newInput + a4 * newInput + a5 * newInput + a6 * newInput + a7 * newInput - b1 * outputHistory[0] - b2 * outputHistory[1];
}


static void findPeaks(void){
  
}