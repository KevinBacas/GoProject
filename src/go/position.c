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

int positionsEgale(SPosition* pos1, SPosition* pos2)
{
	return (pos1->x == pos2->x && pos1->y == pos2->x) ? 1 : 0;
}
