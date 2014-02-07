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
#include "utilsGo.h"
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


//TODO : Refaire handicap
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
	res->joueur = NOIR;
	return res;
}

void detruirePartie(SPartie* partie)
{
	printf("detruireChaine\n");
	while(!listEmpty(partie->chaines)) detruireChaine(listRemove(partie->chaines, 0));
	printf("detruirePlateau\n");
	while(!listEmpty(partie->p_prec)) detruire_plateau(listRemove(partie->p_prec, 0));
	printf("detruirechaines\n");
	listDelete(partie->chaines);
	printf("detruirep_prec\n");
	listDelete(partie->p_prec);
	printf("detruirep_courant\n");
	detruire_plateau(partie->p_courant);
	printf("PARTIE\n");

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
		while ( getchar() != '\n' );

		if(!strcmp("pass", saisie))
		{
			pass_counter++;
			if(pass_counter == 2)
			{
				printf("On quitte (double pass)\n");
				quit = 1;
			}
			partie->joueur = (partie->joueur == BLANC) ? NOIR : BLANC;
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
			if(pos)
			{
				if(positionValide(partie->p_courant, pos))
				{
					if(coup_valide(partie, pos))
					{
						jouer_coup(partie, *pos);
						pass_counter = 0;
						partie->joueur = (partie->joueur == BLANC) ? NOIR : BLANC;
					}
					else
					{
						printf("Coup non autorisé, veuillez rejouer.");
					}
				}
				else
				{
					printf("Position non valide.\n\n");
				}
				free(pos);
			}
			else
			{
				printf("Commande non reconnue.");
			}
		}
	}while(!quit);

	printf("lel\n");
	// CALCUL SCORE TOUSSA TOUSSA
	return res;
}

SPartie* partie_charge(FILE* fichier)
{
	return NULL;
}

void partie_sauvegarde(SPartie* partie, FILE* fichier)
{
}

void jouer_coup(SPartie* partie, SPosition position)
{
	printf("jouer_coup\n");

	ECouleur couleur_joueur = partie->joueur;
	SPlateau* plateau = partie->p_courant;
	SChaines* chaines = partie->chaines;

	SPositions* list = listInit();
	listAdd(list, &position);

	SPosition* v_droit = voisinDroit(plateau, &position);
	SPosition* v_gauche = voisinGauche(plateau, &position);
	SPosition* v_bas = voisinBas(plateau, &position);
	SPosition* v_haut = voisinHaut(plateau, &position);

	printf("deter chaine\n");
	SChaine* chaine_droit = plateau_determiner_chaine(chaines, v_droit);
	SChaine* chaine_gauche = plateau_determiner_chaine(chaines,v_gauche);
	SChaine* chaine_bas = plateau_determiner_chaine(chaines,v_bas);
	SChaine* chaine_haut = plateau_determiner_chaine(chaines,v_haut);

	plateau_set(plateau, &position, couleur_joueur);

	if(v_droit) printf("v_droit OK !\n"); else printf("v_droit NOK !\n");
	if(v_gauche) printf("v_gauche OK !\n"); else printf("v_gauche NOK !\n");
	if(v_bas) printf("v_bas OK !\n"); else printf("v_bas NOK !\n");
	if(v_haut) printf("v_haut OK !\n"); else printf("v_haut NOK !\n");

	if(chaine_droit) printf("chaine_droit OK !\n"); else printf("chaine_droit NOK !\n");
	if(chaine_gauche) printf("chaine_gauche OK !\n"); else printf("chaine_gauche NOK !\n");
	if(chaine_bas) printf("chaine_bas OK !\n"); else printf("chaine_bas NOK !\n");
	if(chaine_haut) printf("chaine_haut OK !\n"); else printf("chaine_haut NOK !\n");



	printf("concat\n");
	if(v_droit && chaine_droit && plateau_get(plateau,v_droit)==couleur_joueur) listConcatUnique(list, listEnsembleColore(chaine_droit), positionsEgale);
	if(v_bas && chaine_bas && plateau_get(plateau,v_bas)==couleur_joueur) listConcatUnique(list, listEnsembleColore(chaine_bas), positionsEgale);
	if(v_gauche && chaine_gauche && plateau_get(plateau,v_gauche)==couleur_joueur) listConcatUnique(list, listEnsembleColore(chaine_gauche), positionsEgale);
	if(v_haut && chaine_haut && plateau_get(plateau,v_haut)==couleur_joueur) listConcatUnique(list, listEnsembleColore(chaine_haut), positionsEgale);

	// création de la nouvelle chaine
	actualiseChaines(chaines, list);

	SChaine* new_chaine = creerEnsembleColore();
	setCouleurEnsembleColore(new_chaine, couleur_joueur);
	listHead(list);
	do
	{
		listAdd(listEnsembleColore(new_chaine), listCurrent(list));
	}while(listNext(list));

	listDelete(list);
	listAdd(chaines, new_chaine);
}

int coup_valide(SPartie* partie, SPosition* position)
{
	printf("coup_valide\n");

	ECouleur couleur_joueur = partie->joueur;
	SPlateau* plateau = partie->p_courant;
	SChaines* chaines = partie->chaines;

	SPion* pion = creerPion(*position, couleur_joueur);
	SPosition* v_droit = voisinDroit(plateau,position);
	SPosition* v_gauche = voisinGauche(plateau,position);
	SPosition* v_bas = voisinBas(plateau,position);
	SPosition* v_haut = voisinHaut(plateau,position);

	SChaine* chaine_droit = plateau_determiner_chaine(chaines,v_droit);
	SChaine* chaine_gauche = plateau_determiner_chaine(chaines,v_gauche);
	SChaine* chaine_bas = plateau_determiner_chaine(chaines,v_bas);
	SChaine* chaine_haut = plateau_determiner_chaine(chaines,v_haut);

	if(plateau_get(plateau, position)!=VIDE) return 0;

	//cas de capture, on capture !!!
	if(v_droit && chaine_droit && couleur_joueur != plateau_get(plateau,v_droit) && determineLiberte(plateau,chaine_droit)==NULL)
	{
		plateau_realiser_capture(plateau,chaines,chaine_droit);
		detruirePion(pion);
		return 1;
	}
	if(v_gauche && chaine_gauche && couleur_joueur != plateau_get(plateau,v_gauche) && determineLiberte(plateau,chaine_gauche)==NULL)
	{
		plateau_realiser_capture(plateau,chaines,chaine_gauche);
		detruirePion(pion);
		return 1;
	}
	if(v_bas && chaine_bas && couleur_joueur != plateau_get(plateau,v_bas)&& determineLiberte(plateau,chaine_bas)==NULL)
	{
		plateau_realiser_capture(plateau,chaines,chaine_bas);
		detruirePion(pion);
		return 1;
	}
	if(v_haut && chaine_haut && couleur_joueur != plateau_get(plateau,v_haut) && determineLiberte(plateau,chaine_haut)==NULL)
	{
		plateau_realiser_capture(plateau,chaines,chaine_haut);
		detruirePion(pion);
		return 1;
	}

	if(listEmpty(libertesAdjacente(plateau,pion)) == 1)
	{
		if(v_haut && chaine_haut && couleur_joueur==plateau_get(plateau,v_haut) && determineLiberte(plateau,chaine_haut)==NULL)
			detruirePion(pion);
			return 0;
		if(v_droit && chaine_droit && couleur_joueur==plateau_get(plateau,v_droit) && determineLiberte(plateau,chaine_droit)==NULL)
			detruirePion(pion);
			return 0;
		if(v_gauche && chaine_gauche && couleur_joueur==plateau_get(plateau,v_gauche) && determineLiberte(plateau,chaine_gauche)==NULL)
			detruirePion(pion);
			return 0;
		if(v_bas && chaine_bas && couleur_joueur==plateau_get(plateau,v_bas) && determineLiberte(plateau,chaine_bas)==NULL)
			detruirePion(pion);
			return 0;
	}
	else
	{
		detruirePion(pion);
		return 1;
	}
}

