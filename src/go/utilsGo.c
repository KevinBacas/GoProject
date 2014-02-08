#include <stdlib.h>
#include <stdio.h>

#include "utilsGo.h"
#include "chaines.h"
#include "utilsGo.h"
#include "territoire.h"
#include "position.h"


STerritoire* determineTerritoire(SPlateau* plateau, SPosition* pos)
{
	STerritoire* territoire = creerEnsembleColore();
	SList* list = listEnsembleColore(territoire);
	listAdd(list,(void*)pos);
	if((positionValide(plateau,pos))==0) return NULL;
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
	printf("determineLiberte chaine : "); printf("%x\n", chaine);
	SPositions* positions = listEnsembleColore(chaine);
	listDisplay(positions);
	if(listEmpty(positions)) return NULL;

	SLibertes* res = listInit();
	listHead(positions);
	do
	{
		SLibertes* libs = libertesAdjacente(plateau, listCurrent(positions));
		printf("determineLiberte (%d,%d): ", abscissePosition(listCurrent(positions)), ordonneePosition(listCurrent(positions)));
		listDisplay(libs);
		listConcatUnique(res, libs, positionsEgale);
	} while(listNext(positions));

	printf("determineLiberte res : ");
	listDisplay(res);

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
			printf("plateau_determiner_chaine : %X | %d\n", res, found);
		}
	}
	return res;
}

void plateau_realiser_capture(SPlateau* plateau, SChaines* chaines, SChaine* chaine)
{
	if(!chaine) return;

	SList* list = listEnsembleColore(chaine);

	listHead(list);
	do
	{
		SPosition* pos = listCurrent(list);
		printf("x : %d, y : %d\n", pos->x, pos->y);
		plateau_set(plateau, pos, VIDE);
	}while(listNext(list));

	while(!listEmpty(list)) ///*free*/(listRemove(list, 0));
	listRemoveElement(chaines, chaine);
	//free(chaine);
}

int plateau_est_identique(SPlateau* plateau, SPlateau* ancienPlateau)
{
	int res = 1;
	int taille = taille_plateau(plateau);
	int i,j;
	SPosition pos;
	for(i = 0 ; i < taille && res ; ++i)
	{
		for(j = 0 ; j < taille && res ; ++j)
		{
			pos.x = i;
			pos.y = j;
			if(plateau_get(plateau, &pos) != plateau_get(ancienPlateau, &pos))
			{
				res = 0;
			}
		}
	}
	return res;
}

void plateau_copie(SPlateau* from, SPlateau* to)
{
	int taille = taille_plateau(from);
	int i,j;
	SPosition pos;
	for(i = 0 ; i < taille ; ++i)
	{
		for(j = 0 ; j < taille ; ++j)
		{
			pos.x = i;
			pos.y = j;
			plateau_set(to, &pos, plateau_get(from, &pos));
		}
	}
}

SChaines* plateau_entoure_un_territoire(STerritoire* leTerritoire, SPlateau* plateau);
