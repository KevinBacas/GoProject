#include <stdlib.h>
#include <stdio.h>
#include "utilsGo.h"
#include "chaines.h"
#include "utilsGo.h"
#include "territoire.h"


STerritoire* determineTerritoire(SPlateau* plateau, SPosition* pos)
{
	STerritoire* territoire = creerEnsembleColore();
	listAdd(territoire,(void*)pos);
	if((positionValide(plateau,pos))==0) return NULL;
	SPosition* posG = positionGauche(pos);
	SPosition* posD = positionDroite(pos);
	SPosition* posB = positionBas(pos);
	SPosition* posH = positionHaut(pos);
	SList* l1=listConcatUnique(listEnsembleColore(territoire),determineTerritoire(plateau, posG));
	SList* l2=listConcatUnique(l1, determineTerritoire(plateau,posD));
	SList* l3=listConcatUnique(l2, determineTerritoire(plateau, posB));
	SList* l4=listConcatUnique(l4, determineTerritoire(plateau, posH));

	detruirePosition(posG);
	detruirePosition(posD);
	detruirePosition(posB);
	detruirePosition(posH);

	return l4;
}

SLibertes* libertesAdjacente(SPlateau* plateau,SPion* pion)
{
	SLibertes* liberte = listInit();
	SPosition* pos = positionPion(pion);
	SPosition* posG = positionGauche(pos);
	SPosition* posD = positionDroite(pos);
	SPosition* posB = positionBas(pos);
	SPosition* posH = positionHaut(pos);
	int taille = taille_plateau(plateau) - 1; //pour comptabilite avec le tableau 2 dimension



	if(x>taille || x < 0 || y > taille || y < 0) return NULL;

	if(x == taille)
	{
		if(y == taille) //le pion est dans le coin en haut a droite
		{
			if(plateau_get(x,y-1)==VIDE)
				listAdd(liberte, (void*)posB);
			if(plateau_get(x-1,y)==VIDE)
				listAdd(liberte, (void*)posG);
		}
		else
		{
			if(y==0)// coin inf�rieur droit
			{
				if(plateau_get(x,y+1)==VIDE)
					listAdd(liberte, (void*)posH);
				if(plateau_get(x-1,y)==VIDE)
					listAdd(liberte, (void*)posG);
			}
			else //pion sur le bord droit
			{
				if(plateau_get(x,y-1)==VIDE)
					listAdd(liberte, (void*)posB);
				if(plateau_get(x,y+1)==VIDE)
					listAdd(liberte, (void*)posH);
				if(plateau_get(x-1,y)==VIDE)
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
				if(plateau_get(x,y-1)==VIDE)
					listAdd(liberte, (void*)posB);
				if(plateau_get(x+1,y)==VIDE)
					listAdd(liberte, (void*)posD);
			}
			else
			{
				if(y==0)// coin inf�rieur gauche
				{
					if(plateau_get(x,y+1)==VIDE)
						listAdd(liberte, (void*)posH);
					if(plateau_get(x+1,y)==VIDE)
						listAdd(liberte, (void*)posD);
				}
				else //pion sur le bord gauche
				{
					if(plateau_get(x,y-1)==VIDE)
						listAdd(liberte, (void*)posB);
					if(plateau_get(x,y+1)==VIDE)
						listAdd(liberte, (void*)posH);
					if(plateau_get(x+1,y)==VIDE)
						listAdd(liberte, (void*)posD);
				}
			}
		}
		else // tout est au milieu
		{
			if(plateau_get(x,y-1)==VIDE)
				listAdd(liberte, (void*)posB);
			if(plateau_get(x,y+1)==VIDE)
				listAdd(liberte, (void*)posH);
			if(plateau_get(x+1,y)==VIDE)
				listAdd(liberte, (void*)posD);
			if(plateau_get(x-1,y)==VIDE)
				listAdd(liberte, (void*)posG);
		}
	}
	detruirePosition(posG);
	detruirePosition(posD);
	detruirePosition(posB);
	detruirePosition(posH);
	detruirePosition(pos);
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

SChaine* positionDansChaines(SChaines* chaines, SPosition* pos)
{
	listHead(chaines);
	while(listCurrent(chaines) && positionDansChaine(listCurrent(chaines), pos))
	{
		if(!listNext(chaines))
		{
			return NULL;
		}
	}
	return listCurrent(chaines);
}

SChaine* plateau_determiner_chaine(SPlateau* plateau, SChaines* chaines, SPosition* pos)
{
	SChaine* res = NULL;
	listAdd(listEnsembleColore(res), pos);
	ECouleur couleur_chaine = plateau_get(plateau, abscissePosition(pos), ordonneePosition(pos));
	if(couleur_chaine != VIDE && couleur_chaine != KO)
	{
		//Position N
		SPosition* pos = NULL;
		SChaine* chaine = NULL;
		pos = creerPosition(abscissePosition(pos), ordonneePosition(pos)+1);
		chaine = positionDansChaines(chaines, pos);
		if(chaine)
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
}

void plateau_realiser_capture(SPlateau* plateau, SChaines* chaines, SChaine* chaine)
{

}

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
