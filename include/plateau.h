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
	list_SPion* liste;
} SPlateau;

SPlateau* creer_plateau (int taille, SPion** grille);

void detruire_plateau(SPlateau plateau);

#endif /* PLATEAU_H_ */
