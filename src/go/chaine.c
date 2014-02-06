#include <stdio.h>
#include <stdlib.h>

#include "chaine.h"
#include "position.h"

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
	listAdd((SList*)listEnsembleColore(chaine), (void*)pion);
	return chaine;
}

SChaine* concatenerChaine(SChaine* chaine1, SChaine* chaine2)
{
	return (SChaine*)listConcat((void*)chaine1, (void*)chaine2);
}

int positionDansChaine(SChaine* chaine, SPosition* pos)
{
	listHead((SList*)listEnsembleColore(chaine));
	while(listCurrent((SList*)listEnsembleColore(chaine))
			&& positionsEgale(listCurrent((SList*)listEnsembleColore(chaine)), pos)
			)
	{
		listNext((SList*)listEnsembleColore(chaine));
	}
	return positionsEgale(listCurrent((SList*)listEnsembleColore(chaine)), pos);
}
