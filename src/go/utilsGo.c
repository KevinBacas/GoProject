#include <stdlib.h>
#include <stdio.h>
#include "utilsGo.h"
#include "chaines.h"


SLibertes* libertesAdjacente(SPlateau* plateau,SPion* pion)
{
	SLibertes* liberte = listInit();
	int x = abscissePion(pion);
	int y = ordonneePion(pion);
	int taille = taille_plateau(plateau) - 1; //pour comptabilité avec le tableau 2 dimension

	if(x>taille || x < 0 || y > taille || y < 0) return NULL;

	if(x == taille)
	{
		if(y == taille) //le pion est dans le coin en haut a droite
		{
			listAdd(liberte, (void*)creerPosition(x,y-1));
			listAdd(liberte, (void*)creerPosition(x-1,y));
		}
		else
		{
			if(y==0)// coin inférieur droit
			{
				listAdd(liberte, (void*)creerPosition(x,y+1));
				listAdd(liberte, (void*)creerPosition(x-1,y));
			}
			else //pion sur le bord droit
			{
				listAdd(liberte, (void*)creerPosition(x,y-1));
				listAdd(liberte, (void*)creerPosition(x,y+1));
				listAdd(liberte, (void*)creerPosition(x-1,y));
			}
		}
	}
	else
	{
		if(x==0)
		{
			if(y == taille) //le pion est dans le coin en haut a gauche
			{
				listAdd(liberte, (void*)creerPosition(x,y-1));
				listAdd(liberte, (void*)creerPosition(x+1,y));
			}
			else
			{
				if(y==0)// coin inférieur gauche
				{
					listAdd(liberte, (void*)creerPosition(x,y+1));
					listAdd(liberte, (void*)creerPosition(x+1,y));
				}
				else //pion sur le bord gauche
				{
					listAdd(liberte, (void*)creerPosition(x,y-1));
					listAdd(liberte, (void*)creerPosition(x,y+1));
					listAdd(liberte, (void*)creerPosition(x+1,y));
				}
			}
		}
		else // tout est au milieu
		{
			listAdd(liberte, (void*)creerPosition(x,y-1));
			listAdd(liberte, (void*)creerPosition(x,y+1));
			listAdd(liberte, (void*)creerPosition(x+1,y));
			listAdd(liberte, (void*)creerPosition(x-1,y));
		}
	}
	return liberte;
}

SLibertes* determineLiberte(SPlateau* plateau,SChaine* chaine)
{
	if(listEnsembleColore(chaine)==NULL) return NULL;

	SLibertes* liberte=listConcatUnique(libertesAdjacente(plateau,listCurrent(listEnsembleColore(chaine)), determineLiberte(plateau,listNext(listEnsembleColore(chaine))) ));

	return liberte;
}

STerritoire determineTerritoire(SPlateau plateau, SPosition pos)

int estUnSeki(STerritoire leTerritoire, SChaines lesChaines, SPlateau plateau)

SPositions lesYeuxDeLaChaine(SChaine chaine, SPlateau plateau)

SChaine plateau_determiner_chaine(SPlateau plateau,SPosition pos)

void plateau_realiser_capture(SPlateau plateau, SChaine chaine)

int plateau_est_identique(SPlateau plateau, SPlateau ancienPlateau)

int plateau_copie(SPlateau from, SPlateau to)

SChaines plateau_entoure_un_territoire(STerritoire leTerritoire, SPlateau plateau)
