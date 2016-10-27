#include <pebble.h>
#include "data_acc.h"
#include "filter.h"
#include "display.h"

/* Structure contenant les valeurs des accélérations (x, y ou z) brut et filtrés organisée de la manière suivante :
    - indices 0 à 5 : valeurs au temps t-6, t-5 ... (ces valeurs sont nécessaires pour un filtre d'ordre 6)
    - indices 6 à NSAMPLES + 6 : derniéres valeurs lues par l'accéléromètre.                                      */
typedef struct data_acc
{
  int acc[7];
  double acc_filt[7];
} Data_Acc;

/* Même principe que Data_Acc mais pour la norme de l'accélération. 12 valeurs précédentes sont ici nécessaires 
   car un filtre passe bande d'ordre 6 est effectué par la suite.                                                  */
typedef struct data_norm
{
  long norm[13];
  double norm_filt[NSAMPLES + 12];
} Data_Norm;

static Data_Acc Acc[3];
static Data_Norm Norm;

void data_acc_init(void)
{
  int i = 0, j=0;
  for (i=0;i<=6;i++)
  {
    //j : permet de sélectionner l'axe (j = 0 -> X, 1 -> Y, 2 -> Z)
    for (j=0;j<=2;j++)
    {
      Acc[j].acc[i] = 0;
      Acc[j].acc_filt[i] = 0;
    }
  }
}

void data_norm_init(void)
{
  int i = 0;
  for (i=0;i<=12;i++)
  {
    Norm.norm[i] = 0;
    Norm.norm_filt[i] = 0;
  }
  for (i=14;i <= NSAMPLES + 11;i++)
    Norm.norm_filt[i] = 0;
}

// Cette fonction permet de garder en mémoire les valeurs précédentes des accélérations / normes, nécessaires pour le filtrage.
static void data_norm_decalage(void)
{
  int i = 0;  
  for (i = 0; i <= 11; i++)
  {
    // Décalage des normes (indicage différent des accélérations)
    Norm.norm_filt[i] = Norm.norm_filt[NSAMPLES+i];
  }  
}

void data_acc_update_acc(AccelData * Data)
{
  static int step = 0;
  int i = 0; 
  // Décalage des normes avant d'enregistrer les nouvelles.
  data_norm_decalage();
  for (i = 0; i <= NSAMPLES - 1; i++)
  {
    // Enregistrement des accélérations
    Acc[X].acc[i%7] = Data[i].x;
    Acc[Y].acc[i%7] = Data[i].y;
    Acc[Z].acc[i%7] = Data[i].z;
    
    Acc[X].acc_filt[i%7] = filter_lowpass(i,Acc[X].acc, Acc[X].acc_filt);
    Acc[Y].acc_filt[i%7] = filter_lowpass(i,Acc[Y].acc, Acc[Y].acc_filt);
    Acc[Z].acc_filt[i%7] = filter_lowpass(i,Acc[Z].acc, Acc[Z].acc_filt);
    
    Norm.norm[i%13] = Acc[X].acc_filt[i%7]*Acc[X].acc_filt[i%7] +
                       Acc[Y].acc_filt[i%7]*Acc[Y].acc_filt[i%7] +
                       Acc[Z].acc_filt[i%7]*Acc[Z].acc_filt[i%7];
    
    Norm.norm_filt[i + 12] = filter_bandpass(i, Norm.norm, Norm.norm_filt);
  }
  update_counter(findPeaks(Norm.norm_filt));
  
}