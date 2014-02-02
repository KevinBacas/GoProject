#include <stdlib.h>
#include <stdio.h>
#include "pion.h"

SPion* creer_Pion(SPosition pos, ECouleur couleur)
{
	SPion* pion = malloc(sizeof(pion));
	pion->pos = pos;
	pion->couleur = couleur;
	return pion;
}

void detruire_Pion(SPion pion)
{
	detruire_Position(pion.pos);
	free(pion);
}
