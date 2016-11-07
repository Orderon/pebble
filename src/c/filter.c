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
  double result = a1 * acc[(i+7)%7] + a2 * acc[(i+6)%7] +  a3 * acc[(i+5)%7] + a4 * acc[(i+4)%7] + 
                  a5 * acc[(i+3)%7] + a6 * acc[(i+2)%7] +  a7 * acc[(i+1)%7] -
                  b1 * facc[(i+6)%7] - b2 * facc[(i+5)%7] - b3 * facc[(i+4)%7] - b4 * facc[(i+3)%7] - 
                  b5 * facc[(i+2)%7] - b6 * facc[(i+1)%7];
  
return result;
}

/*
finds peaks in the given array of consecutive data
function should be called to evaluate consecutive data sets not undependent ones.
Inputs: double fnfacc[7+NSAMPLES]: most recent filtered data
        double moy: mean of the last 7+NSAMPLES samples
Output: int result: number of peaks found 
*/
int findPeaks(double fnfacc[7+NSAMPLES]){
  //keep ilastpeak over function initialisations;
  static int ilastpeak = 0, start_prog = 1;
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
     if(last_temp>(llast_temp+12) && last_temp>(temp+12) && (last_temp > 1350) && (delta_i>7))
      {
         result += 1;
         ilastpeak = i;
         
         /* Au démarrage du programme les anciennes valeures des accélérations n'étant pas connues, un pas est détecté.
            Cette condition permet de ne pas en prendre compte. */
         if(start_prog)
         {
           start_prog = 0;
           result -= 1;
         }
      }
  }
  if (result == 0)
    ilastpeak = 0;
  
    return result;
}
