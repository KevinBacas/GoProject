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
						jouer_coup(partie, pos);
						pass_counter = 0;
						partie->joueur = (partie->joueur == BLANC) ? NOIR : BLANC;
					}
					else
					{
						free(pos);
						printf("Coup non autorisé, veuillez rejouer.");
					}
				}
				else
				{
					free(pos);
					printf("Position non valide.\n\n");
				}
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

void jouer_coup(SPartie* partie, SPosition* position)
{
	printf("jouer_coup\n");

	ECouleur couleur_joueur = partie->joueur;
	SPlateau* plateau = partie->p_courant;
	SChaines* chaines = partie->chaines;

	SPositions* list = listInit();
	listAdd(list, position);

	SPosition* v_droit = voisinDroit(plateau, position);
	SPosition* v_gauche = voisinGauche(plateau, position);
	SPosition* v_bas = voisinBas(plateau, position);
	SPosition* v_haut = voisinHaut(plateau, position);

	SChaine* chaine_droit = plateau_determiner_chaine(chaines, v_droit);
	SChaine* chaine_gauche = plateau_determiner_chaine(chaines, v_gauche);
	SChaine* chaine_bas = plateau_determiner_chaine(chaines, v_bas);
	SChaine* chaine_haut = plateau_determiner_chaine(chaines, v_haut);

	//plateau_set(plateau, position, couleur_joueur);


	if(v_droit && chaine_droit && plateau_get(plateau,v_droit)==couleur_joueur) listConcatUnique(list, listEnsembleColore(chaine_droit), positionsEgale);
	if(v_bas && chaine_bas && plateau_get(plateau,v_bas)==couleur_joueur) listConcatUnique(list, listEnsembleColore(chaine_bas), positionsEgale);
	if(v_gauche && chaine_gauche && plateau_get(plateau,v_gauche)==couleur_joueur) listConcatUnique(list, listEnsembleColore(chaine_gauche), positionsEgale);
	if(v_haut && chaine_haut && plateau_get(plateau,v_haut)==couleur_joueur) listConcatUnique(list, listEnsembleColore(chaine_haut), positionsEgale);

	// On actualise les chaines
	actualiseChaines(chaines, list);

	// création de la nouvelle chaine
	SChaine* new_chaine = creerEnsembleColore();
	setCouleurEnsembleColore(new_chaine, couleur_joueur);

	listConcatUnique(listEnsembleColore(new_chaine), list, positionsEgale);

	// On detruit la chaine
	//listDelete(list);
	// On ajoute la liste colore a la liste des chaines
	listAdd(chaines, new_chaine);

	displayChaine(new_chaine);



	printf("----- DISPLAY CHAINES -----\n");
	printf("%d chaines\n", listSize(chaines));
	listHead(chaines);
	do
	{
		displayChaine(listCurrent(chaines));
	}while(listNext(chaines));
	printf("----- DISPLAY CHAINES -----\n");
}

int coup_valide(SPartie* partie, SPosition* position)
{
	printf("coup_valide\n");

	ECouleur couleur_joueur = partie->joueur;
	SPlateau* plateau = partie->p_courant;
	SChaines* chaines = partie->chaines;

	//SPion* pion = creerPion(*position, couleur_joueur);
	SPosition* v_droit = voisinDroit(plateau,position);
	SPosition* v_gauche = voisinGauche(plateau,position);
	SPosition* v_bas = voisinBas(plateau,position);
	SPosition* v_haut = voisinHaut(plateau,position);

	SChaine* chaine_droit = plateau_determiner_chaine(chaines, v_droit);
	SChaine* chaine_gauche = plateau_determiner_chaine(chaines, v_gauche);
	SChaine* chaine_bas = plateau_determiner_chaine(chaines, v_bas);
	SChaine* chaine_haut = plateau_determiner_chaine(chaines, v_haut);

	if(plateau_get(plateau, position)!=VIDE) return 0;

	plateau_set(plateau, position, couleur_joueur);
	//cas de capture, on capture !!!
	int nb_captures = 0;
	SLibertes* libertes = NULL;

	libertes = determineLiberte(plateau,chaine_droit);
	if(v_droit && chaine_droit && couleur_joueur != plateau_get(plateau,v_droit) && listEmpty(libertes))
	{
		plateau_realiser_capture(plateau, chaines, chaine_droit);
		++nb_captures;
	}
	free(libertes);
	libertes = NULL;

	libertes = determineLiberte(plateau,chaine_gauche);
	if(v_gauche && chaine_gauche && couleur_joueur != plateau_get(plateau,v_gauche) && listEmpty(libertes))
	{
		plateau_realiser_capture(plateau, chaines, chaine_gauche);
		++nb_captures;
	}
	free(libertes);
	libertes = NULL;

	libertes = determineLiberte(plateau,chaine_bas);
	if(v_bas && chaine_bas && couleur_joueur != plateau_get(plateau,v_bas)&& listEmpty(libertes))
	{
		plateau_realiser_capture(plateau, chaines, chaine_bas);
		++nb_captures;
	}
	free(libertes);
	libertes = NULL;

	libertes = determineLiberte(plateau,chaine_haut);
	if(v_haut && chaine_haut && couleur_joueur != plateau_get(plateau,v_haut) && listEmpty(libertes))
	{
		plateau_realiser_capture(plateau, chaines, chaine_haut);
		++nb_captures;
	}
	free(libertes);
	libertes = NULL;

	if(nb_captures)
	{
		printf("%d capture(s)\n", nb_captures);
		return 1;
	}


	printf("END\n");
	if(listEmpty(libertesAdjacente(plateau,position)))
	{
		if(    (v_haut 		&& chaine_haut 		&& couleur_joueur==plateau_get(plateau,v_haut) 		&& listEmpty(determineLiberte(plateau,chaine_haut)))
			|| (v_droit 	&& chaine_droit 	&& couleur_joueur==plateau_get(plateau,v_droit) 	&& listEmpty(determineLiberte(plateau,chaine_droit)))
			|| (v_gauche 	&& chaine_gauche 	&& couleur_joueur==plateau_get(plateau,v_gauche) 	&& listEmpty(determineLiberte(plateau,chaine_gauche)))
			|| (v_bas 		&& chaine_bas 		&& couleur_joueur==plateau_get(plateau,v_bas) 		&& listEmpty(determineLiberte(plateau,chaine_bas)))
			)
		{
			plateau_set(plateau, position, VIDE);
			return 0;
		}
	}

	return 1;
}

