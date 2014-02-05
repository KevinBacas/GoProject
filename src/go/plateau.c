#include <stdlib.h>
#include <stdio.h>
#include "plateau.h"
#include "pion.h"

SPlateau* creer_plateau (int taille, SPion** grille)
{
	SPlateau* plateau = malloc(sizeof(SPlateau));
	plateau->taille = taille;
	plateau->grille = grille;

	return plateau;
}

void detruire_plateau(SPlateau* plateau)
{
	plateau->taille = 0;
	detruireGrille(plateau->grille);
	free(plateau);
}

