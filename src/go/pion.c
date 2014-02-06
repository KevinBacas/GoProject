#include <stdlib.h>
#include <stdio.h>
#include "pion.h"

SPion* creerPion(SPosition pos, ECouleur couleur)
{
	SPion* pion = malloc(sizeof(SPion));
	pion->pos = pos;
	pion->couleur = couleur;
	return pion;
}

void detruirePion(SPion* pion)
{
	free(pion);
}

ECouleur couleurPion(SPion* pion)
{
	return pion->couleur;
}

int abscissePion(SPion* pion)
{
	return abscissePosition(&pion->pos);
}

int ordonneePion(SPion* pion)
{
	return ordonneePosition(&pion->pos);
}

SPosition positionPion(SPion* pion)
{
	return pion->pos;
}
