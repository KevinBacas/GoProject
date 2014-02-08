#include <stdlib.h>
#include <stdio.h>

#include "utilsGo.h"
#include "chaines.h"
#include "utilsGo.h"
#include "territoire.h"
#include "position.h"
#include "couleur.h"


STerritoire* determineTerritoire(SPlateau* plateau, SPosition* pos)
{
	STerritoire* territoire = creerEnsembleColore();
	SList* list = listEnsembleColore(territoire);
	listAdd(list,(void*)pos);
	if((positionValide(plateau,pos))==0 && plateau_get(plateau, pos) != VIDE) return NULL;

	SPosition* posG = positionGauche(pos);
	SPosition* posD = positionDroite(pos);
	SPosition* posB = positionBas(pos);
	SPosition* posH = positionHaut(pos);

	listConcatUnique(list, listEnsembleColore(determineTerritoire(plateau, posG)), positionsEgale);
	listConcatUnique(list, listEnsembleColore(determineTerritoire(plateau, posD)), positionsEgale);
	listConcatUnique(list, listEnsembleColore(determineTerritoire(plateau, posB)), positionsEgale);
	listConcatUnique(list, listEnsembleColore(determineTerritoire(plateau, posH)), positionsEgale);


	detruirePosition(posG);
	detruirePosition(posD);
	detruirePosition(posB);
	detruirePosition(posH);

	return territoire;
}


int compter_point(SPlateau* plateau,float komi)
{
	STerritoire* territoire = creerEnsembleColore();
	int x,y;
	int score = komi;
	for(x=0;x<19;x++)
	{
		for(y=0;y<19;y++)
		{
			SPosition* position = creerPosition(x,y);
			ECouleur couleur_position = plateau_get(plateau,position);
			if(couleur_position == NOIR || couleur_position == BLANC)
			{
				score += (int)couleur_position;
			}
			else
			{
				if(listFind(listEnsembleColore(territoire), position)==0)
				{
					territoire = determineTerritoire(plateau, position);
				}
				score += (int)(couleur_territoire(territoire));
			}
		}
	}
	return score;
}

SLibertes* libertesAdjacente(SPlateau* plateau, SPosition* pos)
{
	if(positionValide(plateau, pos)==0) return NULL;

	SLibertes* liberte = listInit();
	SPosition* posG = positionGauche(pos);
	SPosition* posD = positionDroite(pos);
	SPosition* posB = positionBas(pos);
	SPosition* posH = positionHaut(pos);

	if(plateau_get(plateau,posG)==VIDE)
		listAdd(liberte,posG);
	else
		detruirePosition(posG);

	if(plateau_get(plateau,posD)==VIDE)
		listAdd(liberte,posD);
	else
		detruirePosition(posD);

	if(plateau_get(plateau,posH)==VIDE)
		listAdd(liberte,posH);
	else
		detruirePosition(posH);

	if(plateau_get(plateau,posB)==VIDE)
		listAdd(liberte,posB);
	else
		detruirePosition(posB);

	return liberte;
}

SLibertes* determineLiberte(SPlateau* plateau, SChaine* chaine)
{
	if(!chaine) return NULL;
	SPositions* positions = listEnsembleColore(chaine);
	listDisplay(positions);
	if(listEmpty(positions)) return NULL;

	SLibertes* res = listInit();
	listHead(positions);
	do
	{
		SLibertes* libs = libertesAdjacente(plateau, listCurrent(positions));
		listConcatUnique(res, libs, positionsEgale);
	} while(listNext(positions));

	return res;
}

int estUnSeki(STerritoire* leTerritoire, SChaines* lesChaines, SPlateau* plateau);

SPositions* lesYeuxDeLaChaine(SChaine* chaine, SPlateau* plateau)
{
	SPositions* yeux = listInit();
	SLibertes* libertes = determineLiberte(plateau,chaine);

	listHead(libertes);
	SPosition* pos = listCurrent(libertes);

	ECouleur c_haut = plateau_get(plateau, positionHaut(pos));
	ECouleur c_bas = plateau_get(plateau, positionBas(pos));
	ECouleur c_gauche = plateau_get(plateau, positionGauche(pos));
	ECouleur c_droite = plateau_get(plateau, positionDroite(pos));

	if(c_haut == c_bas && c_bas == c_gauche && c_gauche== c_droite && (c_haut==NOIR || c_haut == BLANC)) listAdd(yeux, listHead(libertes));

	while(listNext(libertes)!=NULL)
	{
		c_haut = plateau_get(plateau, positionHaut(listCurrent(libertes)));
		c_bas = plateau_get(plateau, positionBas(listCurrent(libertes)));
		c_gauche = plateau_get(plateau, positionGauche(listCurrent(libertes)));
		c_droite = plateau_get(plateau, positionDroite(listCurrent(libertes)));
		if(c_haut == c_bas && c_bas == c_gauche && c_gauche== c_droite && (c_haut==NOIR || c_haut == BLANC)) listAdd(yeux,listCurrent(libertes));
	}
	listDelete(libertes);
	return yeux;
}

SChaine* plateau_determiner_chaine(SChaines* chaines, SPosition* pos)
{
	SChaine* res = NULL;
	if(chaines && pos && !listEmpty(chaines))
	{
		listHead(chaines);
		int found = 0;

		do
		{
			found = positionDansChaine(listCurrent(chaines), pos);
		} while(!found && listNext(chaines));

		if(found)
		{
			res = listCurrent(chaines);
		}
	}
	return res;
}

SChaines* plateau_entoure_un_territoire(STerritoire* leTerritoire, SPlateau* plateau);
