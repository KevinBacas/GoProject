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
	//if(!pos) return BORD;
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
	case'_' : return VIDE;
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
	case VIDE : return '_';
	case BLANC : return 'B';
	case BORD : return '-';
	default : return 'D';
	}
}

void plateau_affichage(SPlateau* plateau)
{
	int taille = plateau->taille;
	int i,j;
	printf(" ");
	for(j = 0 ; j < taille ; ++j)
	{
		printf("%c", 'a'+j);
	}
	printf("\n");

	for(i = 0 ; i < taille ; ++i)
	{
		printf("%d", i);
		for(j = 0 ; j < taille ; ++j)
		{
			SPosition pos;
			pos.x = i;
			pos.y = j;
			printf("%c", couleur_to_char(plateau_get(plateau, &pos)));
		}
		printf("%d\n", i);
	}

	printf(" ");
	for(j = 0 ; j < taille ; ++j)
	{
		printf("%c", 'a'+j);
	}
	printf("\n");
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

int positionValide(SPlateau* plateau,SPosition* position)
{
	int x = abscissePosition(position);
	int y = ordonneePosition(position);
	int taille=taille_plateau(plateau);
	if(x >= taille || x < 0 || y >= taille || y<0) return 0;
	else return 1;
}

SPosition* voisinDroit(SPlateau* plateau, SPosition* position)
{
	ECouleur coul = plateau_get(plateau,positionDroite(position));
	if(coul == VIDE || coul == KO || coul == BORD) return NULL;
	else
	{
		return positionDroite(position);
	}
}

SPosition* voisinGauche(SPlateau* plateau, SPosition* position)
{
	ECouleur coul = plateau_get(plateau,positionGauche(position));
	if(coul == VIDE || coul == KO || coul == BORD) return NULL;
	else
	{
		return positionGauche(position);
	}
}

SPosition* voisinHaut(SPlateau* plateau, SPosition* position)
{
	ECouleur coul = plateau_get(plateau,positionHaut(position));
	if(coul == VIDE || coul == KO || coul == BORD) return NULL;
	else
	{
		return positionHaut(position);
	}
}

SPosition* voisinBas(SPlateau* plateau, SPosition* position)
{
	ECouleur coul = plateau_get(plateau,positionBas(position));
	if(coul == VIDE || coul == KO || coul == BORD) return NULL;
	else
	{
		return positionBas(position);
	}
}
