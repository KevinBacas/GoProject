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
	listAdd(listEnsembleColore(territoire),(void*)pos);
	if((positionValide(plateau,pos))==0) return NULL;
	SPosition* posG = positionGauche(pos);
	SPosition* posD = positionDroite(pos);
	SPosition* posB = positionBas(pos);
	SPosition* posH = positionHaut(pos);
	SList* l1 = listConcatUnique(listEnsembleColore(territoire), listEnsembleColore(determineTerritoire(plateau, posG)), positionsEgale);
	SList* l2 = listConcatUnique(l1, listEnsembleColore(determineTerritoire(plateau, posD)), positionsEgale);
	SList* l3 = listConcatUnique(l2, listEnsembleColore(determineTerritoire(plateau, posB)), positionsEgale);
	SList* l4 = listConcatUnique(l4, listEnsembleColore(determineTerritoire(plateau, posH)), positionsEgale);

	detruirePosition(posG);
	detruirePosition(posD);
	detruirePosition(posB);
	detruirePosition(posH);

	return l4;
}

SLibertes* libertesAdjacente(SPlateau* plateau,SPion* pion)
{
	SLibertes* liberte = listInit();
	SPosition pos = positionPion(pion);
	SPosition* posG = positionGauche(&pos);
	SPosition* posD = positionDroite(&pos);
	SPosition* posB = positionBas(&pos);
	SPosition* posH = positionHaut(&pos);

	if(positionValide(plateau, &pos)==0) return NULL;

	if(plateau_get(plateau,posG)==VIDE)
		listAdd(liberte,posG);
	if(plateau_get(plateau,posD)==VIDE)
		listAdd(liberte,posD);
	if(plateau_get(plateau,posH)==VIDE)
		listAdd(liberte,posH);
	if(plateau_get(plateau,posB)==VIDE)
		listAdd(liberte,posB);

	detruirePosition(posG);
	detruirePosition(posD);
	detruirePosition(posB);
	detruirePosition(posH);

	return liberte;
}

SLibertes* determineLiberte(SPlateau* plateau, SChaine* chaine)
{
	if(chaine) return NULL;
	if(listEmpty(listEnsembleColore(chaine))) return NULL;

	SLibertes* res = listInit();
	SPositions* positions = listEnsembleColore(chaine);
	ECouleur couleur = couleurEnsembleColore(chaine);
	listHead(positions);
	do
	{
		SPion* pion = creerPion(*((SPosition*)listCurrent(positions)), couleur);
		listConcatUnique(libertesAdjacente(plateau, pion), res, positionsEgale);
		detruirePion(pion);
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
			if(positionDansChaine(listCurrent(chaines), pos))
			{
				found = 1;
			}
		} while(!found && listNext(chaines));
		res = listCurrent(chaines);
	}
	return res;
}

void plateau_realiser_capture(SPlateau* plateau, SChaines* chaines, SChaine* chaine)
{
	if(!chaine) return;

	SList* list = listEnsembleColore(chaine);

	if(listEmpty(list)) printf("----------- !!!!!!!!!!!!!!!!! -----------\n");

	listHead(list);
	do
	{
		SPosition* pos = listCurrent(list);
		plateau_set(plateau, pos, VIDE);
		free(pos);
	}while(listNext(list));

	while(!listEmpty(list)) free(listRemove(list, 0));
	listRemoveElement(chaines, chaine);
	free(chaine);
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
