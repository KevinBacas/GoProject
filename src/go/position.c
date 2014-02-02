#include <stdlib.h>
#include <stdio.h>
#include "position.h"

SPosition* creer_Position(int x, int y)
{
	SPosition* pos = malloc(sizeof(SPosition));
	pos->x=x ;
	pos->y=y ;
	return pos;
}


void detruire_Position(SPosition* pos)
{
	free(pos);
}
