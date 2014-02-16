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
#include <time.h>

typedef SList SPlateaux;

typedef enum TypeJoueur
{
	HUMAN,
	BOT
} ETypeJoueur;

typedef enum
{
	NVALIDE,
	SAVE,
	PASS,
	COUP,
	GIVEUP,
	QUIT
} ECoupJoue;

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
		do
		{
			printf("Renseigner la Nature du joueur 1 (H pour Humain, B pour Bot) : ");
			scanf("%c", &rep);
			getchar();
		}while(rep != 'H' && rep != 'B');
		partie->t_j1 = rep == 'H' ? HUMAN : BOT;
		rep = ' ';

		do
		{
			printf("Renseigner la Nature du joueur 2 (H pour Humain, B pour Bot) : ");
			scanf("%c", &rep);
			getchar();
		}while(rep != 'H' && rep != 'B');
		partie->t_j2 = rep == 'H' ? HUMAN : BOT;
		break;
	}
	case 1:
	{
		char rep = ' ';
		do
		{
			printf("Taille du plateau (A = 9x9, B = 13x13, C = 19x19) : ");
			scanf("%c", &rep);
			getchar();
		}while(!(rep == 'A' || rep == 'B' || rep == 'C'));
		int taille = rep == 'A' ? 9 : (rep == 'B' ? 13 : 19);
		partie->p_courant = init_plateau(taille);
		break;
	}
	case 2:
	{
		int rep = -1;

		do{
			printf("Renseigner le handicap (de 0 a 9) : ");
			scanf("%d", &rep);
			getchar();
		}while(!(rep < 10 && rep > -1));

		if(rep == 0)
		{
			partie->joueur = NOIR;
			partie->komi = 7.5;
		}
		else
		{
			partie->joueur = rep == 1 ? NOIR : BLANC;
			partie->komi = 0.5;

			char name[50];
			sprintf(name, "./preset/handi%d-%d.txt", rep, taille_plateau(partie->p_courant));
			printf("%s\n", name);

			FILE* fichier = fopen(name, "r+");
			if(fichier)
			{
				SPlateau* plateau = plateau_chargement(fichier);
				if(plateau)
				{
					plateau_copie(plateau, partie->p_courant);
					detruire_plateau(plateau);
					rejouerPartie(partie);
				}
				else
				{
					printf("Le fichier d'handicap n'a pas pu etre charge.\n");
				}
			}
			else
			{
				printf("Le fichier d'handicap n'a pas pu etre charge.\n");
			}
		}
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
	res->chaines = listInit();
	res->p_prec = listInit();
	for(i = 0 ; i < nb_question ; ++i)
	{
		fonctionQuestions(i, res);
	}
	return res;
}

SPartie* partie_charge(FILE* fichier)
{
	SPartie* res = NULL;
	if(fichier)
	{
		res = malloc(sizeof(SPartie));

		int joueur = 0;
		float komi = 0.0f;
		int type_j1 = 0;
		int type_j2 = 0;

		fscanf(fichier,
				"%d %f %d %d\n",
				&joueur,
				&komi,
				&type_j1,
				&type_j2);

		if(feof(fichier))
		{
			free(res);
			res = NULL;
			return res;
		}

		res->joueur = (ECouleur)joueur;
		res->komi = komi;
		res->t_j1 = (ETypeJoueur)type_j1;
		res->t_j2 = (ETypeJoueur)type_j2;

		res->p_courant = plateau_chargement(fichier);
		if(res->p_courant)
		{
			int nb_plats = 0;
			fscanf(fichier, "%d\n", &nb_plats);
			if(feof(fichier))
			{
				free(res);
				res = NULL;
				return res;
			}

			res->p_prec = listInit();

			int i = 0;
			SPlateau* plat_curr = NULL;

			do
			{
				printf("%d tour\n", i);
				plat_curr = plateau_chargement(fichier);

				if(plat_curr)
				{
					printf("a\n");
					listAdd(res->p_prec, plat_curr);
					plateau_affichage(plat_curr);
				}
				else
				{
					printf("b\n");
					free(res);
					res = NULL;
				}
				++i;
			}while(plat_curr && (i < nb_plats-1));

			res->chaines = listInit();
		}
		else
		{
			free(res);
			res = NULL;
		}
	}
	return res;
}

void partie_sauvegarde(SPartie* partie, FILE* fichier)
{
	if(partie && fichier)
	{
		// joueur courant, komi, type J1, type J2
		fprintf(fichier, "%d %f %d %d\n",
				partie->joueur,
				partie->komi,
				partie->t_j1,
				partie->t_j2);

		SPlateau* plat_courant = partie->p_courant;
		if(plat_courant)
		{
			plateau_sauvegarde(plat_courant, fichier);
		}

		SPlateaux* plats = partie->p_prec;
		if(plats && !listEmpty(plats))
		{
			fprintf(fichier, "%d\n", listSize(plats));
			listHead(plats);
			do
			{
				plateau_sauvegarde(listCurrent(plats), fichier);
			}while(listNext(plats));
		}
	}
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

ECoupJoue joueur_terminal(SPartie* partie)
{
	ECoupJoue res = COUP;

	printf("Joueur : %s.\n", partie->joueur == BLANC ? "BlLanc" : "Noir");
	printf("<lettre><num> : Position sur laquelle jouer (ex : E5).\n");
	printf("pass : Passer.\n");
	printf("save : Sauvegarder la partie.\n");
	printf("giveup : Abandonner.\n");
	printf("undo : Revenir un coup en arriere.\n");
	printf("redo : Revenir un coup en avant.\n");
	printf("quit : Quitter la partie.\n");

	char saisie[50];
	scanf("%s", saisie);
	while ( getchar() != '\n' );

	if(!strcmp("pass", saisie))
	{
		res = PASS;
	}
	else if(!strcmp("save", saisie))
	{
		char nom_dossier [50];
		char saisie[50];
		strcpy(nom_dossier, "./save/");

		printf("Veuillez choisir un nom de sauvegarde : ");

		scanf("%s", saisie);
		strcat(nom_dossier, saisie);
		FILE* fichier = fopen(nom_dossier, "w");
		partie_sauvegarde(partie, fichier);
		fclose(fichier);
		res = SAVE;
	}
	else if(!strcmp("giveup", saisie))
	{
		res = GIVEUP;
	}
	else if(!strcmp("quit", saisie))
	{
		res = QUIT;
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
					jouer_coup(partie, partie->joueur, pos);
				}
				else
				{
					res = NVALIDE;
					free(pos);
					printf("Coup non autorisé, veuillez rejouer.");
				}
			}
			else
			{
				res = NVALIDE;
				free(pos);
				printf("Position non valide.\n\n");
			}
		}
		else
		{
			printf("Commande non reconnue.");
		}
	}

	return res;
}

ECoupJoue ordinateur_jouer(SPartie* partie)
{
	ECoupJoue coup;
	srand(time(NULL));
	int r = rand() % 100;

	if(r < 2)
	{
		coup = PASS;
	}
	else
	{
		SPosition* pos = malloc(sizeof(SPosition));
		pos->x = -1;
		pos->y = -1;
		while(!coup_valide(partie, pos))
		{
			pos->x = rand() % taille_plateau(partie->p_courant);
			pos->y = rand() % taille_plateau(partie->p_courant);
		}

		jouer_coup(partie, partie->joueur, pos);

		coup = COUP;
	}

	return coup;
}

float jouerPartie(SPartie* partie)
{
	int quit = 0;
	int pass_counter = 0;
	float res = 0;

	do
	{
		plateau_affichage(partie->p_courant);

		ECoupJoue coup = QUIT;
		ETypeJoueur type = partie->joueur == BLANC ? partie->t_j1 : partie->t_j2;

		if(type == BOT)
			coup = ordinateur_jouer(partie);
		else
			coup = joueur_terminal(partie);

		switch(coup)
		{
		case PASS:
		{
			partie->joueur = (partie->joueur == BLANC) ? NOIR : BLANC;
			pass_counter++;
			if(pass_counter == 2)
			{
				quit = 1;
			}
			break;
		}
		case NVALIDE:
			break;
		case COUP:
			partie->joueur = (partie->joueur == BLANC) ? NOIR : BLANC;
			SPlateau* plateau = init_plateau(taille_plateau(partie->p_courant));
			plateau_copie(partie->p_courant, plateau);
			listAdd(partie->p_prec, plateau);
			pass_counter = 0;
			break;
		case QUIT:
			quit = 1;
			break;
		case GIVEUP:
			quit = 2;
			break;
		case SAVE:
			break;
		}

	}while(!quit);

	if(quit == 1)
	{
		res = compter_point(partie->p_courant, partie->komi);
	}
	else
	{
		res = partie->joueur == BLANC ? -1 : 1;
	}

	return res;
}

void jouer_coup(SPartie* partie, ECouleur couleur, SPosition* position)
{
	ECouleur couleur_joueur = couleur;
	SPlateau* plateau = partie->p_courant;
	SChaines* chaines = partie->chaines;

	SPositions* list = listInit();
	listAdd(list, position);

	SPosition* v_droit = voisinDroit(plateau, position);
	SChaine* chaine_droit = plateau_determiner_chaine(chaines, v_droit);
	if(v_droit && chaine_droit && plateau_get(plateau,v_droit)==couleur_joueur)
		listConcatUnique(list, listEnsembleColore(chaine_droit), positionsEgale);

	SPosition* v_gauche = voisinGauche(plateau, position);
	SChaine* chaine_gauche = plateau_determiner_chaine(chaines, v_gauche);
	if(v_gauche && chaine_gauche && plateau_get(plateau,v_gauche)==couleur_joueur)
		listConcatUnique(list, listEnsembleColore(chaine_gauche), positionsEgale);

	SPosition* v_bas = voisinBas(plateau, position);
	SChaine* chaine_bas = plateau_determiner_chaine(chaines, v_bas);
	if(v_bas && chaine_bas && plateau_get(plateau,v_bas)==couleur_joueur)
		listConcatUnique(list, listEnsembleColore(chaine_bas), positionsEgale);

	SPosition* v_haut = voisinHaut(plateau, position);
	SChaine* chaine_haut = plateau_determiner_chaine(chaines, v_haut);
	if(v_haut && chaine_haut && plateau_get(plateau,v_haut)==couleur_joueur)
		listConcatUnique(list, listEnsembleColore(chaine_haut), positionsEgale);


	// On actualise les chaines
	actualiseChaines(chaines, list);

	// création de la nouvelle chaine
	SChaine* new_chaine = creerEnsembleColore();
	setCouleurEnsembleColore(new_chaine, couleur_joueur);
	listHead(list);
	do
	{
		listAdd(listEnsembleColore(new_chaine), listCurrent(list));
	}while(listNext(list));

	// On detruit la chaine
	listDelete(list);
	// On ajoute la liste colore a la liste des chaines
	listAdd(chaines, new_chaine);
}

int coup_valide(SPartie* partie, SPosition* position)
{

	ECouleur couleur_joueur = partie->joueur;
	SPlateau* plateau = partie->p_courant;
	SChaines* chaines = partie->chaines;


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

	// Verifications pour le KO
	// Si le plateau d'il y a deux tours est identique au plateau courant
	// Alors c'est un KO
	if(listSize(partie->p_prec) > 2)
	{
		SPlateau* p_prec_2_t = listGetElement(partie->p_prec, listSize(partie->p_prec) - 1);
		if( plateau_est_identique(partie->p_courant, p_prec_2_t))
		{
			plateau_set(plateau, position, VIDE);
			return 0;
		}
	}

	//cas de capture, on capture !!!
	int nb_captures = 0;
	SLibertes* libertes = NULL;

	libertes = determineLiberte(plateau,chaine_droit);
	if(v_droit && chaine_droit && couleur_joueur != plateau_get(plateau,v_droit) && listEmpty(libertes))
	{
		plateau_realiser_capture(plateau, chaines, chaine_droit);
		free(v_droit);
		++nb_captures;
	}
	listDelete(libertes);
	libertes = NULL;

	libertes = determineLiberte(plateau,chaine_gauche);
	if(v_gauche && chaine_gauche && couleur_joueur != plateau_get(plateau,v_gauche) && listEmpty(libertes))
	{
		plateau_realiser_capture(plateau, chaines, chaine_gauche);
		free(v_gauche);
		++nb_captures;
	}
	listDelete(libertes);
	libertes = NULL;

	libertes = determineLiberte(plateau,chaine_bas);
	if(v_bas && chaine_bas && couleur_joueur != plateau_get(plateau,v_bas)&& listEmpty(libertes))
	{
		plateau_realiser_capture(plateau, chaines, chaine_bas);
		free(v_bas);
		++nb_captures;
	}
	listDelete(libertes);
	libertes = NULL;

	libertes = determineLiberte(plateau,chaine_haut);
	if(v_haut && chaine_haut && couleur_joueur != plateau_get(plateau,v_haut) && listEmpty(libertes))
	{
		plateau_realiser_capture(plateau, chaines, chaine_haut);
		free(v_haut);
		++nb_captures;
	}
	listDelete(libertes);
	libertes = NULL;

	if(nb_captures)
	{
		return 1;

	}

	if(listEmpty(libertesAdjacente(plateau,position)))
	{
		SLibertes* lib_haut 	= determineLiberte(plateau, chaine_haut);
		SLibertes* lib_droit 	= determineLiberte(plateau, chaine_droit);
		SLibertes* lib_gauche 	= determineLiberte(plateau, chaine_gauche);
		SLibertes* lib_bas 		= determineLiberte(plateau, chaine_bas);
		if(    (v_haut 		&& chaine_haut 		&& couleur_joueur==plateau_get(plateau,v_haut) 		&& listEmpty(lib_haut))
			|| (v_droit 	&& chaine_droit 	&& couleur_joueur==plateau_get(plateau,v_droit) 	&& listEmpty(lib_droit))
			|| (v_gauche 	&& chaine_gauche 	&& couleur_joueur==plateau_get(plateau,v_gauche) 	&& listEmpty(lib_gauche))
			|| (v_bas 		&& chaine_bas 		&& couleur_joueur==plateau_get(plateau,v_bas) 		&& listEmpty(lib_bas))
			)
		{
			plateau_set(plateau, position, VIDE);
			listDelete(lib_haut);
			listDelete(lib_droit);
			listDelete(lib_gauche);
			listDelete(lib_bas);
			free(v_droit);
			free(v_gauche);
			free(v_bas);
			free(v_haut);
			return 0;
		}
	}
	return 1;
}

void rejouerPartie(SPartie* partie)
{
    int x;
    int y;
    SPlateau* plateau = partie->p_courant;
    int taille = taille_plateau(plateau);

    for(x=0; x < taille; ++x)
    {
        for(y=0; y<taille; ++y)
        {
            SPosition* position = creerPosition(x,y);
            ECouleur couleur_pos = plateau_get(plateau, position);
            if(couleur_pos != VIDE);
            {
                jouer_coup(partie,couleur_pos, position);
            }
        }
    }
}
