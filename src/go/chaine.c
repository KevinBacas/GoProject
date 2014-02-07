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

void actualiseChaines(SChaines chaines)
{
	SList* tail = ListInit();
	while(!listNext(chaines));
	tail = getListNodeData(listCurrent(chaines));
	int i = listFind(tail,getListNodeData(listHead(getListNodeData(listHead(chaines)))));
	if(i==1) listRemoveElement(chaines,listHead(chaines));
	while(!listNext(listNext(chaines)))
	{
		i = listFind(tail,getListNodeData(listCurrent(getListNodeData(listCurrent(chaines)))));
		if(i==1) listRemoveElement(chaines,listCurrent(chaines));
	}
	free(tail);
}
