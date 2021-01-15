#include "gestion_fournisseur.h"
/**
Fonction de saisie d'un Fournisseur
*/
Fourni saisie_new_Fourni(Fourni *f)
{
    printf("introduire le code du fournisseur :");
    scanf("%d",&f->code);
    saisie_adresse(&f->adr);
    printf("introduire le numero du fournisseur :");
    scanf("%ld",&f->tel);

}

void saisie_liste_fournisseur(int nb, Fourni TABFOURNISSEUR[])
{
    int i;

    for(i=0; i<nb; i++)
    {
        //Saisie de la première partie du fournisseur : le code
        printf("introduire le code du fourniseur :");
        scanf("%d",&TABFOURNISSEUR[i].code);
  //saisie de le deuxiemme partie du fournisseur : l'adresse
        saisie_adresse(&TABFOURNISSEUR[i].adr);
        //saisie de la troisieme partie du fournisseur : Numero de télephone
        printf("Entrez le numero de telephone :");
        scanf("%ld",&TABFOURNISSEUR[i].tel);


    }
}

void affiche_liste_fournisseur(int nb, Fourni TABFOURNISSEUR[])
{
int i;
    for(i=0; i<nb; i++)
    {
        printf("|%d|%d|%ld|\n",i+1,TABFOURNISSEUR[i].code,TABFOURNISSEUR[i].tel);
      affiche_adresse(TABFOURNISSEUR[i].adr);
    }
}

void permuter_adr(Adr * adrA, Adr * AdrB)
{
Fourni AIDE;

}


void permuter_fourni(Fourni *A, Fourni *B)
{
Fourni AIDE;

 AIDE.code = A->code;
 AIDE.tel= A->tel;

    A->code = B->code;
    A->tel = B->tel;

    B->code = AIDE.code;
    B->tel=  AIDE.tel;

}
void tri_liste_code_fournisseur(int N, Fourni TABFOURNISSEUR[])
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
            if (TABFOURNISSEUR[j].code>TABFOURNISSEUR[i].code)
            {
                permuter_fourni(&TABFOURNISSEUR[j],&TABFOURNISSEUR[i]);
            }
        }
    }
}
void tri_liste_adr_fournisseur(int N, Fourni TABFOURNISSEUR[])
{
  int i;
    int j;
    for (i=0; i<N-1; i++)
    {
        for (j=i+1; j<N; j++)
        {
            if (strcmp(TABFOURNISSEUR[j].adr.nomville, TABFOURNISSEUR[i].adr.nomville)>0)
            {
                permuter_fourni(&TABFOURNISSEUR[j],&TABFOURNISSEUR[i]);
            }
        }
    }
}
int rechercher_fournisseur_in_tab(int nb, Fourni TABFOURNISSEUR[], Fourni fourniToFind)
{
  int i;
    int POS;


    /**Recherche de la valeur */
    for(i=0, POS = -1; i<nb; i++)
    {
        if(TABFOURNISSEUR[i].code==fourniToFind.code && TABFOURNISSEUR[i].tel!=fourniToFind.tel)
        {
            POS = i;
            i = nb;
        }
    }
    return POS;
}
int insert_nouveau_fournisseur(int nb, Fourni TABFOURNISSEUR[], Fourni fourniToInsert)
{
int res = 0; // le résultat est par défaut = 0

    if(nb<MAX_SIZE_TAB_FOURNISSEUR)  // si le tableau n'est pas complètement remplis
    {
      TABFOURNISSEUR[nb].code= fourniToInsert.code; // on insert le produit à la fin du tableau
      strcpy(TABFOURNISSEUR[nb].adr.nomville, fourniToInsert.adr.nomville); // on insert le produit à la fin du tableau
       res = 1; // l'insertion s'est bien passée du coup on renvoi 1
    }
    return (res);
}
void load_liste_fournisseurs_from_file(int* nb, Fourni TABFOURNISSEUR[], char* file_path)
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
        sscanf(ligne,"%d|%s|",&TABFOURNISSEUR[i].code,&TABFOURNISSEUR[i].tel);

        i++;
    }
    *nb=i;
    fclose(fp_read);
}
void save_liste_fournisseurs_into_file(int nb, Fourni TABFOURNISSEUR[], char* file_path)
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
        fprintf(fp_write,"%d|%ld|\n",TABFOURNISSEUR[i].code,TABFOURNISSEUR[i].tel);

    }
    fclose(fp_write);
}


void save_adr_fournisseurs_into_file(int nb, Fourni TABFOURNISSEUR[], char* file_path)
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
        fprintf(fp_write,"%d|\n",TABFOURNISSEUR[i].adr.num);

    }
    fclose(fp_write);
}



//void save_liste_fournisseurs_into_bdd(int N, Fourni TABFOURNISSEUR[], char* nom_bd_to_save,MYSQL*mysql)
//{
//TO DO
int i = 0;
    char sql[256];

  /*  mysql_options(mysql,MYSQL_OPT_WRITE_TIMEOUT,"option");
    if(mysql_real_connect(mysql, "127.0.0.1" , "root", "", nom_bd_to_save, 0, NULL, 0) == NULL)
        {
        printf("Une erreur s'est produite lors de la connexion à la BDD: %s", nom_bd_to_save);
        return;
    }
    while (i < N) {
        snprintf(sql, sizeof(sql), "INSERT INTO Fournisseur (code, tel) VALUES('%d', '%ld')", TABFOURNISSEUR[i].code, TABFOURNISSEUR[i].tel);

        if(mysql_query(mysql, sql)) {
            fprintf(stderr, "%s\n", mysql_error(mysql));
        }
        i++;
    }*/
//}


//void load_liste_fournisseurs_from_bdd(int* N,Fourni TABFOURNISSEUR[], char* nom_bd_to_load, MYSQL*mysql)
//{
   /*mysql_options(mysql,MYSQL_READ_DEFAULT_GROUP,"option");
    if(mysql_real_connect(mysql,"127.0.0.1" ,"root","",nom_bd_to_load,0,NULL,0))
//   if(mysql_real_connect(&mysql,"192.168.43.208","root","","tp1_cinema",0,NULL,0))
    {
 //Requête qui sélectionne tout dans ma table scores
        mysql_query(mysql, "SELECT * FROM fournisseur");
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
            TABFOURNISSEUR[j-1].code = atoi(row[1]);    //la troisème colonne de l'uplet
            TABFOURNISSEUR[j-1].tel = (float)atol(row[2]); //la quatrième colonne de l'uplet
            printf("** Tab : code %d tel %ld ",TABFOURNISSEUR[j-1].code, TABFOURNISSEUR[j-1].tel);

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

void affiche_adresse(Adr adr_to_show){
printf("%d|%s|%s|%d|%s \n",adr_to_show.num,adr_to_show.nomrue,adr_to_show.nomville,adr_to_show.codePostal,adr_to_show.nomPays);
}


void saisie_adresse(Adr * adr_to_insert)
{
    printf("numero rue : ");
    scanf("%d", &adr_to_insert->num);

    printf("nom rue : ");
    scanf("%s", adr_to_insert->nomrue);

    printf("nom ville : ");
    scanf("%s", adr_to_insert->nomville);

    printf("code postl : ");
    scanf("%d", &adr_to_insert->codePostal);

    printf("nom pays : ");
    scanf("%s", adr_to_insert->nomPays);
}


void saisie_date(date * d_to_insert)
{
    //Saisie de la date
    printf("Jour : ");
    scanf("%d", &d_to_insert->jour);

    printf("Mois : ");
    scanf("%d", &d_to_insert->mois);

    printf("Annee : ");
    scanf("%d", &d_to_insert->annee);
}

void affiche_date(date d)
{
    printf("%d/%d/%d",d.jour,d.mois,d.annee);
}



