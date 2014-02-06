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

int abscissePosition(SPosition* position)
{
	return position->x;
}

int ordonneePosition(SPosition* position)
{
	return position->y;
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

int positionsEguale(SPosition* pos1, SPosition* pos2)
{
	return (pos1->x == pos2->x && pos1->y == pos2->x) ? 1 : 0;
}
