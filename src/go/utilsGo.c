#include <stdlib.h>
#include <stdio.h>

#include "utilsGo.h"
#include "chaines.h"
#include "utilsGo.h"
#include "territoire.h"
#include "position.h"
#include "couleur.h"


STerritoire* determineTerritoire(SPlateau* plateau, SPosition* pos, SPositions* positions)
{
	STerritoire* territoire = NULL;
	if( plateau && pos && positions)
	{
		territoire = creerEnsembleColore();
		SList* list = listEnsembleColore(territoire);

		if( positionValide(plateau, pos)==0 || plateau_get(plateau, pos) != VIDE || listSearch(positions, pos, positionsEgale)) return NULL;

		listAdd(list,(void*)pos);
		listAdd(positions, pos);
		SPosition* posG = positionGauche(pos);
		listConcatUnique(list, listEnsembleColore(determineTerritoire(plateau, posG, positions)), positionsEgale);
		//detruirePosition(posG);

		SPosition* posD = positionDroite(pos);
		listConcatUnique(list, listEnsembleColore(determineTerritoire(plateau, posD, positions)), positionsEgale);
		//detruirePosition(posD);

		SPosition* posB = positionBas(pos);
		listConcatUnique(list, listEnsembleColore(determineTerritoire(plateau, posB, positions)), positionsEgale);
		//detruirePosition(posB);

		SPosition* posH = positionHaut(pos);
		listConcatUnique(list, listEnsembleColore(determineTerritoire(plateau, posH, positions)), positionsEgale);
		//detruirePosition(posH);
	}

	return territoire;
}


float compter_point(SPlateau* plateau, float komi)
{
	STerritoire* territoire = creerEnsembleColore();
	int x,y;
	float score = komi;
	int taille = taille_plateau(plateau);

	for(x = 0 ; x < taille ; ++x)
	{
		for(y = 0 ; y < taille ; ++y)
		{
			SPosition* position = creerPosition(x,y);
			ECouleur couleur_position = plateau_get(plateau,position);
			if(couleur_position == NOIR || couleur_position == BLANC)
			{
				score += (float)couleur_position;
			}
			else
			{
				if(listFind(listEnsembleColore(territoire), position)==0)
				{
					SPositions* positions = listInit();
					territoire = determineTerritoire(plateau, position, positions);
					listDelete(positions);
				}
				score += (float)couleur_territoire(territoire);
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
		SPosition* pos_haut = positionHaut(listCurrent(libertes));
		SPosition* pos_bas = positionBas(listCurrent(libertes));
		SPosition* pos_gauche = positionGauche(listCurrent(libertes));
		SPosition* pos_droit = positionDroite(listCurrent(libertes));
		c_haut = plateau_get(plateau, pos_haut);
		c_bas = plateau_get(plateau, pos_bas);
		c_gauche = plateau_get(plateau, pos_gauche);
		c_droite = plateau_get(plateau, pos_droit);
		free(pos_haut);
		free(pos_bas);
		free(pos_gauche);
		free(pos_droit);
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

SChaines* plateau_entoure_un_territoire(STerritoire* leTerritoire, SPlateau* plateau)
{
	SChaines* liste_de_chaines = listInit();
	listHead(listEnsembleColore(leTerritoire));

	SPosition* v_haut = voisinHaut(plateau,listCurrent(listEnsembleColore(leTerritoire)));
	SPosition* v_bas = voisinBas(plateau,listCurrent(listEnsembleColore(leTerritoire)));
	SPosition* v_gauche = voisinGauche(plateau,listCurrent(listEnsembleColore(leTerritoire)));
	SPosition* v_droit = voisinDroit(plateau,listCurrent(listEnsembleColore(leTerritoire)));

	SChaine* chaine_haut = plateau_determiner_chaine(liste_de_chaines,v_haut);
	SChaine* chaine_bas = plateau_determiner_chaine(liste_de_chaines,v_bas);
	SChaine* chaine_gauche = plateau_determiner_chaine(liste_de_chaines,v_gauche);
	SChaine* chaine_droite = plateau_determiner_chaine(liste_de_chaines,v_droit);

	if(v_haut && chaine_haut && listFind(liste_de_chaines,chaine_haut))
	{
		listAdd(liste_de_chaines,chaine_haut);
	}
	if(v_bas && chaine_bas && listFind(liste_de_chaines,chaine_bas))
	{
		listAdd(liste_de_chaines,chaine_bas);
	}
	if(v_gauche && chaine_gauche && listFind(liste_de_chaines,chaine_gauche))
	{
		listAdd(liste_de_chaines,chaine_gauche);
	}
	if(v_droit && chaine_droite && listFind(liste_de_chaines,chaine_droite))
	{
		listAdd(liste_de_chaines,chaine_droite);
	}


	while(listEmpty(listNext(listEnsembleColore(leTerritoire))))
	{
		v_haut = voisinHaut(plateau, listCurrent(listEnsembleColore(leTerritoire)));
		v_bas = voisinBas(plateau, listCurrent(listEnsembleColore(leTerritoire)));
		v_gauche = voisinGauche(plateau, listCurrent(listEnsembleColore(leTerritoire)));
		v_droit = voisinDroit(plateau, listCurrent(listEnsembleColore(leTerritoire)));

		chaine_haut = plateau_determiner_chaine(liste_de_chaines,v_haut);
		chaine_bas = plateau_determiner_chaine(liste_de_chaines,v_bas);
		chaine_gauche = plateau_determiner_chaine(liste_de_chaines,v_gauche);
		chaine_droite = plateau_determiner_chaine(liste_de_chaines,v_droit);

		if(v_haut && chaine_haut && listFind(liste_de_chaines,chaine_haut))
		{
			listAdd(liste_de_chaines,chaine_haut);
		}
		if(v_bas && chaine_bas && listFind(liste_de_chaines,chaine_bas))
		{
			listAdd(liste_de_chaines,chaine_bas);
		}
		if(v_gauche && chaine_gauche && listFind(liste_de_chaines,chaine_gauche))
		{
			listAdd(liste_de_chaines,chaine_gauche);
		}
		if(v_droit && chaine_droite && listFind(liste_de_chaines,chaine_droite))
		{
			listAdd(liste_de_chaines,chaine_droite);
		}
	}
	return liste_de_chaines;
}

int estUnSeki(STerritoire* leTerritoire, SChaines* lesChaines, SPlateau* plateau)
{
	ECouleur couleur_courrant = couleurChaine(listHead(lesChaines));
	SChaines* liste_de_chaines = plateau_entoure_un_territoire(leTerritoire,plateau);
	if(!listFind(liste_de_chaines, listHead(lesChaines)))
	{
		return 0;
	}
	while(listNext(lesChaines))
	{
		if(!listFind(liste_de_chaines, listCurrent(lesChaines)) || couleurChaine(listCurrent(lesChaines)))
		{
			return 0;
		}
		couleur_courrant = couleurChaine(listCurrent(lesChaines));
	}
	return 1;
}
