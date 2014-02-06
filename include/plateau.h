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

SPlateau* init_plateau(int taille);

SPlateau* creer_plateau (int taille, ECouleur** grille);

void detruire_plateau(SPlateau* plateau);

int taille_plateau(SPlateau* plateau);

ECouleur couleur_position(SPlateau* plateau, int x, int y);


#endif /* PLATEAU_H_ */
