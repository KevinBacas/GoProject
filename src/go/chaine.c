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

		found = positionsEgale(listCurrent(list), pos);
	} while(!found && listNext(list));

	printf("positionDansChaine (%d,%d) : %x %d\n", abscissePosition(pos), ordonneePosition(pos), chaine, found);

	return found;
}

void actualiseChaines(SChaines* chaines, SList* n_chaine)
{
	if(!listEmpty(chaines))
	{
		SList* tail = n_chaine;

		listHead(chaines);
		do
		{
			SChaine* c = listCurrent(chaines);
			SPositions* poss = listEnsembleColore(c);
			SPosition* pos = listHead(poss);

			int i = listFind(tail, pos);

			if(i==1)
			{
				printf("destruction chaine : "); displayChaine(c);
				listRemoveElement(chaines, c);
			}
		} while(listNext(chaines));
	}
}

void displayChaine(SChaine* chaine)
{
	printf("Chaine %x %c : ", chaine, couleur_to_char(couleurEnsembleColore(chaine)));
	SList* list = listEnsembleColore(chaine);

	if(!listEmpty(list))
	{
		listHead(list);
		do
		{
			printf("(%d,%d) / ", abscissePosition(listCurrent(list)), ordonneePosition(listCurrent(list)));
		}while(listNext(list));
	}
	printf("\n");
}
