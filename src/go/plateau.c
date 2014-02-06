#include <stdlib.h>
#include <stdio.h>

#include "plateau.h"
#include "pion.h"

// TODO : Allocation désallocation de la grille à la main.

SPlateau* creer_plateau(int taille, ECouleur** grille)
{
	SPlateau* plateau = malloc(sizeof(SPlateau));
	plateau->taille = taille;
	plateau->grille = grille;

	return plateau;
}

void detruire_plateau(SPlateau* plateau)
{
	plateau->taille = 0;
	//detruireGrille(plateau->grille);
	free(plateau);
}

int taille_plateau(SPlateau* plateau)
{
	return plateau->taille;
}

ECouleur plateau_get(SPlateau* plateau, int x, int y)
{
	return plateau->grille[x][y];
}

