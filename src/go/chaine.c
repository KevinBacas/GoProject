#include <stdio.h>
#include <stdlib.h>

#include "chaine.h"

SChaine* creer_chaine()
{
	return listInit();
}

void detruire_chaine(SChaine* chaine)
{
	deleteList(chaine);
}

ECouleur couleur_chaine(SChaine* chaine)
{
	return ((SPion*)listCurrent(chaine))->couleur;
}

SChaine* ajouter_chaine(SChaine* chaine, SPion* pion)
{
	listAdd(chaine, (void*)pion);
	return chaine;
}

SChaine* concatener_chaine(SChaine* chaine1, SChaine* chaine2)
{
	return concatenList(chaine1, chaine2);
}
