#include <stdlib.h>
#include <stdio.h>
#include "utilsGo.h"
#include "chaines.h"
#include "utilsGo.h"
#include "territoire.h"


STerritoire* determineTerritoire(SPlateau* plateau, SPosition* pos)
{
	if(plateau_get(plateau,pos)!=VIDE) return NULL;

	STerritoire* territoire = creerEnsembleColore();
	listAdd(listEnsembleColore(territoire),(void*)pos);
	SPosition* posG = positionGauche(pos);
	SPosition* posD = positionDroite(pos);
	SPosition* posB = positionBas(pos);
	SPosition* posH = positionHaut(pos);
	SList* l1=listConcatUnique(listEnsembleColore(territoire), listEnsembleColore(determineTerritoire(plateau, posG)));
	SList* l2=listConcatUnique(l1, listEnsembleColore(determineTerritoire(plateau, posD)));
	SList* l3=listConcatUnique(l2, listEnsembleColore(determineTerritoire(plateau, posB)));
	SList* l4=listConcatUnique(l4, listEnsembleColore(determineTerritoire(plateau, posH)));

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
	int taille = taille_plateau(plateau) - 1; //pour comptabilite avec le tableau 2 dimension

	int x = abscissePion(pion);
	int y = ordonneePion(pion);



	if(positionValide(plateau, &pos)==0) return NULL;

	if(x == taille)
	{
		if(y == taille) //le pion est dans le coin en haut a droite
		{
			if(plateau_get(plateau,posB)==VIDE)
				listAdd(liberte, (void*)posB);
			if(plateau_get(plateau,posG)==VIDE)
				listAdd(liberte, (void*)posG);
		}
		else
		{
			if(y==0)// coin inf�rieur droit
			{
				if(plateau_get(plateau,posH)==VIDE)
					listAdd(liberte, (void*)posH);
				if(plateau_get(plateau,posG)==VIDE)
					listAdd(liberte, (void*)posG);
			}
			else //pion sur le bord droit
			{
				if(plateau_get(plateau,posB)==VIDE)
					listAdd(liberte, (void*)posB);
				if(plateau_get(plateau,posH)==VIDE)
					listAdd(liberte, (void*)posH);
				if(plateau_get(plateau,posG)==VIDE)
					listAdd(liberte, (void*)posG);
			}
		}
	}
	else
	{
		if(x==0)
		{
			if(y == taille) //le pion est dans le coin en haut a gauche
			{
				if(plateau_get(plateau,posB)==VIDE)
					listAdd(liberte, (void*)posB);
				if(plateau_get(plateau,posD)==VIDE)
					listAdd(liberte, (void*)posD);
			}
			else
			{
				if(y==0)// coin inf�rieur gauche
				{
					if(plateau_get(plateau,posH)==VIDE)
						listAdd(liberte, (void*)posH);
					if(plateau_get(plateau,posD)==VIDE)
						listAdd(liberte, (void*)posD);
				}
				else //pion sur le bord gauche
				{
					if(plateau_get(plateau,posB)==VIDE)
						listAdd(liberte, (void*)posB);
					if(plateau_get(plateau,posH)==VIDE)
						listAdd(liberte, (void*)posH);
					if(plateau_get(plateau,posD)==VIDE)
						listAdd(liberte, (void*)posD);
				}
			}
		}
		else // tout est au milieu
		{
			if(plateau_get(plateau,posB)==VIDE)
				listAdd(liberte, (void*)posB);
			if(plateau_get(plateau,posH)==VIDE)
				listAdd(liberte, (void*)posH);
			if(plateau_get(plateau,posD)==VIDE)
				listAdd(liberte, (void*)posD);
			if(plateau_get(plateau,posG)==VIDE)
				listAdd(liberte, (void*)posG);
		}
	}
	detruirePosition(posG);
	detruirePosition(posD);
	detruirePosition(posB);
	detruirePosition(posH);

	return liberte;
}

SLibertes* determineLiberte(SPlateau* plateau, SChaine* chaine)
{
	if(listEnsembleColore(chaine)==NULL) return NULL;

	SPion* pion_curr = listCurrent(listEnsembleColore(chaine));
	listNext(listEnsembleColore(chaine));

	SLibertes* liberte = listConcatUnique(libertesAdjacente(plateau, pion_curr), determineLiberte(plateau, chaine));

	return liberte;
}

int estUnSeki(STerritoire* leTerritoire, SChaines* lesChaines, SPlateau* plateau);

SPositions* lesYeuxDeLaChaine(SChaine* chaine, SPlateau* plateau);

SChaine* plateau_determiner_chaine(SChaines* chaines, SPosition* pos)
{
	listHead(chaines);
	while(listCurrent(chaines) && !positionDansChaine(listCurrent(chaines), pos))
	{
		if(!listNext(chaines))
		{
			return NULL;
		}
	}
	return listCurrent(chaines);
}
/*
SChaine* res = creerEnsembleColore();
listAdd(listEnsembleColore(res), pos);
ECouleur couleur_chaine = plateau_get(plateau, pos);
if(couleur_chaine != VIDE && couleur_chaine != KO)
{
	//Position N
	SPosition* pos = NULL;
	SChaine* chaine = NULL;


	pos = creerPosition(abscissePosition(pos), ordonneePosition(pos)+1);
	chaine = positionDansChaines(chaines, pos);
	if(chaine && )
	{
		concatenerChaine(res, chaine);
		listRemoveElement(chaines, chaine);
	}
	free(pos);

	//Position S
	pos = creerPosition(abscissePosition(pos), ordonneePosition(pos)-1);
	chaine = positionDansChaines(chaines, pos);
	if(chaine)
	{
		concatenerChaine(res, chaine);
		listRemoveElement(chaines, chaine);
	}
	free(pos);

	//Position W
	pos = creerPosition(abscissePosition(pos)-1, ordonneePosition(pos));
	chaine = positionDansChaines(chaines, pos);
	if(chaine)
	{
		concatenerChaine(res, chaine);
		listRemoveElement(chaines, chaine);
	}
	free(pos);

	//Position E
	pos = creerPosition(abscissePosition(pos)+1, ordonneePosition(pos));
	chaine = positionDansChaines(chaines, pos);
	if(chaine)
	{
		concatenerChaine(res, chaine);
		listRemoveElement(chaines, chaine);
	}
	free(pos);
}
return res;
*/

void plateau_realiser_capture(SPlateau* plateau, SChaines* chaines, SChaine* chaine)
{
	listRemoveElement(chaines, chaine);
	listHead(listEnsembleColore(chaine));
	do
	{
		SPosition* pos = listCurrent(listEnsembleColore(chaine));
		plateau_set(plateau, pos, VIDE);
		free(pos);
	}while(listNext(chaine));
	while(!listEmpty(listEnsembleColore(chaine))) free(listRemove(listEnsembleColore(chaine), 0));
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
