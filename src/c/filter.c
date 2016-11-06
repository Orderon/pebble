/*---------------------------------------------------------------------------
filter.c
Authors: Thomas Triquet, Cyrill Baumann
Version: 1.0
Date: 06.11.2016
---------------------------------------------------------------------------*/


#include <pebble.h>
#include "filter.h"
#include "data_acc.h"
#define DIST_PER_STEP 0.5
static int n_steps;
static double distance;
  

/*
executes lowpass filter order 7
Inputs: int i: position of the most recent value in the array
        double acc[7]: 7 most recent accelerometer values
        double facc[7]: 7 last outputs of this filter
Output: double result: the filtered value of acc[i], the most recent accelerometer value 
*/
double filter_lowpass(int i, double acc[7],double facc[7]){
/* variable declaration for filter*/
 static double          
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
  
  /*executes lowpass filter of type:
    b*OUTPUTs = a*INPUTs with a's and b's declared above*/
  double result = a1* acc[(i+7)%7] + a2 * acc[(i+6)%7] +  a3 * acc[(i+5)%7] + a4 * acc[(i+4)%7] + 
  a5 * acc[(i+3)%7] + a6 * acc[(i+2)%7] +  a7 * acc[(i+1)%7] -
  b1 * facc[(i+6)%7] - b2 * facc[(i+5)%7] - b3 * facc[(i+4)%7] - b4 * facc[(i+3)%7] - 
  b5 * facc[(i+2)%7] - b6 * facc[(i+1)%7];
  
return result;
}


/*
executes bandpass filter order 7
Inputs: int i: position of the most recent value in the array
        double nfacc[7]: 13 most recent filtered accelerometer and normalized values
        double facc[7]: 12+NSAMPLES last outputs of this filter, used are only last 13, rest can be empty
Output: double result: the filtered value of nfacc[i], the most recent accelerometer value 
*/
double filter_bandpass(int i,double nfacc[13],double fnfacc[12+NSAMPLES]){
/* variable declaration for filter*/
 static double          
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
  b11 = -0.0645,
  b12 = 0.0050;
  
  
  
  /*executes bandpass filter of type:
    b*OUTPUTs = a*INPUTs with a's and b's declared above*/
  double result = a1* nfacc[(i+13)%13] +  a3 * nfacc[(i+11)%13] +  a5 * nfacc[(i+9)%13] +
  a7 * nfacc[(i+7)%13] +  a9 * nfacc[(i+5)%13] +  a11 * nfacc[(i+3)%13] +  a13 * nfacc[(i+1)%13] -
  b1 * fnfacc[i+11] - b2 * fnfacc[i+10] - b3 * fnfacc[i+9] - b4 * fnfacc[i+8] - 
  b5 * fnfacc[i+7] - b6 * fnfacc[i+6] - b7 * fnfacc[i+5] - b8 * fnfacc[i+4] -
  b9 * fnfacc[i+3] - b10 * fnfacc[i+2] - b11 * fnfacc[i+1] - b12 * fnfacc[i+0];
  return result;
}

/*
finds peaks in the given array of consecutive data
function should be called to evaluate consecutive data sets not undependent ones.
Inputs: double fnfacc[7+NSAMPLES]: most recent filtered data
        double moy: mean of the last 7+NSAMPLES samples
Output: int result: number of peaks found 
*/
int findPeaks(double fnfacc[7+NSAMPLES], double moy){
  //keep ilastpeak over function initialisations;
  static int ilastpeak = 0;
  int i = 0;
  int delta_i = 0;
  double result=0;
  double llast_temp=0; 
  double last_temp=fnfacc[5]; //initialize last two variables from previous set.
  double temp=fnfacc[6];
  for(i=7;i<7+NSAMPLES;i++){ 
    
    //actualise temporary variables (go forward in time by 1 step)
    llast_temp = last_temp;
    last_temp = temp;
    temp = fnfacc[i];
    delta_i = i-ilastpeak;
    
    //make sure delta_i >= 0
    if(delta_i<0)
      delta_i += 6+NSAMPLES;
    
    //if the middle value is higher than the two others, then add a peak. Further filtering of noise through minimal threshold between the 3 values.
    //as well as a general threshhold of the needed acceleration and a minimal distance in time between two consecutive peaks
     if(last_temp>(llast_temp+5) && last_temp>(temp+5) && (last_temp > 1250) && (delta_i>8))
      {
         result += 1;
         ilastpeak = i;
      }
  }
  if (result == 0)
    ilastpeak = 0;
  
    return result;
}
