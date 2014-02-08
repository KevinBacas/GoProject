/*
 * territoire.h
 *
 *  Created on: Feb 6, 2014
 *      Author: dev
 */

#ifndef TERRITOIRE_H_
#define TERRITOIRE_H_

#include "ensembleColore.h"
#include "plateau.h"

/**
 * @typedef SEnsembleColore STerritoire
 */
typedef SEnsembleColore STerritoire;

ECouleur couleurVoisin(SPlateau* plateau, SPosition* position);

ECouleur compareCouleur(ECouleur couleur1, ECouleur couleur2);

ECouleur determineCouleurTerritoire(SPlateau* plateau, STerritoire* territoire, ECouleur couleur);

ECouleur couleur_territoire(STerritoire* territoire);

#endif /* TERRITOIRE_H_ */
