#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "partie.h"

void printHomeMenu()
{
	printf("-- MENU --\n");
	printf("1) Jouer une nouvelle partie\n");
	printf("2) Charger dernière partie\n");
	printf("Q) Quitter le jeu\n");
}

void playTerminalMod()
{
	int quit = 0;
	do
	{
		printHomeMenu();

		char saisie = ' ';
		scanf("%c", &saisie);
		while ( getchar() != '\n' );
		switch(saisie)
		{
		case '1':
		{
			SPartie* p = initialisationPartie(questionsTerminal);

			printf("Score de fin : %f\n", jouerPartie(p));

			detruirePartie(p);
			break;
		}
		case '2':
		{
			FILE* fichier = fopen("sauvegarde.save", "r");
			if(fichier)
			{
				SPartie* partie = partie_charge(fichier);
				fclose(fichier);
				if(partie)
				{
					rejouerPartie(partie);
					jouerPartie(partie);
					detruirePartie(partie);
				}
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
}

void playSDLMod()
{
	printf("SDL !");
}

int main(int argc, char** argv)
{
	printf("== JEU DE GO ==\n\n\n");

	if(argc == 2)
	{
		if(strcmp("--SDL", argv[1]) == 0)
		{
			playSDLMod();
		}
	}
	else
	{
		playTerminalMod();
	}

	return EXIT_SUCCESS;
}
