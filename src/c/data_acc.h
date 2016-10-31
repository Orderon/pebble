#pragma once
#define X 0
#define Y 1
#define Z 2
#define NSAMPLES 25

// Initialisation des accélérations à 0.
void data_acc_init(void);

// Initialisation des normes à 0.
void data_norm_init(void);

// Enregistrement des nouvelles accélérations tout en enregistrant les anciennes nécessaires pour le filtrage
void data_acc_update_acc(AccelData * Data);