#include <stdlib.h>
#include <stdio.h>
#include "pion.h"

SPion* creer_Pion(SPosition pos, ECouleur couleur)
{
	SPion* pion = malloc(sizeof(SPion));
	pion->pos = pos;
	pion->couleur = couleur;
	return pion;
}

void detruire_Pion(SPion pion)
{
	detruire_Position(pion.pos);
	free(pion);
}

ECouleur couleur_pion(SPion* pion)
{
	return pion->couleur;
}

int abscisse_pion(SPion* pion)
{
	return abscisse_position(pion->pos);
}

int ordonnee_pion(SPion* pion)
{
	return ordonnee_position(pion->pos);
}
