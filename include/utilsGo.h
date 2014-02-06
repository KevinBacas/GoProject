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

/**
 * @brief determine l’ensemble des libertés d’une chaine donnée en fonction de la position des pions sur le plateau
 */
SLibertes determineLiberte(SPlateau plateau,SChaine chaine);

/** @brief retourne un ensemble d’intersections inoccup ́es voisines de proche en
 * proche d ́limit ́es par des pierres de mˆme couleur en commen ̧ant par l’intersection vide a la position pos.
 * Important : Si la case ne fait pas partie d’un territoire de mˆme couleur,
 * retourne quand mˆme l’ensemble des intersections voisines mais en sp ́cifiant que ce ”Territoire” n’a aucune couleur.
 * Ce cas est exploit ́ par la fonction estUnSeki
 */
STerritoire determineTerritoire(SPlateau plateau, SPosition pos);

/**
 * @brief determine si un territoire forme un seki pour les chaines de différentes couleurs concern ́es.
 * La valeur retournée est de 1 pour vrai et de 0 pour faux
 */
int estUnSeki(STerritoire leTerritoire, SChaines lesChaines, SPlateau plateau);

/**
 * @brief Determine la position des yeux relatifs a une chaine
 * Si la chaine n’a aucun oeil alors la valeur retournée est NULL
 */
SPositions lesYeuxDeLaChaine(SChaine chaine, SPlateau plateau);

/**
 * @brief Produit la chaine a laquelle appartient le pion a la position pos sur le plateau.
 * S’il n’y a pas de pion sur cette case, alors le résultat retournée est NULL */
SChaine plateau_determiner_chaine(SPlateau plateau,SPosition pos);

/**
 * @brief Réalise la capture des pions correspondant a la chaine en les enlevant du plateau.
 */
void plateau_realiser_capture(SPlateau plateau, SChaine chaine);

/**
 * @brief indique si l’organisation du plateau est identique a une pr ́c ́dente organisation de plateau.
 * La valeur retourn ́e est de 1 pour vrai et de 0 pour faux
 */
int plateau_est_identique(SPlateau plateau, SPlateau ancienPlateau);

/**
 * @brief Copie un plateau.
 * Les deux tableaux sont supposés deja alloues
 */
int plateau_copie(SPlateau from, SPlateau to);

/**
 * @brief D ́termine la ou les chaines entourant un territoire
 */
SChaines plateau_entoure_un_territoire(STerritoire leTerritoire, SPlateau plateau);

#endif /* UTILSGO_H_ */
