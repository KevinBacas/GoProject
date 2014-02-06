/*
 * ensembleColore.c
 *
 *  Created on: Feb 6, 2014
 *      Author: dev
 */

#include "ensembleColore.h"
#include "couleur.h"

typedef struct ensembleColore {
	SEnsemblePosition* e_position;
	ECouleur couleur;
} SEnsembleColore;

ECouleur couleurEnsembleColore(SEnsembleColore* e_colore)
{
	return e_colore->couleur;
}
