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

int positionValide(SPlateau* plateau,SPosition* position)
{
	int x = abscissePosition(position);
	int y = ordonneePosition(position);
	int taille=taille_plateau(plateau);
	if(x >= taille || x < 0 || y >= taille || y<0) return 0;
	else return 1;
}

SPosition* transformerPosition(SPlateau* plateau, char* saisie)
{
	char tab_abscisse[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','s','r'};
	char tab_ordonnee[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
	int x = 0;
	int y = 0;
	if(strlen(saisie)==2)
	{
		if(strchr(tab_ordonnee, (int)(*(saisie))) != NULL)
		{
			y = (int)(*(saisie));
			x = 1 + (int)'a' - (int)*(saisie+1);
		}
		else
		{
			y = (int)((*(saisie+1))-'0');
			x = (int)((*(saisie))-'a');
		}
	}
	return creerPosition(x,y);
}

int positionsEgale(SPosition* pos1, SPosition* pos2)
{
	return (pos1->x == pos2->x && pos1->y == pos2->x) ? 1 : 0;
}
