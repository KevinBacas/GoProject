#include <stdlib.h>
#include <stdio.h>

#include "plateau.h"
#include "pion.h"
#include "matrice.h"

struct plateau
{
	int taille;
	Matrice* grille;
};

SPlateau* init_plateau(int taille)
{
	Matrice* matrice = allouerMatrice(taille, taille);
	return creer_plateau(taille, matrice);
}

SPlateau* creer_plateau(int taille, Matrice* matrice)
{
	SPlateau* plateau = malloc(sizeof(SPlateau));
	plateau->taille = taille;
	plateau->grille = matrice;

	return plateau;
}

void detruire_plateau(SPlateau* plateau)
{
	plateau->taille = 0;
	desallouerMatrice(plateau->grille);
	free(plateau);
}

int taille_plateau(SPlateau* plateau)
{
	return plateau->taille;
}

ECouleur plateau_get(SPlateau* plateau, SPosition* pos)
{
	int x = abscissePosition(pos);
	int y = ordonneePosition(pos);
	if(x < 0 || x >= taille_plateau(plateau) || y < 0 || y >= taille_plateau(plateau)) return BORD;
	return char_to_couleur(getValeurMatrice(plateau->grille, x, y));
}

void plateau_set(SPlateau* plateau, SPosition* pos, ECouleur couleur)
{
	setValeurMatrice(plateau->grille, abscissePosition(pos), ordonneePosition(pos), couleur_to_char(couleur));
}

ECouleur char_to_couleur(char c)
{
	switch(c)
	{
	case'K' : return KO;
	case'N' : return NOIR;
	case'V' : return VIDE;
	case'B' : return BLANC;
	case'-' : return BORD;
	default : return VIDE;
	}
}

char couleur_to_char(ECouleur c)
{
	switch(c)
	{
	case KO : return 'K';
	case NOIR : return 'N';
	case VIDE : return 'V';
	case BLANC : return 'B';
	case BORD : return '-';
	default : return 'V';
	}
}
/*
int plateau_sauvegarde(SPlateau* plateau, FILE* fichier)
{
	sauvegarderMatrice(plateau->grille, fichier);
	return 1;
}
*/
/*
SPlateau* plateau_chargement(SPlateau* plateau, FILE* fichier)
{
	SPlateau* res = NULL;
	res->grille = chargerMatrice(fichier);
	if(res->grille)
	{
		plateau->taille = getNbLigne(res->grille);
	}
	ret
}
*/

SPosition* transformerPosition(SPlateau* plateau, char* saisie)
{
	char tab_abscisse[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','s','r'};
	char tab_ordonnee[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
	int x = 0;
	int y = 0;
	if(strlen(saisie)==2)
	{
		if(strchr(tab_ordonnee, (int)(*(saisie))) != NULL)
		{
			y = (int)(*(saisie));
			x = 1 + (int)'a' - (int)*(saisie+1);
		}
		else
		{
			y = (int)((*(saisie+1))-'0');
			x = (int)((*(saisie))-'a');
		}
	}
	return creerPosition(x,y);
}
