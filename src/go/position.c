#include <stdlib.h>
#include <stdio.h>
#include "position.h"

Position* creer_Position(int x, int y)
{
	Position* pos = malloc(sizeof(Position));
	pos->x=x ;
	pos->y=y ;
	return pos;
}


void detruire_Position(Position* pos)
{
	free(pos);
}
