#ifndef __MATRICE_H__
#define __MATRICE_H__

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

// Permet de configurer le dosser et le nom de base des fichiers pour la sauvegarde
void configMatrice(char* folderName, char* baseName);

/**
  * @brief Alloue une matrice avec les dimensions passées en paramètre.
  * @param nbLig : Nombre de lignes.
  * @param nbCol : Nombre de colonnes.
  * @return : Retourne la matrice allouée précedement.
  */
Matrice allouerMatrice(int nbLig, int nbCol);

/**
  * @brief Charge une matrice à partir d'un fichier dont le nom est passé en paramètre.
  * @param fichier : Nom du fichier à charger.
  * @return : Retourne la matrice chargée.
  */
// TODO : prendre en compte la config
Matrice chargerMatrice(char* fichier);

/**
  * @brief Affichier le contenu d'une Matrice.
  * @param matrice : Matrice à afficher.
  */
void afficherMatrice(Matrice matrice);

/**
  * @brief Sauvegarde une Matrice dans un fichier.
  * @param matrice : Matrice à sauvegarder.
  * @param nom_fichier : Nom du fichier dans lequel on sauvegarde.
  */
// TODO : prendre en compte la config
void sauvegarderMatrice(Matrice matrice, char* nom_fichier);

// TODO : prendre en compte la config
int supprimerMatrice(char* nom_fichier);

// Désalloue la matrice donnée
void desallouerMatrice(Matrice matrice);

// Get la valeur pour un (x,y) donné
char getValeurMatrice(Matrice matrice, int x, int y);

// Set la valeur pour un (x,y) donné
void setValeurMatrice(Matrice matrice, int x, int y, char valeur);

#endif
