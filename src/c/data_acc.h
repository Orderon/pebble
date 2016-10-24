#pragma once
#define TAILLE_ACC 100

// Structure regroupant les "TAILLE_ACC" dernières accélérations suivant les 3 axes, et l'indice de la dernière accélération (pseudo tableau cicrulaire)
typedef struct data_acc
{
  int last_accel;
  int x[TAILLE_ACC];
  int y[TAILLE_ACC];
  int z[TAILLE_ACC];
} Data_Acc;

//Initialise last_accel à 0 (pas encore d'accélération enregistrée)
void data_acc_init(Data_Acc * Acc);

//Enregistre les "num_samples" accélérations lue par l'accéléromètre dans la structure Acc
void data_acc_update_acc(AccelData * Data, Data_Acc * Acc, uint32_t num_samples);

/* Retourne une valeure d'accélération choisie de manière suivante :
    - indice : 0 -> dernière accélération, 1 -> avant dernière ...
    - indice_ccord : 0 -> suivant l'axe x, 1 -> y, autre -> z        */
int data_acc_get_samples(Data_Acc * Acc, int indice, int indice_coord);
