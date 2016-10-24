#pragma once


static void handle_acc_data(void);
static int find_nb_steps(void);
static double filter_pass_band();
static double filter_lowpass(char STRUCT_TODO,int time);
static void findPeaks(uint32_t num_samples);