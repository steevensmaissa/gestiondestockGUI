#include <stdio.h>
#include <allegro.h>
#include <time.h>
#include<allegro/gfx.h>
#include"gestion_produits.h"
#include"gestion_fournisseur.h"




int main(int argc, char *argv[])
{
    /*Déclartion des varibale**/
    int N;
    int CHOIX ;
    Prod tabProd[MAX_SIZE_TAB];
    Fourni tabFourni[MAX_SIZE_TAB_FOURNISSEUR];
    char nom_file_to_load[100];
    char nom_file_to_save[100];
    char nom_bd_to_load[1000];
    char nom_bd_to_save[1000];
    Prod p;
    Fourni f;
//    MYSQL mysql;
    int DBOPEN = 0;
    int clicx,clicy;
    int pos_x=100,pos_y=40;


    // Image mémoire servant à mémoriser l'écran
    BITMAP *page;

    // tableau pour les boutons de choix de couleurs
    int couleurs[12];

    // tableau pour les noms sur les boutons de l'interface
    char *noms[] = { "saisie","affichage","chargement.txt","chargement.sql","Recherche","tri par nom","tri par prix "," insertion","enregistrement"};
    char *noms2[] = { "Produits","Fournisseurs"};

    int fin,ymenu,couleur,nbep;

    srand(time(NULL));
    // Lancer allegro et le mode graphique
    allegro_init();
    install_mouse();
    install_keyboard();

    set_color_depth(desktop_color_depth());
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED,800,600,0,0)!=0)
    {
        allegro_message("problème mode graphique");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    show_mouse(screen);
    // dessiner une zone EXIT en haut à droit de l'écran
    rectfill(screen,0,0,40,20,makecol(0,128,0 ));
    textprintf_ex(screen,font,700,20,makecol(250, 255, 240),makecol(250, 0, 0),"EXIT");
    // déterminer les couleurs de la palette du menu
    couleurs[0]=makecol(  141, 70, 210);
    couleurs[1]=makecol( 141, 70, 210);
    couleurs[2]=makecol( 141, 70, 210);
    couleurs[3]=makecol(  141, 70, 210);
    couleurs[4]=makecol(   141, 70, 210);
    couleurs[5]=makecol(   141, 70, 210);
    couleurs[6]=makecol(   141, 70, 210);
    couleurs[7]=makecol(   141, 70, 210);
    couleurs[8]=makecol(   141, 70, 210);


    // dessiner les zones de l'interface en haut à gauche de l'écran
    for (ymenu=0; ymenu<2; ymenu++)
    {

        rectfill(screen,0,ymenu*40,117,ymenu*40+39,couleurs[ymenu]);
        rect(screen,0,ymenu*40,117,ymenu*40+39,makecol(255,255,255));
        textprintf_ex(screen,font,20,ymenu*40+20,makecol(255,255,255),-1,noms2[ymenu]);
    }

    // couleur initiale : blanc
    couleur=makecol(255,255,255);

    // Création de l'image mémoire à la taille de l'écran
    page=create_bitmap(SCREEN_W,SCREEN_H);

    // Boucle interactive
    fin=0;
    while (!fin || !key[KEY_ESC])
    {

        // afficher du texte coin supérieur gauche en x=400 y=20 (couleur=blanc)
        textprintf_ex(screen,font,400,20,makecol(0,255,0),-1," MONDE GRAPHIQUE !");

        // afficher coordonnées de la souris (%4d = format numérique largeur fixe sur 4 caractères)
        textprintf_ex(screen,font,300,300,makecol(0,255,0),makecol(0,0,0),"%4d %4d",mouse_x,mouse_y);

        // les clics

        if ( (mouse_b&1 || mouse_b&2) && mouse_y<=39 && mouse_x<=120 )
        {
            for (ymenu=0; ymenu<9; ymenu++)
            {

                rectfill(screen,310,ymenu*40,133,ymenu*40+39,couleurs[ymenu]);
                rect(screen,310,ymenu*40,133,ymenu*40+39,makecol(255,255,255));
                textprintf_ex(screen,font,140,ymenu*40+20,makecol(255,255,255),-1,noms[ymenu]);
            }
        }



        if ( (mouse_b&1 || mouse_b&2) && mouse_y<=39 && mouse_x<=310 && mouse_x>=170)
        {
            do
            {
                printf("inroduire N:");
                scanf("%d",&N);
            }
            while(N<=0||N>MAX_SIZE_TAB);
            saisie_liste_produit(N, tabProd);
        }


        if ( (mouse_b&1 || mouse_b&2) && mouse_y<=79 && mouse_y>40 && mouse_x<=310 && mouse_x>170)
        {

            affiche_liste_produit(N,tabProd);
        }

         if ( (mouse_b&1 || mouse_b&2) && mouse_y<=119 && mouse_x<=310 && mouse_x>170 && mouse_y>=80)
        {
            printf("Saisir le nom du fichier : ");
            scanf("%s",nom_file_to_load);
            load_liste_produit_from_file(&N,tabProd,nom_file_to_load);
        }

         if ( (mouse_b&1 || mouse_b&2) && mouse_y<=198 && mouse_y >=158 && mouse_x<=310 && mouse_x>170)
        {
            p = saise_new_prod();
            if(recherche_produit_into_list_produit(N, tabProd,p)==-1)
            {
                printf("produit [%s|%f] non trouve !! \n",p.nom,p.prix);
            }
            else
            {
                printf("produit [%s|%f] trouve. \n",p.nom,p.prix);
            }
        }

        if ( (mouse_b&1 || mouse_b&2) && mouse_y<=240 && mouse_y>200 && mouse_x<=310 && mouse_x>170)
        {
            tri_liste_produit_nom(N, tabProd);
        }

         if ( (mouse_b&1 || mouse_b&2) && mouse_y<=280 && mouse_y>239 && mouse_x<=310 && mouse_x>170)
        {
            tri_liste_produit_prix(N,tabProd);
        }

        if ( (mouse_b&1 || mouse_b&2) && mouse_y>281 && mouse_y<=320 && mouse_x<=310 && mouse_x>170)
        {
            p = saise_new_prod();
            if(insert_nouveau_produit(N,tabProd,p))
            {
                N++;
            }
        }
        if ( (mouse_b&1 || mouse_b&2) && mouse_y<=362 && mouse_y>321 && mouse_x<=310 && mouse_x>170)
        {
            printf("Saisir le nom du fichier : ");
            scanf("%s",nom_file_to_save);
            save_liste_produit_into_file(N,tabProd,nom_file_to_save);

        }

    }
    return 0;
} // Fin de boucle interactive
END_OF_MAIN();

