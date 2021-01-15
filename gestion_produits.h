
#ifndef _gestion_produit_h
#define _gestion_produit_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <winsock.h>
//#include <mysql.h>



#define MAX_SIZE_TAB 100
#define SAISIE_TAB_LIST_CLAVIER 1
#define LOAD_TAB_FROM_FILE 2
#define LOAD_TAB_FROM_DB 3
#define AFFICHE_TAB_PRO 4
#define TRI_PROD_PRIX 5
#define TRI_PROD_NOM 6
#define INSERT_NEW_PROD 7
#define FIND_PROD_IN_TAB 8
#define SAVE_TAB_IN_FILE 9
#define SAVE_TAB_IN_DB 10
#define QUITTER 21

struct Produit
{
    char nom[40];
    float prix;
};
typedef struct Produit Prod;

void saisie_liste_produit(int nb, Prod TABPROD[]);
Prod saise_new_prod();
void affiche_liste_produit(int nb, Prod TABPROD[]);
void tri_liste_produit_prix(int nb, Prod TABPROD[]);
void tri_liste_produit_nom(int nb, Prod TABPROD[]);
void permuter(Prod *A, Prod *B);
int insert_nouveau_produit(int nb, Prod TABPROD[], Prod produitToInert);
void load_liste_produit_from_file(int *nb, Prod TABPROD[], char* file_path);
void save_liste_produit_into_file(int nb, Prod TABPROD[], char* file_path);
//void load_liste_produit_from_DB(int* N, Prod tabProd[], char* nom_bd_to_load, MYSQL*mysql);
//void save_liste_produit_into_DB(int N, Prod tabProd[], char* nom_bd_to_save, MYSQL*mysql);
int recherche_produit_into_list_produit(int N, Prod TABDPROD[], Prod produitToFind);
#endif // _gestion_produit_h
