
#ifndef PLATEAU_H_
#define PLATEAU_H_

#include "couleur.h"
#include "matrice.h"
#include "position.h"

/**
 * @struct SPlateau
 */
typedef struct plateau SPlateau;

/**
 * @fn SPlateau* init_plateau(int taille)
 * @brief initialise un plateau dynamiquement
 * @param taille taille du plateau, c'est un tableau 2D donc de taille_finale = taille*taille
 * @return Pointeur vers le plateau
 */
SPlateau* init_plateau(int taille);

/**
 * @fn SPlateau* creer_plateau (int taille, ECouleur** grille)
 * @brief creer un plateau a partir d une grille donnee
 * @param taille taille du plateau
 * @param grille grille a affecter
 * @return Pointeur vers le plateau
 */
SPlateau* creer_plateau (int taille, Matrice* grille);

/**
 * @fn void detruire_plateau(SPlateau* plateau)
 * @brief detruit le plateau
 * @param Plateau a detruire
 */
void detruire_plateau(SPlateau* plateau);

/**
 * @fn int taille_plateau(SPlateau* plateau)
 * @brief renvoi la taille du plateau
 * @param plateau Plateau concerne
 * @return taille du plateau
 */
int taille_plateau(SPlateau* plateau);

/**
 * @fn ECouleur plateau_get(SPlateau* plateau, int x, int y)
 * @brief get la couleur a une position donnee
 * @param plateau Plateau concerne
 * @param x position en x
 * @param y position en y
 * @return Couleur de la position
 */
ECouleur plateau_get(SPlateau* plateau, SPosition* pos);

/**
 * @fn void plateau_set(SPlateau* plateau, int x, int y, ECouleur couleur)
 * @brief change la couleur a une position donnee
 * @param plateau Plateau concerne
 * @param x position en x
 * @param y position en y
 * @param couleur Couleur a mettre
 */
void plateau_set(SPlateau* plateau, SPosition* pos, ECouleur couleur);

/**
 * @fn ECouleur char_to_couleur(char c)
 * @brief converti un caractere en couleur
 * @param c Le caractere a transformer
 * @return la couleur correspondante
 */
ECouleur char_to_couleur(char c);

/**
 * @fn char couleur_to_char(ECouleur c)
 * @brief converti une couleur en caractere
 * @param c La couleur a transformer
 * @return le caractere correspondant
 */
char couleur_to_char(ECouleur c);

/**
 * @brief Sauvegarde le plateau dans sa position actuelle.
 * Si la sauvegarde se passe sans probleme, la fonction retourne 1, sinon 0
 */
int plateau_sauvegarde(SPlateau* plateau, FILE* fichier);

/**
 * @brief Charge un plateau precedement sauvegarde
 * Si le chargement n'est pas possible, retourne un Pointeur NULL
 */
SPlateau* plateau_chargement(SPlateau* plateau, FILE* fichier);


SPosition* transformerPosition(SPlateau* plateau, char* saisie);

int positionValide(SPlateau* plateau,SPosition* position);

#endif /* PLATEAU_H_ */
