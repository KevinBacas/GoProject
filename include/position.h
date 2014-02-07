#ifndef __POSITION__
#define __POSITION__

#include "plateau.h"

//TODO : documentation
typedef struct
{
	int x;
	int y;
} SPosition;

SPosition* creerPosition(int x, int y);

int abscissePosition(SPosition* position);

int ordonneePosition(SPosition* position);

SPosition* transformerPosition(SPlateau* plateau, char* saisie);

/**
 * @brief Test si les positions sont eguales.
 * @return 1 si vrai sinon 0.
 */
int positionsEgale(SPosition* pos1, SPosition* pos2);

#endif
