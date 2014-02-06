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

// TODO : TOUT
/**
 * @brief determine l'ensemble des libertes d'une chaine donnee en fonction de la position des pions sur le plateau
 */
SLibertes determineLiberte(SPlateau plateau,SChaine chaine);

/** @brief retourne un ensemble d'intersections inoccupees voisines de proche en
 * proche delimitees par des pierres de meme couleur en commencant par l'intersection vide a la position pos.
 * Important : Si la case ne fait pas partie d'un territoire de meme couleur,
 * retourne quand meme l'ensemble des intersections voisines mais en specifiant que ce Territoire n'a aucune couleur.
 * Ce cas est exploite par la fonction estUnSeki
 */
// TODO :
STerritoire determineTerritoire(SPlateau plateau, SPosition pos);

/**
 * @brief determine si un territoire forme un seki pour les chaines de differentes couleurs concernees.
 * La valeur retournee est de 1 pour vrai et de 0 pour faux
 */
// TODO :
int estUnSeki(STerritoire leTerritoire, SChaines lesChaines, SPlateau plateau);

/**
 * @brief Determine la position des yeux relatifs a une chaine
 * Si la chaine n'a aucun oeil alors la valeur retournee est NULL
 */
// TODO :
SPositions lesYeuxDeLaChaine(SChaine chaine, SPlateau plateau);

/**
 * @brief Produit la chaine a laquelle appartient le pion a la position pos sur le plateau.
 * S'il n'y a pas de pion sur cette case, alors le resultat retournee est NULL */
// TODO :
SChaine plateau_determiner_chaine(SPlateau plateau,SPosition pos);

/**
 * @brief Realise la capture des pions correspondant a la chaine en les enlevant du plateau.
 */
// TODO :
void plateau_realiser_capture(SPlateau plateau, SChaine chaine);

/**
 * @brief indique si l'organisation du plateau est identique a une precedente organisation de plateau.
 * La valeur retourne est de 1 pour vrai et de 0 pour faux
 */
// TODO :
int plateau_est_identique(SPlateau plateau, SPlateau ancienPlateau);

/**
 * @brief Copie un plateau.
 * Les deux tableaux sont supposes deja alloues
 */
// TODO :
int plateau_copie(SPlateau from, SPlateau to);

/**
 * @brief Determine la ou les chaines entourant un territoire
 */
// TODO :
SChaines plateau_entoure_un_territoire(STerritoire leTerritoire, SPlateau plateau);

#endif /* UTILSGO_H_ */