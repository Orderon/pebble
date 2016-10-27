#include <pebble.h>
#include "data_acc.h"

/* Structure contenant les valeurs des accélérations (x, y ou z) brut et filtrés organisée de la manière suivante :
    - indices 0 à 5 : valeurs au temps t-6, t-5 ... (ces valeurs sont nécessaires pour un filtre d'ordre 6)
    - indices 6 à NSAMPLES + 6 : derniéres valeurs lues par l'accéléromètre.                                      */
typedef struct data_acc
{
  int acc[NSAMPLES + 6];
  int acc_filt[NSAMPLES + 6];
} Data_Acc;

/* Même principe que Data_Acc mais pour la norme de l'accélération. 12 valeurs précédentes sont ici nécessaires 
   car un filtre passe bande d'ordre 6 est effectué par la suite.                                                  */
typedef struct data_norm
{
  int norm[NSAMPLES + 12];
  int norm_filt[NSAMPLES + 12];
} Data_Norm;

static Data_Acc* Acc[3];
static Data_Norm* Norm;


void data_acc_init(void)
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

void data_norm_init(void)
{
  int i = 0;
  for (i=0;i<=12 + NSAMPLES;i++)
  {
    Norm->norm[i] = 0;
    Norm->norm_filt[i] = 0;
  }
}

// Cette fonction permet de garder en mémoire les valeurs précédentes des accélérations / normes, nécessaires pour le filtrage.
static void data_acc_decalage(void)
{
  int i = 0;  
  for (i = 0; i <= 6; i++)
  {
    // Décalage des accélérations brutes.
    Acc[X]->acc[i] = Acc[X]->acc[NSAMPLES-6+i];
    Acc[Y]->acc[i] = Acc[Y]->acc[NSAMPLES-6+i];
    Acc[Z]->acc[i] = Acc[Z]->acc[NSAMPLES-6+i];
    
    // Décalage des accélérations filtrées.
    Acc[X]->acc_filt[i] = Acc[X]->acc_filt[NSAMPLES-6+i];
    Acc[Y]->acc_filt[i] = Acc[Y]->acc_filt[NSAMPLES-6+i];
    Acc[Z]->acc_filt[i] = Acc[Z]->acc_filt[NSAMPLES-6+i];
  }
  
  for (i = 0; i <= 12; i++)
  {
    // Décalage des normes (indicage différent des accélérations)
    Norm->norm[i] = Norm->acc[NSAMPLES-12+i];
    Norm->norm_filt[i] = Norm->acc_filt[NSAMPLES-12+i];
  }  
}

void data_acc_update_acc(AccelData * Data)
{
  int i = 0; 
  // Décalage des accélérations / normes avant d'enregistrer les nouvelles.
  data_acc_decalage();
  for (i = 0; i <= NSAMPLES - 1; i++)
  {
    // Enregistrement des accélérations
    Acc[X]->acc[6+i] = Data[i].x;
    Acc[Y]->acc[6+i] = Data[i].y;
    Acc[Z]->acc[6+i] = Data[i].z;
    // Calcul de la norme (sans la racine carré)
    Norm->norm[12+i] = Data[i].x*Data[i].x + Data[i].y*Data[i].y + Data[i].z*Data[i].z; 
  }
}