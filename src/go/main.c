#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>

#include "partie.h"

/*
 * @brief Permet d'afficher le contenu d'un dossier récursivement
 * @param dir Nom du dossier
 * @param depth Sert pour l'affichage
 */
void printdir(char *dir, int depth)
{
    DIR *dp;
    struct dirent *entry;
    struct stat statbuf;

    if((dp = opendir(dir)) == NULL) {
        fprintf(stderr, "cannot open directory: %s\n", dir);
        return;
    }
    chdir(dir);
    while((entry = readdir(dp)) != NULL)
    {
        lstat(entry->d_name, &statbuf);
        if(S_ISDIR(statbuf.st_mode))
        {
            if(	strcmp(".", entry->d_name) == 0
            	|| strcmp("..", entry->d_name) == 0)
                continue;
            printf("%*s%s/\n", depth, "", entry->d_name);
            /* Recurse at a new indent level */
            printdir(entry->d_name,depth+4);
        }
        else printf("%*s%s\n", depth, "", entry->d_name);
    }
    chdir("..");
    closedir(dp);
}

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
			char nom_dossier [50];
			char saisie[50];
			strcpy(nom_dossier, "./save/");

			printf("sauvegardes disponibles :\n");
			printdir(nom_dossier, 0);
			printf("Veuillez choisir une sauvegarde : ");

			scanf("%s", saisie);
			strcat(nom_dossier, saisie);
			FILE* fichier = fopen(nom_dossier, "r+");
			if(fichier)
			{
				SPartie* partie = partie_charge(fichier);
				if(partie)
				{
					rejouerPartie(partie);
					jouerPartie(partie);
					detruirePartie(partie);
				}
				else
				{
					printf("Erreur : \n"
							"=>	!!! La partie n'a pas pu être chargée correctement.\n");
				}
			}
			else
			{
				printf("Erreur : \n"
						"=>	!!! Le fichier de sauvegarde demandé n'est présent.\n");
			}
			fclose(fichier);
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
	printf("\n===============================================================================\n");
	printf("  OooOoo o.OOoOoo O       o       o.OOOo.   o.OOoOoo        .oOOOo.   .oOOOo.  \n");
	printf("      O   O       o       O        O    `o   O             .O     o  .O     o. \n");
	printf("      o   o       O       o        o      O  o             o         O       o \n");
	printf("      O   ooOO    o       o        O      o  ooOO          O         o       O \n");
	printf("      o   O       o       O        o      O  O             O   .oOOo O       o \n");
	printf("      O   o       O       O        O      o  o             o.      O o       O \n");
	printf("O     o   O       `o     Oo        o    .O'  O              O.    oO `o     O' \n");
	printf("`OooOO'  ooOooOoO  `OoooO'O        OooOO'   ooOooOoO         `OooO'   `OoooO'  \n");
	printf("===============================================================================\n\n");

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
