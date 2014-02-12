#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "position.h"

SPosition* creerPosition(int x, int y)
{
	SPosition* pos = malloc(sizeof(SPosition));
	pos->x = x;
	pos->y = y;
	return pos;
}

void detruirePosition(SPosition* position)
{
	free(position);
}
int abscissePosition(SPosition* position)
{
	return position->x;
}

int ordonneePosition(SPosition* position)

{
	return position->y;
}

SPosition* positionGauche(SPosition* position)
{
	return creerPosition(abscissePosition(position)-1, ordonneePosition(position));
}

SPosition* positionDroite(SPosition* position)
{
	return creerPosition(abscissePosition(position)+1, ordonneePosition(position));
}

SPosition* positionBas(SPosition* position)
{
	return creerPosition(abscissePosition(position), ordonneePosition(position)-1);
}

SPosition* positionHaut(SPosition* position)
{
	return creerPosition(abscissePosition(position), ordonneePosition(position)+1);
}

SPosition* transformerPosition(char* saisie)
{
	SPosition* res = NULL;
	int x,y;
	int taille_chaine = strlen(saisie);
	if (taille_chaine == 2)
	{
		x = (int)(saisie[0] - 'A');
		y = (int)(saisie[1] - '0');
		res = creerPosition(x,y);
	}
	else if(taille_chaine == 3)
	{
		x = (int)(saisie[0] - 'A');
		y = (int)(saisie[1] - '0')*10;
		y += (int)(saisie[2] - '0');
		res = creerPosition(x,y);
	}
	return res;
}

int positionsEgale(void* pos1, void* pos2)
{
	SPosition* p1 = (SPosition*)pos1;
	SPosition* p2 = (SPosition*)pos2;
	//printf("(%d == %d) && (%d == %d)\n", p1->x, p2->x, p1->y ,p2->y);
	return ((p1->x == p2->x) && (p1->y == p2->y));
}
