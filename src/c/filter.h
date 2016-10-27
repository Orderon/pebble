#pragma once

#include <pebble.h>
#include "filter.h"
#include "data_acc.h"
#define DIST_PER_STEP 0.5
#define NSAMPLES 15
static int n_steps;
static double distance;
static double filter1_History[7];
double filter_lowpass(int i, int acc[7],double facc[7]);
double filter_bandpass(int i, double nfacc[13],double fnfacc[12+NSAMPLES]);

int findPeaks(double fnfacc[12+NSAMPLES], double moy);