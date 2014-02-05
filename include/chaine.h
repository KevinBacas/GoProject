#ifndef __CHAINE__
#define __CHAINE__

#include "pion.h"

typedef struct
{
	ECouleur couleur;
	SList* liste;

}SChaine;

SChaine* creer_chaine_vide();

void detruire_chaine(SChaine* chaine);

ECouleur couleur_chaine(SChaine* chaine);

SList* liste_chaine(SChaine* chaine);

SChaine* ajouter_chaine(SChaine* chaine, SPion* pion);

SChaine* concatener_chaine(SChaine* chaine1, SChaine chaine2);


#endif
