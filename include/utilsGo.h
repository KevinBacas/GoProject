/*
 * utilsGo.h
 *
 *  Created on: Feb 6, 2014
 *      Author: dev
 */

#ifndef UTILSGO_H_
#define UTILSGO_H_

#include "territoire.h"
#include "plateau.h"
#include "libertes.h"
#include "chaine.h"
#include "chaines.h"
#include "positions.h"

/**
 * @biref calcul les libertés pour une position donnee
 */
SLibertes* libertesAdjacente(SPlateau* plateau, SPosition* pos);

/**
 * @brief determine l'ensemble des libertes d'une chaine donnee en fonction de la position des pions sur le plateau
 */
SLibertes* determineLiberte(SPlateau* plateau, SChaine* chaine);

/** @brief retourne un ensemble d'intersections inoccupees voisines de proche en
 * proche delimitees par des pierres de meme couleur en commencant par l'intersection vide a la position pos.
 * Important : Si la case ne fait pas partie d'un territoire de meme couleur,
 * retourne quand meme l'ensemble des intersections voisines mais en specifiant que ce Territoire n'a aucune couleur.
 * Ce cas est exploite par la fonction estUnSeki
 */
STerritoire* determineTerritoire(SPlateau* plateau, SPosition* pos, SPositions* positions);

/**
 * @brief determine si un territoire forme un seki pour les chaines de differentes couleurs concernees.
 * La valeur retournee est de 1 pour vrai et de 0 pour faux
 */
int estUnSeki(STerritoire* leTerritoire, SChaines* lesChaines, SPlateau* plateau);

/**
 * @brief Determine la position des yeux relatifs a une chaine
 * Si la chaine n'a aucun oeil alors la valeur retournee est NULL
 */
SPositions* lesYeuxDeLaChaine(SChaine* chaine, SPlateau* plateau);

/**
 * @brief Produit la chaine a laquelle appartient le pion a la position pos sur le plateau.
 * S'il n'y a pas de pion sur cette case, alors le resultat retournee est NULL */
SChaine* plateau_determiner_chaine(SChaines* chaines, SPosition* pos);

/**
 * @brief Determine la ou les chaines entourant un territoire
 */
SChaines* plateau_entoure_un_territoire(STerritoire* leTerritoire, SPlateau* plateau);

/**
 * @brief en fonction de la position du pion et de sa couleur retourne les chaines
 * capturees. Si aucune chaine n’est capturee par la pose du pion, alors la valeur NULL est retournee.
 * L’entier (reference par) valide est egal a zero si le fait placer le poin en cette position conduit a contruire une chaine sans liberte de la couleur du pion
 * (sauf si ce coup produit la capture d’au moins une chaine adverse).
 * Dans le cas contraire l’entier reference par valide est egale a 1.
*/
SChaines* captureChaines(SPlateau* plateau, SPion* pion, int* valide);

/**
 * @brief Permet de compter les points d'un plateau
 * @param plateau plateau final à calculer
 * @param komi le komi relatif à la partie
 * @return un score relatif (< 0 Noir gagnant, >0 Blanc gagnant, 0 match nul)
 */
float compter_point(SPlateau* plateau,float komi);

#endif // UTILSGO_H_
