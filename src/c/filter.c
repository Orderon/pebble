#include <pebble.h>
#include "filter.h"
#include "data_acc.h"
#define DIST_PER_STEP 0.5
static int n_steps;
static double distance;
static double filter1_History[7];
  
void handle_acc_data(Data_Acc acc){
  n_steps += find_nb_steps(acc);
  distance += n_steps*DIST_PER_STEP;
}


static int find_nb_steps(Data_Acc acc){
  int nb_steps = 0;
  int time=0;
  for(;time<25;time++){
    //do filter 1
    for(int i=0;i<3;i++){
      filter_lowpass(acc, i, time);
    }
    
    //do norm
    
    //do filter 2
    }
  //findpeaks
  
  //return nb of steps found
  return nb_steps;
}
 //x: 0, y:1, z:2
static double filter_lowpass(Data_Acc acc,int xyz,int time){
 double          
  a1= 0.0244,
  a2 = 0.1465,
  a3 = 0.3662,
  a4 = 0.4882,
  a5 = 0.3662,
  a6 = 0.1465,
  a7 = 0.0244,
  b1= -0.2374,
  b2= 0.7987,
  b3= -0.1130,
  b4= 0.1197,
  b5= -0.0076,
  b6= 0.0019;
  
  
  
return a1; /** data_acc_get_samples(&acc, time, xyz) + a2 * data_acc_get_samples(&acc, time+1, xyz) + 
  a3 * data_acc_get_samples(&acc, time+2, xyz) + a4 * data_acc_get_samples(&acc, time+3, xyz) + 
  a5 * data_acc_get_samples(&acc, time+4, xyz) + a6 * data_acc_get_samples(&acc, time+5, xyz) + 
  a7 * data_acc_get_samples(&acc, time+6, xyz) - b1 * filter1_History[1] - b2 * filter1_History[2];*/
}

static double filter_bandpass(Data_Acc acc,int time){
 double          
  a1= 0.0103,
  a3 = -0.0619,
  a5 = 0.1547,
  a7 = -0.2063,
  a9 = 0.1547,
  a11 = -0.0619,
  a13 = 0.0103,
  b1=-5.6631,
  b2=14.9959,
  b3=-25.2098,
  b4=30.6720,
  b5=-28.6609,
  b6=20.9214,
  b7 = -11.9210,
  b8 = 5.2693,
  b9 = -1.7666,
  b10 = 0.4227,
  b11 = -0.0645
  b12 = 0.0050;
  
  
  
return a1; /** data_acc_get_samples(&acc, time, xyz) + a2 * data_acc_get_samples(&acc, time+1, xyz) + 
  a3 * data_acc_get_samples(&acc, time+2, xyz) + a4 * data_acc_get_samples(&acc, time+3, xyz) + 
  a5 * data_acc_get_samples(&acc, time+4, xyz) + a6 * data_acc_get_samples(&acc, time+5, xyz) + 
  a7 * data_acc_get_samples(&acc, time+6, xyz) - b1 * filter1_History[1] - b2 * filter1_History[2];*/
}

static void findPeaks(void){
  
}