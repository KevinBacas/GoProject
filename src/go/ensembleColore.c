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
	SEnsembleColore* res = malloc(sizeof(SEnsembleColore));
	res->e_position = positions;
	res->couleur = couleur;
	return res;
}

void setCouleurEnsembleColore(SEnsembleColore* e_colore, ECouleur couleur)
{
	e_colore->couleur = couleur;
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
	SEnsemblePosition* res = NULL;
	if(e_colore)
	{
		res = e_colore->e_position;
	}
	return res;
}
