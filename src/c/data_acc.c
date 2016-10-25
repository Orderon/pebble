#include <pebble.h>
#include "data_acc.h"

void data_acc_init(Data_Acc * Acc[3])
{
  int i = 0, j=0;
  for (i=0;i<=6 + NSAMPLES;i++)
  {
    //j : permet de sélectionner l'axe (j = 0 -> X, 1 -> Y, 2 -> Z)
    for (j=0;j<=2;j++)
    {
      Acc[j]->acc[i] = 0;
      Acc[j]->acc_filt[i] = 0;
    }
  }
}

void data_norm_init(Data_Norm * Norm)
{
  int i = 0;
  for (i=0;i<=12 + NSAMPLES;i++)
  {
    Norm->acc[i] = 0;
    Norm->acc_filt[i] = 0;
  }
}

// Cette fonction permet de garder en mémoire les valeurs précédentes des accélérations / normes, nécessaires pour le filtrage.
static void data_acc_decalage(Data_Acc * Acc[3], Data_Norm * Norm)
{
  int i = 0;  
  for (i = 0; i <= 6; i++)
  {
    // Décalage des accélérations brutes.
    Acc[X]->acc[i] =  Acc[X]->acc[NSAMPLES-6+i];
    Acc[Y]->acc[i] =  Acc[Y]->acc[NSAMPLES-6+i];
    Acc[Z]->acc[i] =  Acc[Z]->acc[NSAMPLES-6+i];
    
    // Décalage des accélérations filtrées.
    Acc[X]->acc_filt[i] =  Acc[X]->acc_filt[NSAMPLES-6+i];
    Acc[Y]->acc_filt[i] =  Acc[Y]->acc_filt[NSAMPLES-6+i];
    Acc[Z]->acc_filt[i] =  Acc[Z]->acc_filt[NSAMPLES-6+i];
  }
  
  for (i = 0; i <= 12; i++)
  {
    // Décalage des normes (indicage différent des accélérations)
    Norm->acc[i] = Norm->acc[NSAMPLES-12+i];
    Norm->acc_filt[i] = Norm->acc_filt[NSAMPLES-12+i];
  }  
}

void data_acc_update_acc(AccelData * Data, Data_Acc * Acc[3], Data_Norm * Norm)
{
  int i = 0; 
  // Décalage des accélérations / normes avant d'enregistrer les nouvelles.
  data_acc_decalage(Acc,Norm);
  for (i = 0; i <= NSAMPLES - 1; i++)
  {
    // Enregistrement des accélérations
    Acc[X]->acc[6+i] = Data[i].x;
    Acc[Y]->acc[6+i] = Data[i].y;
    Acc[Z]->acc[6+i] = Data[i].z;
    // Calcul de la norme (sans la racine carré)
    Norm->acc[12+i] = Data[i].x*Data[i].x + Data[i].y*Data[i].y + Data[i].z*Data[i].z; 
  }
}