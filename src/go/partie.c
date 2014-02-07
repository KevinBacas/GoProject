/*
 * partie.c
 *
 *  Created on: Feb 6, 2014
 *      Author: dev
 */

#include "partie.h"
#include "plateau.h"
#include "liste.h"
#include "chaines.h"
#include "chaine.h"
#include "plateau.h"
#include <string.h>

typedef SList SPlateaux;

typedef enum TypeJoueur
{
	HUMAN,
	BOT
} ETypeJoueur;

struct partie
{
	SPlateau* p_courant;
	SPlateaux* p_prec;
	ECouleur joueur;
	SChaines* chaines;
	float komi;
	ETypeJoueur t_j1;
	ETypeJoueur t_j2;
};

void questionsTerminal(int i, SPartie* partie)
{
	switch(i)
	{
	case 0:
	{
		char rep = ' ';
		do{
			printf("Renseigner la Nature du joueur 1 (H pour Humain, B pour Bot) :");
			scanf("%c", &rep);
			getchar();
		}while(rep != 'H' && rep != 'B');
		partie->t_j1 = rep == 'H' ? HUMAN : BOT;
		rep = ' ';

		do{
			printf("Renseigner la Nature du joueur 2 (H pour Humain, B pour Bot) :");
			scanf("%c", &rep);
			getchar();
		}while(rep != 'H' && rep != 'B');
		partie->t_j2 = rep == 'H' ? HUMAN : BOT;
		break;
	}
	case 1:
	{
		char rep = ' ';
		do{
			printf("Renseigner le komi (A = 0.5, B = 7.5) :");
			scanf("%c", &rep);
			getchar();
		}while(!(rep == 'A' || rep == 'B'));
		partie->komi = rep == 'A' ? 0.5f : 7.5f;
		break;
	}
	case 2:
	{
		char rep = ' ';
		do{
			printf("Taille du plateau (A = 9x9, B = 13x13, C = 19x19) :");
			scanf("%c", &rep);
			getchar();
		}while(!(rep == 'A' || rep == 'B' || rep == 'C'));
		int taille = rep == 'A' ? 9 : (rep == 'B' ? 13 : 19);
		partie->p_courant = init_plateau(taille);
		break;
	}
	default: break;
	}
}

SPartie* initialisationPartie(FonctionQuestions fonctionQuestions)
{
	SPartie* res = calloc(sizeof(SPartie), 1);
	int i;
	const int nb_question = 3;
	for(i = 0 ; i < nb_question ; ++i)
	{
		fonctionQuestions(i, res);
	}
	res->chaines = listInit();
	res->p_prec = listInit();
	return res;
}

void detruirePartie(SPartie* partie)
{
	while(!listEmpty(partie->chaines)) detruireChaine(listRemove(partie->chaines, 0));
	while(!listEmpty(partie->p_prec)) detruire_plateau(listRemove(partie->p_prec, 0));
	listDelete(partie->chaines);
	listDelete(partie->p_prec);
	detruire_plateau(partie->p_courant);

	free(partie);
}

int jouerPartie(SPartie* partie)
{
	int quit = 0;
	int pass_counter = 0;
	int res = 0;

	do{
		plateau_affichage(partie->p_courant);

		printf("== Menu de jeu == \n");
		printf("E5 ou C13 (par exemple) : Position sur laquelle jouer.\n");
		printf("pass : Passer.\n");
		printf("save : Sauvegarder la partie.\n");
		printf("giveup : Abandonner.\n");
		printf("undo : Revenir un coup en arriere.\n");
		printf("quit : Quitter la partie\n");

		char saisie[50];
		scanf("%s", saisie);
		getchar();
		printf("%s\n", saisie);

		if(!strcmp("pass", saisie))
		{
			pass_counter++;
			partie->joueur = (partie->joueur == BLANC) ? NOIR : BLANC;
			// Le joueur veut passer
		}
		else if(!strcmp("save", saisie))
		{
			FILE* fichier = fopen("sauvegarde.save", "w");
			partie_sauvegarde(partie, fichier);
			fclose(fichier);
		}
		else if(!strcmp("giveup", saisie))
		{
			res = partie->joueur == BLANC ? -1 : 1;
			quit = 1;
			// Le joueur courant abandonne.
		}
		else if(!strcmp("undo", saisie))
		{
			// On retourne un coup en arriere.
		}
		else if(!strcmp("quit", saisie))
		{
			res = 0;
			quit = 1;
		}
		else
		{
			SPosition* pos = transformerPosition(saisie);
			if(positionValide(partie->p_courant, pos))
			{
				if(jouer_coup(partie, pos))
				{
					pass_counter = 0;
				}
				printf("Coup non autorisé, veuillez rejouer.");
				partie->joueur = (partie->joueur == BLANC) ? NOIR : BLANC;
			}
			else
			{
				printf("Commande non reconnue.\n\n")
			}
		}
	}while(!quit);
}

SPartie* partie_charge(FILE* fichier)
{
	return NULL;
}

void partie_sauvegarde(SPartie* partie, FILE* fichier)
{
}
