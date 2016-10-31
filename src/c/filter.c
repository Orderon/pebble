#include <pebble.h>
#include "filter.h"
#include "data_acc.h"
#define DIST_PER_STEP 0.5
static int n_steps;
static double distance;
  

 //called for x,y and z seperately. acc[0] being the t-6 value of the accelerometer
//facc[0] being the filtered value at t-6
double filter_lowpass(int i, int acc[7],double facc[7]){
/* variable declaration for filter*/
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
  
  double result = a1* acc[(i+7)%7] + a2 * acc[(i+6)%7] +  a3 * acc[(i+5)%7] + a4 * acc[(i+4)%7] + 
  a5 * acc[(i+3)%7] + a6 * acc[(i+2)%7] +  a7 * acc[(i+1)%7] -
  b1 * facc[(i+6)%7] - b2 * facc[(i+5)%7] - b3 * facc[(i+4)%7] - b4 * facc[(i+3)%7] - 
  b5 * facc[(i+2)%7] - b6 * facc[(i+1)%7];
  
return result;
}

double filter_bandpass(int i,double nfacc[13],double fnfacc[12+NSAMPLES]){
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
  b11 = -0.0645,
  b12 = 0.0050;
  
  
  
  double result = a1* nfacc[(i+13)%13] +  a3 * nfacc[(i+11)%13] +  a5 * nfacc[(i+9)%13] +
  a7 * nfacc[(i+7)%13] +  a9 * nfacc[(i+5)%13] +  a11 * nfacc[(i+3)%13] +  a13 * nfacc[(i+1)%13] -
  b1 * fnfacc[i+11] - b2 * fnfacc[i+10] - b3 * fnfacc[i+9] - b4 * fnfacc[i+8] - 
  b5 * fnfacc[i+7] - b6 * fnfacc[i+6] - b7 * fnfacc[i+5] - b8 * fnfacc[i+4] -
  b9 * fnfacc[i+3] - b10 * fnfacc[i+2] - b11 * fnfacc[i+1] - b12 * fnfacc[i+0];
  return result;
}

int findPeaks(double fnfacc[12+NSAMPLES], double moy){
  static int ilastpeak = 0;
  double result=0;
  double llast_temp=0; 
  double last_temp=fnfacc[10]; //initialize last two variables from previous set.
  double temp=fnfacc[11];
  for(int i=12;i<12+NSAMPLES;i++){ 
    
    //actualise temporary variables (go forward in time by 1 step)
    llast_temp = last_temp;
    last_temp = temp;
    temp = fnfacc[i];
      
      //if the middle value is higher than the two others, then add a peak
     if((last_temp>(llast_temp)) && (last_temp>(temp)) && (last_temp > 750) && (last_temp<3000000)&& (last_temp > 1.1*moy) && ((i - ilastpeak>=10)||(i-ilastpeak+12+NSAMPLES)>=10))
      {
        result = last_temp;
       ilastpeak = i;
      }
  }
  if (result == 0)
    ilastpeak = 0;
    return result;
}
