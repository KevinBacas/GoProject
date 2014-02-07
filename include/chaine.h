#ifndef __CHAINE__
#define __CHAINE__

#include "pion.h"
#include "ensembleColore.h"

/**
 * @typedef SEnsembleColore SChaine
 */
typedef SEnsembleColore SChaine;


/**
 * @brief Alloue une chaine dynamiquement et la retourne
 * @return Chaine allouee
 */
SChaine* creerChaine();

/**
 * @brief detruit la chaine passee en parametre
 * @param chaine Chaine a detruire
 */
void detruireChaine(SChaine* chaine);

/**
 * @brief Renvoi la couleur d une chaine
 */
ECouleur couleurChaine(SChaine* chaine);

/**
 * @brief Ajoute un pion a la chaine
 */
SChaine* ajouterPion(SChaine* chaine, SPion* pion);

/**
 * @brief concatene deux chaines et renvoi une seule chaine
 */
SChaine* concatenerChaine(SChaine* chaine1, SChaine* chaine2);

/**
 * @brief Verifie si une position correspond a une des positions de la chaine.
 * @return 1 si vrai sinon 0.
 */
int positionDansChaine(SChaine* chaine, SPosition* pos);

void actualiseChaines(SChaines chaines);

#endif // __CHAINE__
