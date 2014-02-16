#ifndef __FILE_H__
#define __FILE_H__

#include <stdlib.h>
#include <stdio.h>

/**
 * @struct node
 * @brief structure contenant un noeud de la liste simplement chainee
 */
typedef struct node SListNode;

/**
 * @struct list
 * Structure definissant une liste simplement chainee
 */
typedef struct list SList;

/**
 * @brief initialise une liste simplement chainee
 * @return liste simplement chainee alouee dynamiquement
 */
SList* listInit();

/**
 * @brief retourne l'element courant de la liste
 * @param list liste concernee
 * @return retourne l'element courant de la liste
 */
void* listCurrent(SList* list);

/**
 * @brief test si une liste est vide
 * @param list liste concernee
 * @return 1 si la liste est vide sinon 0
 */
int listEmpty(SList* list);

/**
 * @biref ajoute un element a la liste
 * @param list liste concernee
 * @param elem element a ajouter
 */
void listAdd(SList* list, void* elem);

/**
 * @brief passe a l'element suivant dans la liste
 * @param list liste concernee
 * @return retourn l'element suivant, NULL si on est en fin de chaine
 */
void* listNext(SList* list);

/**
 * @brief permet de revenir au debut de la liste
 * @param list liste concernee
 */
void* listHead(SList* list);

/**
 * @brief retire un element de la liste
 * @param list liste concernee
 * @param index index a supprimer, la list est indexee comme un tableau standard [[0, N]]
 * @return retourne l'element supprime de la liste
 */
void* listRemove(SList* list, int index);

/**
 * @brief supprime un element de la liste
 * @param list liste concernee
 * @param elem poiteur vers l'element a supprimer
 * @return element supprime
 */
void* listRemoveElement(SList* list, void* elem);

/**
 * @brief permet de recuperer l'element pour un index donne
 * @param list liste concernee
 * @param index index a recuperer, la list est indexee comme un tableau standard [[0, N]]
 */
void* listGetElement(SList* list, int index);

/**
 * @brief donne la taille de la liste
 * @return taille de la liste
 */
int listSize(SList* list);

/**
 * @brief recherche un element via son pointeur dans la liste
 * @param list liste concernee
 * @param elem pointeur a trouver
 * @return index ou est l'element
 */
int listFind(SList* list, void* elem);

/**
 * @brief recherche un element dans la liste via une fonction de comparaison
 * @param list liste concernee
 * @param elem element a rechercher
 * @param cmp fonction de comparaison
 * @return index ou est l'element -1 s'il n'est pas dans la liste
 */
int listSearch(SList* list, void* elem, int(*cmp)(void*, void*));

/**
 * @brief concatene deux listes
 */
SList* listConcat(SList* list1, SList* list2);

/**
 * @biref concatene deux liste dans faire de doublons
 * @param list1 liste 1
 * @param list2 liste 2
 * @param cmp fonction de comparaison
 * @return la liste creee
 */
SList* listConcatUnique(SList* list1, SList* list2, int(*cmp)(void*, void*));

/**
 * @brief supprime une liste creee sans desallouer son contenu
 */
void listDelete(SList* list);

#endif // __FILE_H__
