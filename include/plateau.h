/*
 * plateau.h
 *
 *  Created on: 2 févr. 2014
 *      Author: Jacky
 */

#ifndef PLATEAU_H_
#define PLATEAU_H_

typedef struct
{
	int taille;
	ECouleur** grille;
} SPlateau;

SPlateau* creer_plateau (int taille, ECouleur** grille);

void detruire_plateau(SPlateau plateau);

int taille_plateau(SPlateau* plateau);

ECouleur couleur_position(SPlateau* plateau, int x, int y);


#endif /* PLATEAU_H_ */
