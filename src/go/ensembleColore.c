/*
 * ensembleColore.c
 *
 *  Created on: Feb 6, 2014
 *      Author: dev
 */

#include "ensembleColore.h"
#include "ensemblePosition.h"
#include "couleur.h"

typedef struct ensembleColore {
	SEnsemblePosition* e_position;
	ECouleur couleur;
} SEnsembleColore;

SEnsembleColore* creerEnsembleColore()
{
	ECouleur couleur = VIDE;
	SEnsemblePosition* positions = listInit();
	SEnsembleColore* EnsembleColore = malloc(sizeof(SEnsembleColore));
	EnsembleColore->e_position = positions;
	EnsembleColore->couleur = couleur;
	return EnsembleColore;
}

void detruireEnsembleColore(SEnsembleColore* e_colore)
{
	listDelete(e_colore->e_position);
	free(e_colore);
}

ECouleur couleurEnsembleColore(SEnsembleColore* e_colore)
{
	return e_colore->couleur;
}

SEnsemblePosition* listEnsembleColore(SEnsembleColore* e_colore)
{
	return e_colore->e_position;
}
