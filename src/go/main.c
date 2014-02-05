#include <stdlib.h>
#include <stdio.h>

#include "chaine.h"
#include "couleur.h"
#include "liste.h"
#include "matrice.h"
#include "pion.h"
#include "position.h"

int main()
{
	printf("Hello world !");

	int a = 5;
	int b = 10;
	int c = 15;
	SList* l = listInit();
	listAdd(l, &a);
	listAdd(l, &b);
	listAdd(l, &c);

	listDisplay(l);

	return EXIT_SUCCESS;
}
