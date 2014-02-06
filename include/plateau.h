/*
 * plateau.hdetruire_chaine
 *
 *  Created on: 2 f�vr. 2014
 *      Author: Jacky
 */

#ifndef PLATEAU_H_
#define PLATEAU_H_

#include "couleur.h"

typedef struct
{
	int taille;
	ECouleur** grille;
} SPlateau;

SPlateau* creer_plateau (int taille, ECouleur** grille);

void detruire_plateau(SPlateau* plateau);

int taille_plateau(SPlateau* plateau);

ECouleur plateau_get(SPlateau* plateau, int x, int y);

void plateau_set(SPlateau plateau, int i, int j, ECouleur couleur);

/**
 * @brief Sauvegarde le plateau dans sa position actuelle.
 * Si la sauvegarde se passe sans probl`me, la fonction retourne 1, sinon 0
 */
int plateau_sauvegarde(SPlateau plateau, FILE* fichier);

/**
 * @brief Charge un plateau précedement sauvegardé.
 * Si le chargement n’est pas possible, retourne un Pointeur NULL
 */
SPlateau plateau_chargement(FILE* fichier);



#endif /* PLATEAU_H_ */
