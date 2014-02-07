#ifndef __PION__
#define __PION__

#include "position.h"
#include "couleur.h"
#include "liste.h"

/**
 * @struct SPion
 */
typedef struct
{
	SPosition pos;
	ECouleur couleur;
} SPion;

/**
 * @typedef SList SListPion
 */
typedef SList SListPion;

/**
 * @fn SPion* creerPion(SPosition pos, ECouleur couleur)
 * @brief Alloue un pion dynamiquement
 * @param pos Position du pion
 * @couleur couleur du pion
 * @return pointeur vers le pion
 */
SPion* creerPion(SPosition pos, ECouleur couleur);

/**
 * @fn void detruirePion(SPion* pion)
 * @brief detruit le pion
 * @param pion pion a detruire
 */
void detruirePion(SPion* pion);

/**
 * @fn ECouleur couleurPion(SPion* pion)
 * @brief Renvoi la couleur du pion
 * @param pion Pion concerne
 * @return Couleur du pion
 */
ECouleur couleurPion(SPion* pion);

/**
 * @fn int abscissePion(SPion* pion)
 * @brief renvoi labscisse du pion
 * @param pion concerne
 * @return absicce du pion
 */
int abscissePion(SPion* pion);

/**
 * @fn int ordonneePion(SPion* pion)
 * @brief renvoi l ordonnee du pion
 * @param pion pion concerne
 * @return ordonnee du pion
 */
int ordonneePion(SPion* pion);

/**
 * @fn SPosition positionPion(SPion* pion)
 * @brief Renvoi la position du pion
 * @param pion pion concerne
 * @return Position du pion
 */
SPosition positionPion(SPion* pion);

#endif
