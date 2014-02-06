#ifndef __CHAINE__
#define __CHAINE__

#include "pion.h"
#include "ensembleColore.h"

typedef SEnsembleColore SChaine;

SChaine* creerChaine();

void detruireChaine(SChaine* chaine);

ECouleur couleurChaine(SChaine* chaine);

SChaine* ajouterPion(SChaine* chaine, SPion* pion);

SChaine* concatenerChaine(SChaine* chaine1, SChaine* chaine2);

/**
 * @brief Verifie si une position correspond a une des positions de la chaine.
 * @return 1 si vrai sinon 0.
 */
int positionDansChaine(SChaine* chaine, SPosition* pos);

#endif // __CHAINE__
