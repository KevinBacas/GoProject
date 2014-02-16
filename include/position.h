#ifndef __POSITION__
#define __POSITION__

/**
 * @struct SPosition
 */
typedef struct
{
	int x;
	int y;
} SPosition;

/**
 * @brief creer une position
 * @param x
 * @param y
 * @return position alloue dynamiquement
 */
SPosition* creerPosition(int x, int y);

/**
 * @brief detruit une position
 * @param position
 */
void detruirePosition(SPosition* position);

/**
 * @brief getter sur le x de la position
 */
int abscissePosition(SPosition* position);

/**
 * @brief getter sur le y de la position
 */
int ordonneePosition(SPosition* position);

/**
 * @brief position decallee sur la gauche
 */
SPosition* positionGauche(SPosition* position);

/**
 * @brief position decallee sur la droite
 */
SPosition* positionDroite(SPosition* position);

/**
 * @brief position decallee sur la bas
 */
SPosition* positionBas(SPosition* position);

/**
 * @brief position decallee sur la haut
 */
SPosition* positionHaut(SPosition* position);

/**
 * @brief transforme la position saisie en position
 * @param saisie
 * @return position allouee
 */
SPosition* transformerPosition(char* saisie);

/**
 * @brief Test si les positions sont eguales.
 * @return 1 si vrai sinon 0.
 */
int positionsEgale(void* pos1, void* pos2);

#endif
