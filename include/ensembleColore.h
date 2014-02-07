#ifndef __ENSEMBLE_COLORE_H__
#define __ENSEMBLE_COLORE_H__

#include "ensemblePosition.h"
#include "couleur.h"

/**
 * @struct SEnsembleColore
 */
typedef struct ensembleColore SEnsembleColore;

/**
 * @fn SEnsembleColore* creerEnsembleColore()
 * @brief Alloue un ensemble colore dynamiquement et renvoi son pointeur
 * @return Pointeur sur l'ensemble colore
 */
SEnsembleColore* creerEnsembleColore();

/**
 * @fn void detruireEnsembleColore(SEnsembleColore* e_colore)
 * @brief detruit l'ensembleColore passe en paramtre
 * @param e_colore Ensemble colore a detruire
 */
void detruireEnsembleColore(SEnsembleColore* e_colore);

/**
 * @fn void setCouleurEnsembleColore(SEnsembleColore* e_colore, ECouleur couleur)
 * @brief change la couleur l'EnsembleColore
 * @param e_colore Ensemble alloue qui contient la couleur
 * @param couleur Couleur voulu
 * @return Couleur de l'ensemble
 */
void setCouleurEnsembleColore(SEnsembleColore* e_colore, ECouleur couleur);

/**
 * @fn ECouleur couleurEnsembleColore(SEnsembleColore* e_colore)
 * @brief renvoi la couleur de l'EnsembleColore
 * @param e_colore Ensemble alloue qui contient la couleur
 * @return Couleur de l'ensemble
 */
ECouleur couleurEnsembleColore(SEnsembleColore* e_colore);

/**
 * @fn SEnsemblePosition* listEnsembleColore(SEnsembleColore* e_colore)
 * @brief renvoi la liste de position de l'ensemble
 * @param e_colore Ensemble qui contient la liste
 * @return Pointeur vers la liste
 */
SEnsemblePosition* listEnsembleColore(SEnsembleColore* e_colore);

#endif // __ENSEMBLE_COLORE_H__
