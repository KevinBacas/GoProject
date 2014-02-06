/*
 * ensembleColore.c
 *
 *  Created on: Feb 6, 2014
 *      Author: dev
 */

#include "couleur.h"

typedef struct ensembleColore {
	SEnsemblePosition* e_position;
	ECouleur couleur;
} SEnsembleColore;

SEnsembleColore creerEnsembleColore()
{
	ECouleur couleur = VIDE;
	SEnsemblePosition* positions = creerEnsemblePosition();
	SEnsembleColore* EnsembleColore = malloc(sizeof(SEnsembleColore));
	EnsembleColore->e_position = positions;
	EnsembleColore->couleur = couleur;
	return EnsembleColore;
}

void detruireEnsembleColore(SEnsembleColore* _e_colore)
{
	deleteList(_e_colore->e_position);
	free(_e_colore);
}
