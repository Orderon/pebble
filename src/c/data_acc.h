#pragma once
#define NSAMPLES 10
#define X 0
#define Y 0
#define Z 0

typedef struct data_acc
{
  int last_acc[6];
  int new_acc[NSAMPLES];
  int last_acc_filt[6];
  int new_acc_filt[NSAMPLES];
} Data_Acc;

typedef struct data_norm
{
  int last_acc[12];
  int new_acc[NSAMPLES];
  int last_acc_filt[12];
  int new_acc_filt[NSAMPLES];
} Data_Norm;

void data_acc_init(Data_Acc * Acc[3]);

void data_norm_init(Data_Norm * Norm);

//Enregistre les "num_samples" accélérations lue par l'accéléromètre dans la structure Acc
void data_acc_update_acc(AccelData * Data, Data_Acc * Acc[3], uint32_t num_samples);
