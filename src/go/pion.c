#include <stdlib.h>
#include <stdio.h>
#include "pion.h"

Pion* creer_Pion(Position pos, couleur couleur)
{
	Pion* pion = malloc(sizeof(pion));
	pion.pos = pos;
	pion.couleur = couleur;
	return pion;
}

void detruire_Pion(Pion pion)
{
	detruire_Position(pion.pos);
	free(pion);
}
