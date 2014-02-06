#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "position.h"

SPosition* creer_Position(int x, int y)
{
	SPosition* pos = malloc(sizeof(SPosition));
	pos->x=x ;
	pos->y=y ;
	return pos;
}

int abscisse_position(SPosition position)
{
	return position.x;
}

int ordonnee_position(SPosition position)
{
	return position.y;
}

SPosition* transforme_position(SPlateau* plateau, char* saisie)
{
	char* tab_abscisse={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','s','r'};
	char* tab_ordonnee={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
	int x = 0;
	int y = 0;
	if(strln(saisie)==2)
	{
		if(strchr(tab_ordonnee, (int)(*(saisie))!= NULL))
		{
			y = (int)(*(saisie));
			x = 1 + (int)'a' - (int)*(saisie+1);
		}
		else
		{
			y = (int)*(saisie+1);
			x = 1+ (int)'a'-(int)*(saisie);
		}
	}
	SPosition position = creer_position(x,y);

	{
return position;

}
