#ifndef __POSITION__
#define __POSITION__

//TODO : documentation
typedef struct
{
	int x;
	int y;
} SPosition;

SPosition* creerPosition(int x, int y);

void detruirePosition(SPosition* position);

int abscissePosition(SPosition* position);

int ordonneePosition(SPosition* position);

SPosition* positionGauche(SPosition* position);

SPosition* positionDroite(SPosition* position);

SPosition* positionBas(SPosition* position);

SPosition* positionHaut(SPosition* position);

SPosition* transformerPosition(char* saisie);

/**
 * @brief Test si les positions sont eguales.
 * @return 1 si vrai sinon 0.
 */
int positionsEgale(SPosition* pos1, SPosition* pos2);

#endif
