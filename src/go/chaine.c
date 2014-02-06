#include <stdio.h>
#include <stdlib.h>

#include "chaine.h"

//on doit faire un ensemble qui contient toutes les chaines, je ne sais pas comment l'initialiser !
SEnsembleChaine* creer_ensembleC_vide()
{
	SEnsembleChaine* ensembleC = malloc(sizeof(SEnsembleChaine*));

	return ensembleC;
}

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
	SPion* pion = ((SPion*)listCurrent(chaine));
	if(pion) return pion->couleur;
	return VIDE;
}

SChaine* ajouter_pion(SChaine* chaine, SPion* pion)
{
	listAdd(chaine, (void*)pion);
	return chaine;
}

SChaine* concatener_chaine(SChaine* chaine1, SChaine* chaine2)
{
	return concatenList(chaine1, chaine2);
}
