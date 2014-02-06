#include <stdio.h>
#include <stdlib.h>

#include "chaine.h"

SChaine* creerChaine()
{
	return creerEnsembleColore();
}

void detruireChaine(SChaine* chaine)
{
	detruireEnsembleColore(chaine);
}

ECouleur couleurChaine(SChaine* chaine)
{
	return couleurEnsembleColore(chaine);
}

SChaine* ajouterPion(SChaine* chaine, SPion* pion)
{
	listAdd(chaine, (void*)pion);
	return chaine;
}

SChaine* concatenerChaine(SChaine* chaine1, SChaine* chaine2)
{
	return concatenList(chaine1, chaine2);
}
