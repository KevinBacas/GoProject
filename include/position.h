#ifndef __POSITION__
#define __POSITION__

typedef struct
{
	int x;
	int y;
} SPosition;

SPosition* creer_Position(int x, int y);

void detruire_Position(SPosition* pos);

int abscisse_position(SPosition* position);

int ordonnee_position(SPosition* position);

#endif
