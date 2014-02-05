#include <stdio.h>
#include <stdlib.h>
#include "chaine.h"

SChaine* creer_chaine_vide()
{
	SChaine* chaine = malloc(sizeof(SChaine));
	chaine->couleur = VIDE;
	chaine->liste = listInit;
	return chaine;
}

void detruire_chaine(SChaine* chaine)
{
	deleteList(chaine);
}

ECouleur couleur_chaine(SChaine* chaine)
{
	return chaine->couleur;
}

SList* liste_chaine(SChaine* chaine)
{
	return chaine->liste;
}

SChaine* ajouter_chaine(SChaine* chaine, SPion* pion)
{
	listAdd(chaine->liste, (void*)pion);
	return chaine;
}

SChaine* concatener_chaine(SChaine* chaine1, SChaine* chaine2)
{
	chaine1->liste = concatenList(liste_chaine(chaine1), liste_chaine(chaine2));
	detruire_chaine(chaine2);
	return chaine1;
}


