#include <stdlib.h>
#include <stdio.h>
#include "fonction.h"

int compter_contact(SPlateau* plateau,SPion* pion, ECouleur couleur)
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
	compter_liberte(plateau,NULL)=0;
	return compter_contact(plateau,chaine->tete, VIDE)-1 + compter_liberte( plateau, chaine->queue);
}

void capture_chaine(SPlateau* plateau, listePion* chaine)
{
	if(!(compter_liberte(plateau, chaine)))
	{
		detruire_chaine(chaine);
		//changer la couleur des pions du plateau dans la grille
	}

}


