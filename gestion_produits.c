#include "gestion_produits.h"

/**
Fonction de saisie d'un produit
*/
Prod saise_new_prod()
{
    Prod p;
    printf("introduire le nom du produit :");
    scanf("%s",p.nom);
    p.nom[40]='\0'; // on ajouter \0 pour la fin de la chaine de caratère
    //Saisie de la deuxième partie du produit : le prix
    printf("introduire le prix du produit :");
    scanf("%f",&p.prix);

    return p;
}

/***
Fonction de saisie de la liste de produit
*/
void saisie_liste_produit(int nb, Prod TABPROD[])
{
    int i;

    for(i=0; i<nb; i++)
    {
        //Saisie de la première partie du produit : le nom
        printf("introduire le nom du produit :");
        scanf("%s",TABPROD[i].nom);
        TABPROD[i].nom[40]='\0'; // on ajouter \0 pour la fin de la chaine de caratère
        //Saisie de la deuxième partie du produit : le prix
        printf("introduire le prix du produit :");
        scanf("%f",&TABPROD[i].prix);
    }
}
/**
Fonction d'affichage d'un tableau de structure
*/
void affiche_liste_produit(int nb, Prod TABPROD[])
{
    int i;
    for(i=0; i<nb; i++)
    {
        printf("|%d|%s|%f|\n",i+1,TABPROD[i].nom,TABPROD[i].prix);

    }
}
/**
Fonction de Permutation de deux variable de type structure
*/
void permuter(Prod *A, Prod *B)
{
    Prod AIDE;

    AIDE.prix = A->prix;
    strcpy(AIDE.nom, A->nom);

    A->prix = B->prix;
    strcpy(A->nom, B->nom);

    B->prix = AIDE.prix;
    strcpy(B->nom, AIDE.nom);
}
/***
Fonction de tri de tableau de structure par prix
*/
void tri_liste_produit_prix(int N, Prod TABPROD[])
{
    int i;
    int j;
    /********************************************************/
    /**Trie à Bull du tableau**/
    /********************************************************/
    for (i=0; i<N-1; i++)
    {
        for (j=i+1; j<N; j++)
        {
            if (TABPROD[j].prix>TABPROD[i].prix)
            {
                permuter(&TABPROD[j],&TABPROD[i]);
            }
        }
    }
}

/***
Fonction de Tri d'un tableau de structure par nom
*/
void tri_liste_produit_nom(int N, Prod TABPROD[])
{
    int i;
    int j;
    for (i=0; i<N-1; i++)
    {
        for (j=i+1; j<N; j++)
        {
            if (strcmp(TABPROD[j].nom,TABPROD[i].nom)>0)
            {
                permuter(&TABPROD[j],&TABPROD[i]);
            }
        }
    }
}
/**
Retourne 1 ou 0 selon le resultat de l'insertion
*/
int insert_nouveau_produit(int nb, Prod TABPROD[], Prod produitToInert)
{
    int res = 0; // le résultat est par défaut = 0

    if(nb<MAX_SIZE_TAB)  // si le tableau n'est pas complètement remplis
    {
        TABPROD[nb].prix= produitToInert.prix; // on insert le produit à la fin du tableau
        strcpy(TABPROD[nb].nom, produitToInert.nom); // on insert le produit à la fin du tableau
        res = 1; // l'insertion s'est bien passée du coup on renvoi 1
    }
    return (res);
}


/**
Fonction qui retourne la posiion dans le tableau oubien -1
*/
int recherche_produit_into_list_produit(int N, Prod TABDPROD[], Prod produitToFind)
{
    int i;
    int POS;

    /**Recherche de la valeur */
    for(i=0, POS = -1; i<N; i++)
    {
        if(TABDPROD[i].prix==produitToFind.prix && !strcmp(TABDPROD[i].nom,produitToFind.nom))
        {
            POS = i;
            i = N;
        }
    }
    return POS;
}

/**
Fonction de chargement d'un tableau de structure à partir
d'un fichier text
*/

void load_liste_produit_from_file(int *nb, Prod TABPROD[], char* file_path)
{
    /**Déclaration des variable*/
    FILE* fp_read = NULL;
    int i = 0;
    char ligne[100];
    char c;
    /**Ecriture strcuturée*/
    fp_read= fopen(file_path,"r");/**r:read ; w: write ; a : append*/
    if(!fp_read)
    {
        printf("Erreur de l'ouverture du fichier");
        exit(-1);
    }
    while(fgets(ligne,100,fp_read))
    {
        sscanf(ligne,"%f|%s",&TABPROD[i].prix,TABPROD[i].nom);
        i++;
    }
    *nb=i;
    fclose(fp_read);
}
/**
Fonction d'enregistrement d'un tableau de structure dans un fichier text
*/
void save_liste_produit_into_file(int nb, Prod TABPROD[], char* file_path)
{
    FILE* fp_write = NULL;
    int i;
    fp_write= fopen(file_path,"w");/**r:read ; w: write ; a : append*/
    if(!fp_write)
    {
        printf("Erreur de creation du fichier");
        exit(-1);
    }

    for(i = 0; i<nb; i++)
    {
        fprintf(fp_write,"%3.5f|%s\n",TABPROD[i].prix,TABPROD[i].nom);
    }
    fclose(fp_write);
}

/**
Load liste produit from DB
*/
//void load_liste_produit_from_DB(int* N,Prod tabProd[], char* nom_bd_to_load, MYSQL*mysql)
//{
/*    mysql_options(mysql,MYSQL_READ_DEFAULT_GROUP,"option");
    if(mysql_real_connect(mysql,"127.0.0.1" ,"root","",nom_bd_to_load,0,NULL,0))
    //if(mysql_real_connect(&mysql,"192.168.43.208","root","","tp1_cinema",0,NULL,0))
    {
        //Requête qui sélectionne tout dans ma table scores
        mysql_query(mysql, "SELECT * FROM Produit ORDER BY nom");
        //Déclaration des pointeurs de structure
        MYSQL_RES *result = NULL;
        MYSQL_ROW row;
        unsigned int i = 0;
        unsigned int num_champs = 0;
        int j = 1;
        //On met le jeu de résultat dans le pointeur result
        result = mysql_use_result(mysql);
        //On récupère le nombre de champs
        num_champs = mysql_num_fields(result);
        //on stock les valeurs de la ligne choisie
        while ((row = mysql_fetch_row(result)))
        {
            //On déclare un pointeur long non signé pour y stocker la taille des valeurs
            unsigned long *lengths;
            //On stocke ces tailles dans le pointeur
            lengths = mysql_fetch_lengths(result);

            //On fait une boucle pour avoir la valeur de chaque champs
            strcpy(tabProd[j-1].nom, row[2]);    //la troisème colonne de l'uplet
            tabProd[j-1].prix = (float)atoi(row[3]); //la quatrième colonne de l'uplet
            printf("** Tab : prix %f nom %s ",tabProd[j-1].prix, tabProd[j-1].nom);

            //On affiche la position du produit
            printf("%ld- ", j);
            //OPTIONNEL JUSTE UN AFFICHAGE
            for(i = 1; i < num_champs; i++)
            {
                //On ecrit toutes les valeurs
                printf("%.*s ", (int) lengths[i], row[i] ? row[i] : "NULL");
            }
            printf("\n");
            //On incrémente la position du joueur
            j++;
        }
        *N=j-1;
        //Libération du jeu de résultat
        mysql_free_result(result);
    }
    else
    {
        printf("Une erreur s'est produite lors de la connexion à la BDD: %s", mysql_error(mysql));
    }*/
//}

//void save_liste_produit_into_DB(int N,Prod tabProd[],char* nom_bd_to_save, MYSQL*mysql)
//{
   /* int i = 0;
    char sql[256];

         mysql_options(mysql,MYSQL_OPT_WRITE_TIMEOUT,"option");
    if(mysql_real_connect(mysql, "127.0.0.1" , "root", "", nom_bd_to_save, 0, NULL, 0) == NULL) {
        printf("Une erreur s'est produite lors de la connexion à la BDD: %s", nom_bd_to_save);
        return;
    }
    while (i < N) {
        snprintf(sql, sizeof(sql), "INSERT INTO produit (nom, prix) VALUES('%s', '%f')", tabProd[i].nom, tabProd[i].prix);

        if(mysql_query(mysql, sql)) {
            fprintf(stderr, "%s\n", mysql_error(mysql));
        }
        i++;
    }*/
//}

