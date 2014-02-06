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

SPion* creer_Pion(SPosition pos, ECouleur couleur);

void detruire_Pion(SPion* pion);

ECouleur couleur_pion(SPion* pion);

int abscisse_pion(SPion* pion);

int ordonnee_pion(SPion* pion);

SPosition* position_pion(SPion* pion);

#endif
