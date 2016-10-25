#pragma once
#define NSAMPLES 12
#define X 0
#define Y 0
#define Z 0

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
  int acc[NSAMPLES + 12];
  int acc_filt[NSAMPLES + 12];
} Data_Norm;

// Initialisation des accélérations à 0.
void data_acc_init(Data_Acc * Acc[3]);

// Initialisation des normes à 0.
void data_norm_init(Data_Norm * Norm);

// Enregistrement des nouvelles accélérations tout en enregistrant les anciennes nécessaires pour le filtrage
void data_acc_update_acc(AccelData * Data, Data_Acc * Acc[3], Data_Norm * Norm);
