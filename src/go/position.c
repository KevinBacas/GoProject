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

int abscisse_position(SPosition position)
{
	return position.x;
}

int ordonnee_position(SPosition position)
{
	return position.y;
}
