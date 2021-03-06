#include <stdlib.h>
#include <stdio.h>
#include "territoire.h"

//essaye de donner une couleur a une position, si on a 2 voisin de couleurs differentes non VIDE, retourne VIDE
//sinon retourne la couleur de la case d'une couleur
//si c'est vide, retourne BORD pour ne pas perturber la fonction r�cursive.
ECouleur couleurVoisin(SPlateau* plateau, SPosition* position)
{
	SPosition* haut = positionHaut(position);
	SPosition* bas = positionBas(position);
	SPosition* gauche = positionGauche(position);
	SPosition* droite = positionDroite(position);

	ECouleur c1 = plateau_get(plateau, haut);
	ECouleur c2 = plateau_get(plateau, bas);
	ECouleur c3 = plateau_get(plateau, gauche);
	ECouleur c4 = plateau_get(plateau, droite);

	ECouleur retourner = UNDEFINED;

	if(c1==NOIR && c2!=BLANC && c3!=BLANC && c4!=BLANC) retourner = NOIR;
	if(c1==BLANC && c2!=NOIR && c3!=NOIR && c4!=NOIR) retourner = BLANC;
	if(c1!=BLANC && c2==NOIR && c3!=BLANC && c4!=BLANC)retourner = NOIR;
	if(c1!=NOIR && c2==BLANC && c3!=NOIR && c4!=NOIR) retourner = BLANC;
	if(c1!=BLANC && c2!=BLANC && c3==NOIR && c4!=BLANC)retourner = NOIR;
	if(c1!=NOIR && c2!=NOIR && c3==BLANC && c4!=NOIR) retourner = BLANC;
	if(c1!=BLANC && c2!=BLANC && c3!=BLANC && c4!=NOIR)retourner = NOIR;
	if(c1!=NOIR && c2!=NOIR && c3!=NOIR && c4!=BLANC) retourner = BLANC;

	if(c1==VIDE && c2==VIDE && c3 == VIDE && c4==VIDE) retourner = BORD;
	if(retourner==UNDEFINED) retourner = VIDE;

	detruirePosition(haut);
	detruirePosition(bas);
	detruirePosition(gauche);
	detruirePosition(droite);

	return retourner;
}
//retourne VIDE si les 2 couleurs sont differentes, si elles sont pareil, retourne cette couleur, sinon retourne BORD.
ECouleur compareCouleur(ECouleur couleur1, ECouleur couleur2)
{
	if(couleur1 == BORD || couleur1 == UNDEFINED)
	{
		if(couleur2==UNDEFINED) return BORD;
		else return couleur2;
	}
	if(couleur2 == BORD || couleur2 == UNDEFINED)
	{
		if(couleur1==UNDEFINED) return BORD;
		else return couleur1;
	}
	if(couleur1==couleur2) return couleur1;
	else return VIDE;
}

ECouleur determineCouleurTerritoire(SPlateau* plateau, STerritoire* territoire, ECouleur couleur)
{
	ECouleur couleur_de_comparaison = couleur;
	SPosition* position_territoire = listCurrent(listEnsembleColore(territoire));
	if(listEmpty(listEnsembleColore(territoire))) return BORD;

	return compareCouleur(couleur_de_comparaison, determineCouleurTerritoire(plateau, listNext(listEnsembleColore(territoire)), couleurVoisin(plateau,position_territoire)));
}

ECouleur couleur_territoire(STerritoire* territoire)
{
	ECouleur res = VIDE;
	if(territoire)
	{
		res = couleurEnsembleColore(territoire);
	}
	return res;
}

