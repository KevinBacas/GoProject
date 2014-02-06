#include <stdlib.h>
#include <stdio.h>

#include "plateau.h"
#include "pion.h"

// TODO : Allocation desalocation de la grille a  la main.

SPlateau* init_plateau(int taille)
{
	int i;
	ECouleur** grille = malloc(sizeof(ECouleur*));
	for(i=0; i<taille; i++)
	{
		*(grille+i)=malloc(sizeof(ECouleur));
	}
	return creer_plateau(taille,grille);
}

SPlateau* creer_plateau(int taille, ECouleur** grille)
{
	SPlateau* plateau = malloc(sizeof(SPlateau));
	plateau->taille = taille;
	plateau->grille = grille;

	return plateau;
}

void detruire_plateau(SPlateau* plateau)
{
	int i;
	plateau->taille = 0;
	for(i=0; i<taille_plateau(plateau); i++)
	{
		free(*((plateau->grille)+i));

	}
	free(plateau->grille);
	free(plateau);
}

int taille_plateau(SPlateau* plateau)
{
	return plateau->taille;
}

ECouleur couleur_position(SPlateau* plateau, int x, int y)
{
	return plateau->grille[x][y];
}

