#pragma once

#include <pebble.h>
#include "filter.h"
#include "data_acc.h"
#define DIST_PER_STEP 0.5
static int n_steps;
static double distance;
static double filter1_History[7];
  
void handle_acc_data(Data_Acc * Acc[3]);
static int find_nb_steps(Data_Acc * Acc[3]);
static double filter_lowpass(Data_Acc * Acc[3],int xyz,int time);
static double filter_bandpass(Data_Acc * Acc[3],int time);

static void findPeaks(void);