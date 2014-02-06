#include <stdlib.h>
#include <stdio.h>

#include "fonction.h"
#include "liste.h"
#include "couleur.h"
#include "pion.h"
#include "plateau.h"

typedef SList listePion;

int compter_contact(SPlateau* plateau, SPion* pion, ECouleur couleur)
{
	int contact = 0;
	int x = abscisse_pion(pion);
	int y = ordonnee_pion(pion);
	int taille = taille_plateau(plateau);

	if(x==taille)
	{
		if(y==taille)
		{
			if(couleur == couleur_position(plateau, x-1, y)) contact+=1;
			if(couleur == couleur_position(plateau, x, y-1)) contact+=1;
		}
		else
		{
			if(x==0)
			{
				if(couleur == couleur_position(plateau, x-1, y)) contact+=1;
				if(couleur == couleur_position(plateau, x, y+1)) contact+=1;
			}
			else
			{
				if(couleur == couleur_position(plateau, x-1, y)) contact+=1;
				if(couleur == couleur_position(plateau, x, y+1)) contact+=1;
				if(couleur == couleur_position(plateau, x, y-1)) contact+=1;
			}
		}
	}
	else
		{
			if(x==0)
			{
				if(y==taille)
				{
					if(couleur == couleur_position(plateau, x+1, y)) contact+=1;
					if(couleur == couleur_position(plateau, x, y-1)) contact+=1;
				}
				else
				{
					if(y==0)
					{
						if(couleur == couleur_position(plateau, x+1, y)) contact+=1;
						if(couleur == couleur_position(plateau, x, y+1)) contact+=1;
					}
					else
					{
						if(couleur == couleur_position(plateau, x+1, y)) contact+=1;
						if(couleur == couleur_position(plateau, x, y+1)) contact+=1;
						if(couleur == couleur_position(plateau, x, y-1)) contact+=1;
					}
				}
			}
			else
			{
				if(couleur == couleur_position(plateau, x+1, y)) contact+=1;
				if(couleur == couleur_position(plateau, x, y+1)) contact+=1;
				if(couleur == couleur_position(plateau, x-1, y)) contact+=1;
				if(couleur == couleur_position(plateau, x, y-1)) contact+=1;
			}
		}
	return contact;

}

int compter_liberte(SPlateau* plateau, listePion* chaine)
{
	//TODO : pas compris.
	//compter_liberte(plateau,NULL)=0;
	//TODO : chaine->queue !
	//return compter_contact(plateau, listHead(chaine), VIDE)-1 + compter_liberte( plateau, chaine->queue);
	return 0;
}

void capture_chaine(SPlateau* plateau, listePion* chaine)
{
	if(!(compter_liberte(plateau, chaine)))
	{
		detruire_chaine(chaine);
		//changer la couleur des pions du plateau dans la grille
	}

}


