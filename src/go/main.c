#include <stdlib.h>
#include <stdio.h>

#include "partie.h"

int main()
{
	printf("Hello world !");

	SPartie* p = initialisationPartie(questionsTerminal);

	detruirePartie(p);

	return EXIT_SUCCESS;
}
