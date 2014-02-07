#include <stdlib.h>
#include <stdio.h>

#include "partie.h"

void printHomeMenu()
{
	printf("-- MENU --\n");
	printf("1) Jouer une nouvelle partie\n");
	printf("2) Charger dernière partie\n");
	printf("Q) Quitter le jeu\n");
}

int main()
{
	printf("== JEU DE GO ==\n\n\n");

	int quit = 0;
	do{
		printHomeMenu();

		char saisie = ' ';
		scanf("%c", &saisie);
		getchar();
		switch(saisie)
		{
		case '1':
		{
			SPartie* p = initialisationPartie(questionsTerminal);
			jouerPartie(p);
			detruirePartie(p);
			break;
		}
		case '2':
		{
			FILE* fichier = fopen("sauvegarde.save", "r");
			if(fichier)
			{
				SPartie* p = partie_charge(fichier);
				fclose(fichier);
				jouerPartie(p);
				detruirePartie(p);
			}
			else
			{
				printf("Aucune sauvegarde n'est présente");
			}
			break;
		}
		case 'Q':
			quit = 1;
			break;
		}
	}while(!quit);

	return EXIT_SUCCESS;
}
