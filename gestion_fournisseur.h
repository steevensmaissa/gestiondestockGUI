#ifndef _gestion_fournisseurs_h
#define _gestion_fournisseurs_h


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <winsock.h>
//#include <mysql.h>



#define MAX_SIZE_TAB_FOURNISSEUR 100
#define SAISI_TAB_LIST_CLAVIER 11
#define LOADING_TAB_FROM_FILE 12
#define LOADING_TAB_FROM_DB 13
#define AFFICHER_TAB_FOURNI 14
#define TRI_FOURNI_CODE 15
#define TRI_FOURNI_ADRESSE 16
#define INSERT_NEW_FOURNI 17
#define FIND_FOURN_IN_TAB 18
#define SAVE_F_TAB_IN_FILE 19
#define SAVE_F_TAB_IN_DB 20

struct Adresse{
int num;
char nomrue[30];
char nomville[30];
int codePostal;
char nomPays[30];
};
typedef struct Adresse Adr;

struct Fournisseur{
    //Fournisseur
    int code;
    Adr adr;
    long tel;
};
typedef struct Fournisseur Fourni;

struct Date{
    //Date
    int jour;
    int mois;
    int annee;
}; typedef struct Date date;


void saisie_liste_fournisseur(int nb, Fourni TABFOURNISSEUR[]);
Fourni saisie_new_Fourni(Fourni *f);
void affiche_liste_fournisseur(int nb, Fourni TABFOURNISSEUR[]);
void tri_liste_code_fournisseur(int nb, Fourni TABFOURNISSEUR[]);
void tri_liste_adr_fournisseur(int nb, Fourni TABFOURNISSEUR[]);
int rechercher_fournisseur_in_tab(int nb, Fourni TABFOURNISSEUR[], Fourni fourniToFind);
int insert_nouveau_fournisseur(int nb, Fourni TABFOURNISSEUR[], Fourni fourniToFind);
void load_liste_fournisseurs_from_file(int* nb, Fourni TABFOURNISSEUR[], char* file_path);
void save_liste_fournisseurs_into_file(int nb, Fourni TABFOURNISSEUR[], char* file_path);
//void save_liste_fournisseurs_into_bdd(int N, Fourni TABFOURNISSEUR[], char* nom_bd_to_save,MYSQL*mysql);
//void load_liste_fournisseurs_from_bdd(int* N,Fourni TABFOURNISSEUR[], char* nom_bd_to_load, MYSQL*mysql);
void save_adr_fournisseurs_into_file(int nb, Fourni TABFOURNISSEUR[], char* file_path);
void  saisie_date(date * date_a_saisie);
void affiche_date(date d);
void saisie_adresse(Adr * adr_to_insert);
void affiche_adresse(Adr adr_to_show);
void permuter_adr(Adr * adrA, Adr * AdrB);
void permuter_fourni(Fourni * A, Fourni * B);



#endif
