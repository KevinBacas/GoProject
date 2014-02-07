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
