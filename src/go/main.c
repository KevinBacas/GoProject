#include <stdlib.h>
#include <stdio.h>

#include "chaine.h"
#include "couleur.h"
#include "liste.h"
#include "matrice.h"
#include "pion.h"
#include "position.h"

DECL_LIST(int);

int main()
{
	printf("Hello world !");

	int a = 5;
	int b = 10;
	int c = 15;
	list_int* l = malloc(sizeof(list_int));
	init_list(l);
	list_add(l, &a);
	list_add(l, &b);
	list_add(l, &c);

	return EXIT_SUCCESS;
}
