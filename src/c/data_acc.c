#include <pebble.h>
#include "data_acc.h"

void data_acc_init(Data_Acc * Acc)
{
  Acc->last_accel = 0;
}

void data_acc_maj_acc(AccelData * Data, Data_Acc * Acc, uint32_t num_samples)
{
  uint32_t i = 0;
  for (i = 0; i <= num_samples - 1; i++)
  {
    // Si on arrive à la fin du tableau, reboucle au début (tableau pseudo circulaire)
    if (Acc->last_accel == TAILLE_ACC-1)
      Acc->last_accel = 0;
    // Enregistrement des accélérations
    Acc->x[i] = Data[i].x;
    Acc->y[i] = Data[i].y;
    Acc->z[i] = Data[i].z;
    Acc->last_accel +=1;
  }
}

int data_acc_get_samples_x(Data_Acc * Acc, int indice, int indice_coord)
{
  // Recherche de l'indice du tableau correspondant à l'indice demandé
  if(Acc->last_accel<indice)
    indice = TAILLE_ACC - (indice - Acc->last_accel);
  // Détermination de l'axe demandé
  switch(indice_coord)
  {
    case(0) :
      return Acc->x[indice];
    case(1) :
      return Acc->y[indice];
    default :
      return Acc->x[indice];
  }
  
}