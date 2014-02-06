#include <stdlib.h>
#include <stdio.h>

#include "utilsGo.h"

SLibertes* determineLiberte(SPlateau* plateau,SChaine* chaine);

STerritoire* determineTerritoire(SPlateau* plateau, SPosition* pos);

int estUnSeki(STerritoire* leTerritoire, SChaines* lesChaines, SPlateau* plateau);

SPositions* lesYeuxDeLaChaine(SChaine* chaine, SPlateau* plateau);

SChaine* positionDansChaines(SChaines* chaines, SPosition* pos)
{
	listHead(chaines);
	while(listCurrent(chaines) && positionDansChaine(listCurrent(chaines), pos)) listNext(chaines);
	return (positionDansChaine(listCurrent(chaines), pos)) ? listCurrent(chaines) : NULL;
}

SChaine* plateau_determiner_chaine(SPlateau* plateau,SChaines* chaines, SPosition* pos)
{
	SChaine* res = NULL;
	ECouleur couleur_chaine = plateau_get(plateau, abscissePosition(pos), ordonneePosition(pos));
	if(couleur_chaine != VIDE && couleur_chaine != KO)
	{
		SPosition* pos = creerPosition(abscissePosition(pos)+1, ordonneePosition(pos));
		SChaine* chaine = positionDansChaines(chaines, pos);
		//if()
		//TODO : Regarder N/S/E/W et concat si il y a une chaine
	}
}

void plateau_realiser_capture(SPlateau* plateau, SChaine* chaine);

int plateau_est_identique(SPlateau* plateau, SPlateau* ancienPlateau)
{
	int res = 1;
	int taille = taille_plateau(plateau);
	int i,j;
	for(i = 0 ; i < taille && res ; ++i)
	{
		for(j = 0 ; j < taille && res ; ++j)
		{
			if(plateau_get(plateau, i, j) != plateau_get(ancienPlateau, i, j))
			{
				res = 0;
			}
		}
	}
	return res;
}

int plateau_copie(SPlateau* from, SPlateau* to)
{
	int taille = taille_plateau(from);
	int i,j;
	for(i = 0 ; i < taille ; ++i)
	{
		for(j = 0 ; j < taille ; ++j)
		{
			plateau_set(to, i, j, plateau_get(from, i, j));
		}
	}
}

SChaines* plateau_entoure_un_territoire(STerritoire* leTerritoire, SPlateau* plateau);
