#include <stdio.h>
#include <stdlib.h>

#include "chaine.h"
#include "position.h"
#include "liste.h"
#include "positions.h"

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
	SList* list = (SList*)listEnsembleColore(chaine);

	listHead(list);
	int found = 0;

	do
	{
		if(positionsEgale(listCurrent(list), pos))
		{
			found = 1;
		}
	} while(!found && listNext(list));

	return positionsEgale(listCurrent(list), pos);
}

void actualiseChaines(SChaines* chaines, SList* n_chaine)
{
	printf("actualiseChaines\n");
	if(!listEmpty(chaines))
	{
		SList* tail = n_chaine;

		listHead(chaines);
		do
		{
			printf("1\n");
			SChaine* c = listCurrent(chaines);
				printf("1.1\n");
			SPositions* poss = listEnsembleColore(c);
			listDisplay(poss);
				printf("1.2\n");
			SPosition* pos = listHead(poss);
				printf("1.3\n");
			int i = listFind(tail, pos);
			printf("2\n");
			if(i==1) listRemoveElement(chaines, c);
		} while(listNext(chaines));
		printf("3\n");
	}
}
