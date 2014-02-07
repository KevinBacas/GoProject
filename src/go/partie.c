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

void jouer_coup(SPartie partie, SPosition position)
{
	ECouleur couleur_joueur = partie->joueur;
	SPlateau* plateau = partie->p_courant;
	SChaines* chaines = partie->chaines;

	int compteurBizarre=0;

	SList* list = listAdd(listInit(),(void*)&position);
	SList* l1 = listInit();
	SList* l2 = listInit();
	SList* l3 = listInit();
	SList* l4 = listInit();

	SPion* pion = creerPion(&position, couleur_joueur);
	SPosition* v_droit = voisinDroit(plateau,&position);
	SPosition* v_gauche = voisinGauche(plateau,position);
	SPosition* v_bas = voisinBas(plateau,position);
	SPosition* v_haut = voisinHaut(plateau,position);

	SChaine* chaine_droit = positionDansChaines(chaines,v_droit);
	SChaine* chaine_gauche = positionDansChaines(chaines,v_gauche);
	SChaine* chaine_bas = positionDansChaines(chaines,v_bas);
	SChaine* chaine_haut = positionDansChaines(chaines,v_haut);

	plateau_set(plateau, &position,couleur_joueur);

	if(couleur_joueur==plateau_get(plateau,v_haut))
	{
		l1=listConcatUnique(chaine_haut,list);
		compteurBizarre += 1;
	}

	if(couleur_joueur==plateau_get(plateau,v_gauche))
	{
		if(compteurBizarre==1) l2=listConcatUnique(chaine_gauche,l1);
		else
		{
			l2 = listConcatUnique(chaine_gauche,list);
		}
		compteurBizarre += 2;
	}
	if(couleur_joueur==plateau_get(plateau,v_bas))
	{
		if(compteurBizarre>=2) l3 = listConcatUnique(chaine_bas,l2);
		else
		{
			if(compteurBizarre==1) l3 = listConcatUnique(chaine_bas,l1);
			else l3 = listConcatUnique(chaine_bas,list);
		}
		compteurBizarre+=4;
	}
	if(couleur_joueur==plateau_get(plateau,v_droit))
	{
		if(compteurBizarre>=4) l4 = listConcatUnique(chaine_droit,l3);
		else
		{
			if(compteurBizarre>=2) l4 = listConcatUnique(chaine_droit,l2);
			else
			{
				if(compteurBizarre==1) l4=listConcatUnique(chaine_droit,l1);
				else l4=listConcatUnique(chaine_droit,list);
			}
		}
	}
	//là il faut virer les autres chaines de la doublons de la liste de chaines
	//tet que jme suis fait chier pour RIIIIEN !a voir
}

int coup_valide(SPartie* partie, SPosition* position)
{
	ECouleur couleur_joueur = partie->joueur;
	SPlateau* plateau = partie->p_courant;
	SChaines* chaines = partie->chaines;

	SPion* pion = creerPion(&position, couleur_joueur);
	SPosition* v_droit = voisinDroit(plateau,&position);
	SPosition* v_gauche = voisinGauche(plateau,position);
	SPosition* v_bas = voisinBas(plateau,position);
	SPosition* v_haut = voisinHaut(plateau,position);

	SChaine* chaine_droit = positionDansChaines(chaines,v_droit);
	SChaine* chaine_gauche = positionDansChaines(chaines,v_gauche);
	SChaine* chaine_bas = positionDansChaines(chaines,v_bas);
	SChaine* chaine_haut = positionDansChaines(chaines,v_haut);

	if(plateau_get(plateau, position)!=VIDE) return 0;

	//cas de capture, on capture !!!
	if(couleur_joueur != plateau_get(plateau,v_droit) && determineLiberte(plateau,chaine_droit)==NULL)
	{
		plateau_realiser_capture(plateau,chaines,chaine_droit);
		detruirePion(pion);
		return 1;
	}
	if(couleur_joueur != plateau_get(plateau,v_gauche) && determineLiberte(plateau,chaine_gauche)==NULL)
	{
		plateau_realiser_capture(plateau,chaines,chaine_gauche);
		detruirePion(pion);
		return 1;
	}
	if(couleur_joueur != plateau_get(plateau,v_bas)&& determineLiberte(plateau,chaine_bas)==NULL)
	{
		plateau_realiser_capture(plateau,chaines,chaine_bas);
		detruirePion(pion);
		return 1;
	}
	if(couleur_joueur != plateau_get(plateau,v_haut) && determineLiberte(plateau,chaine_haut)==NULL)
	{
		plateau_realiser_capture(plateau,chaines,chaine_haut);
		detruirePion(pion);
		return 1;
	}

	if(listEmpty(libertesAdjacente(plateau,pion))==1)
	{
		if(couleur_joueur==plateau_get(plateau,v_haut) && determineLiberte(plateau,chaine_haut)==NULL)
			detruirePion(pion);
			return 0;
		if(couleur_joueur==plateau_get(plateau,v_droit) && determineLiberte(plateau,chaine_droit)==NULL)
			detruirePion(pion);
			return 0;
		if(couleur_joueur==plateau_get(plateau,v_gauche) && determineLiberte(plateau,chaine_gauche)==NULL)
			detruirePion(pion);
			return 0;
		if(couleur_joueur==plateau_get(plateau,v_bas) && determineLiberte(plateau,chaine_bas)==NULL)
			detruirePion(pion);
			return 0;
	}
	else
	{
		detruirePion(pion);
		return 1;
	}
}
