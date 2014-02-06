#ifndef __POSITION__
#define __POSITION__

#include "plateau.h"

typedef struct
{
	int x;
	int y;
} SPosition;

SPosition creerPosition(int x, int y);

int abscissePosition(SPosition position);

int ordonneePosition(SPosition position);

SPosition transformerPosition(SPlateau* plateau, char* saisie);

#endif
