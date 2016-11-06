/*---------------------------------------------------------------------------
filter.h
Authors: Thomas Triquet, Cyrill Baumann
Version: 1.0
Date: 06.11.2016
---------------------------------------------------------------------------*/


#pragma once

#include <pebble.h>
#include "filter.h"
#include "data_acc.h"
#define DIST_PER_STEP 0.5
#define NSAMPLES 25

/*executes lowpass filter order 7
Inputs: int i: position of the most recent value in the array
        double acc[7]: 7 most recent accelerometer values
        double facc[7]: 7 last outputs of this filter
Output: double result: the filtered value of acc[i], the most recent accelerometer value */
double filter_lowpass(int i, double acc[7],double facc[7]);

/*executes bandpass filter order 7
Inputs: int i: position of the most recent value in the array
        double nfacc[7]: 13 most recent filtered accelerometer and normalized values
        double facc[7]: 12+NSAMPLES last outputs of this filter, used are only last 13, rest can be empty
Output: double result: the filtered value of nfacc[i], the most recent accelerometer value */
double filter_bandpass(int i, double nfacc[13],double fnfacc[12+NSAMPLES]);


/*finds peaks in the given array of consecutive data
function should be called to evaluate consecutive data sets not undependent ones.
Inputs: double fnfacc[7+NSAMPLES]: most recent filtered data
        double moy: mean of the last 7+NSAMPLES samples
Output: int result: number of peaks found*/
int findPeaks(double fnfacc[12+NSAMPLES], double moy);