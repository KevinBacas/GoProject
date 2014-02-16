/*
 * partie.h
 *
 *  Created on: Feb 6, 2014
 *      Author: dev
 */

#ifndef PARTIE_H_
#define PARTIE_H_

#include <stdio.h>
#include "position.h"
#include "couleur.h"

/**
 * @struct partie
 */
typedef struct partie SPartie;

/**
 * @typedef void(*FonctionQuestions)(int numeroQuestion, SPartie* partie)
 */
typedef void(*FonctionQuestions)(int numeroQuestion, SPartie* partie);

/**
 * @brief fonction de question pour la version terminal.
 */
void questionsTerminal(int i, SPartie* partie);

/**
 * @brief Initialise la partie en fonction des reponses aux differentes questions :
 * natures des joueurs, taille du plateau parmi 9x9, 13x13 et 19x19, Komi.
 * Pour rendre cette partie independante du mode texte ou mode SDL,
 * une fonction specifique permettra de prendre en compte ces deux mode.
 * La declaration de cette fonctiontant la suivante : typedef void (*FonctionQuestions)(int numeroQuestion, Partie* partie) ;
*/
SPartie* initialisationPartie(FonctionQuestions fonctionQuestions);

/**
 * @brief detruit une partie en la desallouant
 */
void detruirePartie(SPartie* partie);

/**
 * @brief Charge une partie precedement sauvegarde Si le chargement n'est pas possible, retourne un Pointeur NULL
 */
SPartie* partie_charge(FILE* fichier);

/**
 * @brief Sauvegarde la partie dans sa position actuelle
 * Si la sauvegarde se passe sans probleme la fonction retourne 1, sinon 0
 * */
void partie_sauvegarde(SPartie* partie, FILE* fichier);

/**
 * @brief permet de jouer un coup
 * @param partie
 * @param couleur couleur du joueur
 * @param position Position du coup
 */
void jouer_coup(SPartie* partie, ECouleur couleur, SPosition* position);

/**
 * @brief verifie si un coup est valide
 * @param partie
 * @param position position du coup
 * @return 1 si oui sinon 0
 */
int coup_valide(SPartie* partie, SPosition* position);

/**
 * @brief fonction qui joue une partie
 * @param partie
 * @return score de la partie si < 0 NOIR gagnant si > 0 BLANC gagnant
 */
float jouerPartie(SPartie* partie);

/**
 * @biref rejoue chaque coup d'une partie (fonction faite pour le chargement
 * @param partie
 */
void rejouerPartie(SPartie* partie);

#endif /* PARTIE_H_ */
