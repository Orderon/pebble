#include <pebble.h>
#include "data_acc.h"

void data_acc_init(Data_Acc * Acc[3])
{
  int i = 0, j=0;
  for (i=0;i<=6;i++)
  {
    for (j=0;j<=2;j++)
    {
      Acc[j]->last_acc[i] = 0;
      Acc[j]->last_acc_filt[i] = 0;
    }
  }
}

void data_norm_init(Data_Norm * Norm)
{
  int i = 0;
  for (i=0;i<=12;i++)
  {
    Norm->last_acc[i] = 0;
    Norm->last_acc_filt[i] = 0;
  }
}

void data_acc_update_acc(AccelData * Data, Data_Acc * Acc[3], uint32_t num_samples)
{
  uint32_t i = 0;
  for (i = 0; i <= 6; i++)
  {
    Acc[X]->last_acc[6-1-i] =  Acc[X]->new_acc[num_samples-1-i];
    Acc[Y]->last_acc[6-1-i] =  Acc[Y]->new_acc[num_samples-1-i];
    Acc[Z]->last_acc[6-1-i] =  Acc[Z]->new_acc[num_samples-1-i];
  }
  
  for (i = 0; i <= num_samples - 1; i++)
  {
    // Enregistrement des accélérations
    Acc[X]->new_acc[i] = Data[i].x;
    Acc[Y]->new_acc[i] = Data[i].y;
    Acc[Z]->new_acc[i] = Data[i].z;
  }
}