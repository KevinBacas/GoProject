#include <stdlib.h>
#include <stdio.h>
#include "territoire.h"


ECouleur couleurVoisin(SPlateau* plateau, SPosition* position)
{
	int x = abscissePosition(position);
	int y = ordonneePosition(position);
	SPosition* haut = creerPosition(x+1,y);
	SPosition* bas = creerPosition(x-1,y);
	SPosition* gauche = creerPosition(x,y-1);
	SPosition* droite = creerPosition(x,y+1);

	ECouleur c1 = plateau_get(plateau, haut);
	ECouleur c2 = plateau_get(plateau, bas);
	ECouleur c3 = plateau_get(plateau, gauche);
	ECouleur c4 = plateau_get(plateau, droite);

	if(c1==NOIR && c2!=BLANC && c3!=BLANC && c4!=BLANC) return NOIR;
	if(c1==BLANC && c2!=NOIR && c3!=NOIR && c4!=NOIR) return BLANC;
	if(c1!=BLANC && c2==NOIR && c3!=BLANC && c4!=BLANC)return NOIR;
	if(c1!=NOIR && c2==BLANC && c3!=NOIR && c4!=NOIR) return BLANC;
	if(c1!=BLANC && c2!=BLANC && c3==NOIR && c4!=BLANC)return NOIR;
	if(c1!=NOIR && c2!=NOIR && c3==BLANC && c4!=NOIR) return BLANC;
	if(c1!=BLANC && c2!=BLANC && c3!=BLANC && c4!=NOIR)return NOIR;
	if(c1!=NOIR && c2!=NOIR && c3!=NOIR && c4!=BLANC) return BLANC;

	if(c1==VIDE && c2==VIDE && c3 == VIDE && c4==VIDE) return BORD;
	else return VIDE;
}

ECouleur compareCouleur(ECouleur couleur1, ECouleur couleur2)
{
	if(couleur1 == BORD || couleur1 == KO)
	{
		if(couleur2==KO) return BORD;
		else return couleur2;
	}
	if(couleur2 == BORD || couleur2 == KO)
	{
		if(couleur1==KO) return BORD;
		else return couleur1;
	}
	if(couleur1==couleur2) return couleur1;
	else return VIDE;
}

ECouleur determineCouleurTerritoire(SPlateau* plateau, STerritoire* territoire, ECouleur couleur)
{
	ECouleur couleur_de_comparaison = couleur;
	SPosition* position_territoire = listCurrent(listEnsembleColore(territoire));
	if(listEmpty(listCurrent(listEnsembleColore(territoire)))) return BORD;

	return compareCouleur(couleur_de_comparaison, determineCouleurTerritoire(plateau, listNext(listEnsembleColore(territoire), couleurVoisin(plateau,position_territoire))));
}

