#ifndef __PION__
#define __PION__

#include "position.h"
#include "couleur.h"
#include "liste.h"

typedef struct
{
	SPosition pos;
	ECouleur couleur;
} SPion;

typedef SList listePion;

SPion* creerPion(SPosition pos, ECouleur couleur);

void detruirePion(SPion* pion);

ECouleur couleurPion(SPion* pion);

int abscissePion(SPion* pion);

int ordonneePion(SPion* pion);

SPosition positionPion(SPion* pion);

#endif
