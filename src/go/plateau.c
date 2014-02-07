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

ECouleur plateau_get(SPlateau* plateau, int x, int y)
{
	if(x < 0 || x >= taille_plateau(plateau) || y < 0 || y >= taille_plateau(plateau)) return BORD;
	return char_to_couleur(getValeurMatrice(plateau->grille, x, y));
}

void plateau_set(SPlateau* plateau, int x, int y, ECouleur couleur)
{
	setValeurMatrice(plateau->grille, x, y, couleur_to_char(couleur));
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
