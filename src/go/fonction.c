#include <stdlib.h>
#include <stdio.h>
#include "fonction.h"

int compter_contact(SPlateau* plateau,SPion* pion, ECouleur couleur)
{
	int contact = 0;

	if(pion->position->x = taille)
	{
		if(pion->position->y = taille)
		{
			if(couleur = plateau->grille[x-1][y]->couleur ) contact+=1;
			if(couleur = plateau->grille[x][y-1]->couleur ) contact+=1;
		}
		else
		{
			if(pion->position->y = 0)
			{
				if(couleur = plateau->grille[x-1][y]->couleur ) contact+=1;
				if(couleur = plateau->grille[x][y+1]->couleur ) contact+=1;
			}
			else
			{
				if(couleur = plateau->grille[x-1][y]->couleur ) contact+=1;
				if(couleur = plateau->grille[x][y+1]->couleur ) contact+=1;
				if(couleur = plateau->grille[x][y-1]->couleur ) contact+=1;
			}
		}
	}
	else
		{
			if(position->x = 0)
			{
				if(position->y = taille)
				{
					if(couleur = plateau->grille[x+1][y]->couleur ) contact+=1;
					if(couleur = plateau->grille[x][y-1]->couleur ) contact+=1;
				}
				else
				{
					if(pion->position->y = 0)
					{
						if(couleur = plateau->grille[x+1][y]->couleur ) contact+=1;
						if(couleur = plateau->grille[x][y+1]->couleur ) contact+=1;
					}
					else
					{
						if(couleur = plateau->grille[x+1][y]->couleur ) contact+=1;
						if(couleur = plateau->grille[x][y+1]->couleur ) contact+=1;
						if(couleur = plateau->grille[x][y-1]->couleur ) contact+=1;
					}
				}
			}
			else
			{
				if(couleur = plateau->grille[x+1][y]->couleur ) contact+=1;
				if(couleur = plateau->grille[x][y+1]->couleur ) contact+=1;
				if(couleur = plateau->grille[x-1][y]->couleur ) contact+=1;
				if(couleur = plateau->grille[x-1][y-1]->couleur ) contact+=1;
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


