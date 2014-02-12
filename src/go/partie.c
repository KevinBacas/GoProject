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

SPartie* partie_charge(FILE* fichier)
{
	SPartie* res = NULL;
	if(fichier)
	{
		res = malloc(sizeof(SPartie));

		printf("a\n");
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

		printf("%d %f %d %d\n", joueur, komi, type_j1, type_j2);
		printf("b\n");
		res->joueur = (ECouleur)joueur;
		res->komi = komi;
		res->t_j1 = (ETypeJoueur)type_j1;
		res->t_j2 = (ETypeJoueur)type_j2;
		printf("c\n");

		res->p_courant = plateau_chargement(fichier);
		printf("d\n");
		if(res->p_courant)
		{
			printf("e\n");
			int nb_plats = 0;
			fscanf(fichier, "%d\n", &nb_plats);
			res->p_prec = listInit();
			printf("f\n");

			int i = 0;
			SPlateau* plat_curr = NULL;

			do
			{
				printf("g\n");
				plat_curr = plateau_chargement(fichier);

				if(plat_curr)
				{
					listAdd(res->p_prec, plat_curr);
				}
				++i;
			}while(plat_curr && (i < nb_plats));

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
	printf("<lettre><num> : Position sur laquelle jouer (ex : A0).\n");
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
		FILE* fichier = fopen("sauvegarde.save", "w");
		partie_sauvegarde(partie, fichier);
		fclose(fichier);
		res = SAVE;
	}
	else if(!strcmp("giveup", saisie))
	{
		res = GIVEUP;
		// Le joueur courant abandonne.
	}
	else if(!strcmp("undo", saisie))
	{
		// On retourne un coup en arriere.
	}
	else if(!strcmp("redo", saisie))
	{
		// On retourne un coup en arriere.
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
					printf("Coup non autoris√©, veuillez rejouer.");
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
	int nb_tour = 0;

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
		nb_tour++;
		printf("tour num : %d\n", nb_tour);

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

	// cr√©ation de la nouvelle chaine
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

//	displayChaine(new_chaine);


//	printf("----- DISPLAY CHAINES -----\n");
//	printf("%d chaines\n", listSize(chaines));
//	listHead(chaines);
//	do
//	{
//		displayChaine(listCurrent(chaines));
//	}while(listNext(chaines));
//	printf("----- DISPLAY CHAINES -----\n");

}

//TODO : changer les commentaires en code ! ne pas oublier le prototype et de mettre dans partie le tableau 2 dim de position.
int coup_valide(SPartie* partie, SPosition* position)
{
	//printf("coup_valide\n");

	ECouleur couleur_joueur = partie->joueur;
	SPlateau* plateau = partie->p_courant;
	SChaines* chaines = partie->chaines;

	/* _______ for(i==0; i<4; ++i){
	 *			*tab_pos = NULL;
	 *			*(tab_pos+1) = NULL;
	 *			*(tab_pos+2) =NULL;
	 *			*(tab_pos+3)=NULL;
	 *			}
	*/
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
		free(v_droit);
		++nb_captures;
		/*
		 *
		 *
		 * *tab_pos = v_droit;
		 */
	}
	listDelete(libertes);
	libertes = NULL;

	libertes = determineLiberte(plateau,chaine_gauche);
	if(v_gauche && chaine_gauche && couleur_joueur != plateau_get(plateau,v_gauche) && listEmpty(libertes))
	{
		plateau_realiser_capture(plateau, chaines, chaine_gauche);
		free(v_gauche);
		++nb_captures;
		/* *(tab_pos+1) = v_gauche;
		 *
		 *
		 */
	}
	listDelete(libertes);
	libertes = NULL;

	libertes = determineLiberte(plateau,chaine_bas);
	if(v_bas && chaine_bas && couleur_joueur != plateau_get(plateau,v_bas)&& listEmpty(libertes))
	{
		plateau_realiser_capture(plateau, chaines, chaine_bas);
		free(v_bas);
		++nb_captures;
		/* *(tab_pos+2) = v_bas;
		 *
		 *
		 */
	}
	listDelete(libertes);
	libertes = NULL;

	libertes = determineLiberte(plateau,chaine_haut);
	if(v_haut && chaine_haut && couleur_joueur != plateau_get(plateau,v_haut) && listEmpty(libertes))
	{
		plateau_realiser_capture(plateau, chaines, chaine_haut);
		free(v_haut);
		++nb_captures;
		/* *(tab_pos+3) = v_haut;
		 *
		 *
		 */
	}
	listDelete(libertes);
	libertes = NULL;

	if(nb_captures)
	{
		/*gererKO(plateau, tab_de_stockage, tab_pos);
		 *
		 *  j'ai changÈ la place de plateau par rapport au prototype que jtÈ filÈ
		 */
		return 1;

	}

	// !!
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
	/*gererKO(plateau, tab_de_stockage, tab_pos);
	 *
	 * ici tab_pos doit valloir NULL pour chaque case.
	 */
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
            if(couleur_pos != VIDE || couleur_pos !=KO);
            {
                jouer_coup(partie,couleur_pos, position);
            }
        }
    }
}
