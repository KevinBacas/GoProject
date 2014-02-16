/**
 * @file territoire.h
 * @author : Kevin BACAS & Louis DELBOSC
 */

#ifndef TERRITOIRE_H_
#define TERRITOIRE_H_

#include "ensembleColore.h"
#include "plateau.h"

/**
 * @typedef SEnsembleColore STerritoire
 */
typedef SEnsembleColore STerritoire;

/**
 * @brief retourne la couleur du voisins
 * @param plateau
 * @param position
 * @return couleur des voisins
 */
ECouleur couleurVoisin(SPlateau* plateau, SPosition* position);

/**
 * @brief compare des couleurs entre elles
 */
ECouleur compareCouleur(ECouleur couleur1, ECouleur couleur2);

/**
 * @brief determine la couleur d'un territoire
 */
ECouleur determineCouleurTerritoire(SPlateau* plateau, STerritoire* territoire, ECouleur couleur);

/**
 * @brief renvoi la couleur d'un territoire
 */
ECouleur couleur_territoire(STerritoire* territoire);

#endif /* TERRITOIRE_H_ */
