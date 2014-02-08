#ifndef __MATRICE_H__
#define __MATRICE_H__

#include <stdio.h>

/**
  * @author : Bacas Kévin & Louis Delbosc
  * @version : 1.0
  * @file : matrice.h
  */

/** 
  * @brief Définie un type de donnée représentant une matrice contenant des caractères.
  * @variable donnees : Tableau de données représentant la Matrice de jeu.
  * @variable nbLigne : Nombre de lignes de la Matrice.
  * @variable nbColonne : Nombre de colonnes de la Matrice.
  */
typedef struct matrice Matrice;

/**
 * @fn Matrice* allouerMatrice(int nbLig, int nbCol)
  * @brief Alloue une matrice avec les dimensions passées en paramètre.
  * @param nbLig : Nombre de lignes.
  * @param nbCol : Nombre de colonnes.
  * @return : Retourne la matrice allouée précedement.
  */
Matrice* allouerMatrice(int nbLig, int nbCol);

/**
 * @fn Matrice* chargerMatrice(FILE* fichier)
  * @brief Charge une matrice à partir d'un fichier dont le nom est passé en paramètre.
  * @param fichier : Nom du fichier à charger.
  * @return : Retourne la matrice chargée.
  */
Matrice* chargerMatrice(FILE* fichier);

/**
 * @fn void afficherMatrice(Matrice* matrice)
  * @brief Affichier le contenu d'une Matrice.
  * @param matrice : Matrice à afficher.
  */
void afficherMatrice(Matrice* matrice);

/**
 * @fn void sauvegarderMatrice(Matrice* matrice, FILE* fichier);
  * @brief Sauvegarde une Matrice dans un fichier.
  * @param matrice : Matrice à sauvegarder.
  * @param nom_fichier : Nom du fichier dans lequel on sauvegarde.
  */
void sauvegarderMatrice(Matrice* matrice, FILE* fichier);

/**
 * @fn int supprimerMatrice(char* nom_fichier)
  * @brief Supprime un fichier contenant une matrice
  * @param nom_fichier bom du fichier.
  * @return 1 si ok sinon 0;
  */
int supprimerMatrice(char* nom_fichier);

/**
 * @fn void desallouerMatrice(Matrice* matrice)
  * @brief desalloue la matrice
  * @param matrice : Matrice à supprimer.
  */
void desallouerMatrice(Matrice* matrice);

/**
 * @fn char getValeurMatrice(Matrice* matrice, int x, int y)
  * @brief retourne la valeur a une position donnee
  * @param matrice : Matrice concernee.
  * @param x abscisse
  * @param y ordonnee
  * @return le caractere dans la case demande
  */
char getValeurMatrice(Matrice* matrice, int x, int y);

/**
 * @fn void setValeurMatrice(Matrice* matrice, int x, int y, char valeur)
  * @brief modifie la valeur a une position donnee
  * @param matrice : Matrice concernee.
  * @param x abscisse
  * @param y ordonnee
  * @param valeur valeur a modifie
  */
void setValeurMatrice(Matrice* matrice, int x, int y, char valeur);

/**
 * @fn int getNbLigne(Matrice* matrice)
 * @param matrice matrice concernee
 * @return le nombre de lignes
 */
int getNbLigne(Matrice* matrice);

/**
 * @fn int getNbColonne(Matrice* matrice)
 * @param matrice matrice concernee
 * @return le nombre de colonnes
 */
int getNbColonne(Matrice* matrice);

// TODO : DOC
int nbLigneMatrice(Matrice* matrice);

int nbColonneMatrice(Matrice* matrice);

#endif
