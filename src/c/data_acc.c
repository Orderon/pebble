/*---------------------------------------------------------------------------
data_acc.c
Authors: Thomas Triquet
Version: 1.0
Date: 06.11.2016
---------------------------------------------------------------------------*/

#include <pebble.h>
#include "data_acc.h"
#include "filter.h"
#include "display.h"

/* Structure contenant les 7 dernières valeurs des accélérations (x, y ou z) brutes et filtrées (qui sont nécessaires
   pour le filtre). Elles sont organisées de manière "circulaire". (la valeure correspondant à la dernière 
   accélération lue, est enregistrée à la place de la plus vieille valeure) : ex : si acc[6] est la dernière 
   valeure lue, la prochaine sera enregistrée dans acc[0] (principe du tableau circulaire).                           */
typedef struct data_acc
{
  double acc[7];
  double acc_filt[7];
} Data_Acc;

/* Même principe que Data_Acc mais pour la norme de l'accélération. Cependant il est nécessaire de garder tout 
   le signal de la norme filtrée pour ensuite détecter les pics sur notre échantillon. Le tableau pour la norme 
   filtrée est donc plus grand.                                                                                      */
typedef struct data_norm
{
  double norm[7];
  double norm_filt[NSAMPLES + 7];
} Data_Norm;

/* Déclarations des structures : 
    - Un tableau pour les accélérations x, y et z.
    - Une norme.                                                                                                    */
static Data_Acc Acc[3];
static Data_Norm Norm;

// Initialisation des accélérations à 0.
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

// Initialisation des normes à 0.
void data_norm_init(void)
{
  int i = 0;
  for (i=0;i<=6;i++)
  {
    Norm.norm[i] = 0;
    Norm.norm_filt[i] = 0;
  }
  for (i=7;i <= NSAMPLES + 6;i++)
    Norm.norm_filt[i] = 0;
}

// Cette fonction permet de garder en mémoire les valeurs précédentes des accélérations / normes, nécessaires pour le filtrage.
static void data_norm_decalage()
{
  int i = 0;  
  for (i = 0; i <= 6; i++)
  {
    // Décalage des normes (indicage différent des accélérations)
    Norm.norm_filt[i] = Norm.norm_filt[NSAMPLES+i];
  }  
}

/* Enregistrement des nouvelles accélérations tout en enregistrant les anciennes nécessaires pour le filtrage.
   Appelle également findPeaks pour compter le nombre de pas détecté.                                         */
void data_acc_update_acc(AccelData * Data)
{
  int i = 0;
  static double last_norm_filt[7] = {0,0,0,0,0,0,0};
  // Décalage des normes avant d'enregistrer les nouvelles.
  data_norm_decalage();
  for (i = 0; i <= NSAMPLES - 1; i++)
  {
    // Enregistrement des accélérations. Le modulo permet d'utiliser le tableau comme un tableau circulaire.
    Acc[X].acc[i%7] = Data[i].x;
    Acc[Y].acc[i%7] = Data[i].y;
    Acc[Z].acc[i%7] = Data[i].z;
   
    // Filtrage des accélérations.
    Acc[X].acc_filt[i%7] = filter_lowpass(i,Acc[X].acc, Acc[X].acc_filt);
    Acc[Y].acc_filt[i%7] = filter_lowpass(i,Acc[Y].acc, Acc[Y].acc_filt);
    Acc[Z].acc_filt[i%7] = filter_lowpass(i,Acc[Z].acc, Acc[Z].acc_filt);
    
    // Norme des accélérations / 1000 (car pas de racine : nombre trop grand si pas divisé par 1000).
    Norm.norm[i%7] = (Acc[X].acc_filt[i%7]*Acc[X].acc_filt[i%7] +
                      Acc[Y].acc_filt[i%7]*Acc[Y].acc_filt[i%7] +
                      Acc[Z].acc_filt[i%7]*Acc[Z].acc_filt[i%7])/1000;
    
    // Filtrage de la norme.
    Norm.norm_filt[i + 6] = filter_lowpass(i, Norm.norm, last_norm_filt);
    last_norm_filt[i%7] = Norm.norm_filt[i + 6];
  } 
  // Comptage des pas.
  update_counter(findPeaks(Norm.norm_filt));
}