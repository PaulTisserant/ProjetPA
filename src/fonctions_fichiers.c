#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "fonctions_fichiers.h"
#include "objet.h"
#include <math.h>


/*
 allouer un tableau de caractères de taille n × m, 
 où n et m sont les nombres de lignes et de colonnes 
 et initialiser ce tableau avec le caractère espace (’ ’).
*/

char** allouer_tab_2D(int n, int m) {

    char **tab = (char**)malloc(n*sizeof(char *));


    for(int i = 0; i < n; ++i) {
        tab[i] = (char*)malloc(m*sizeof(char));
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            tab[i][j] = ' ';
        }
    }

    return tab;
}

/*
 libérer un tableau à deux dimensions, de n lignes.
*/ 
void desallouer_tab_2D(char** tab, int n) {
    for(int i = 0; i < n; ++i){
        free(tab[i]);
    }

}

/*
 afficher le contenu d’un tableau de caractères de taille n × m.
*/
void afficher_tab_2D(char** tab, int n, int m) {
    for (int i = 0; i < n; i++) {
        
        for (int j = 0; j < m; j++) {
             printf("%c ", tab[i][j]);
        }
        printf("\n");
        
    }
}

/*
 compter le nombre max de lignes (nbLig) et de colonnes (nbCol) dans le fichier dont le nom est nomFichier
*/
void taille_fichier(const char* nomFichier, int* nbLig, int* nbCol) {
    
    FILE* fichier = NULL ;
    fichier = fopen(nomFichier, "r") ;
    int c ;
    int max = 0;

    if (fichier != NULL) {
        do {
            c = fgetc(fichier);
            if (c == '\n' || c == '\r'||c == EOF)
            {
                if (*nbCol > max) {
                    max = *nbCol;
                }
                (*nbLig) ++;
                (*nbCol) = 0;
                if (c == '\r') {
                    c = fgetc(fichier);
                }
            } else {
                (*nbCol) ++;
            }

        } while (c != EOF) ;

        *nbCol = max;
        fclose(fichier);
    }else {
        printf("fichier introuvable");
    }

 
    
}


/*
 lire un fichier dont le nom est nomFichier
 et retourner le tableau qui contient les caractères du fichier
 tel qu’une ligne du tableau correspond à une ligne du fichier.
*/
char** lire_fichier(const char* nomFichier) {
    int ligne = 0;
    int colonne = 0;

    int lig = 0;
    int col = 0;

    taille_fichier(nomFichier, &ligne, &colonne);

    //printf("%d,%d \n",ligne,colonne);

    //afficher nomFichier
    printf("nomFichier : %s \n",nomFichier);

    char **tab = allouer_tab_2D(ligne,colonne);

    FILE* fichier = NULL ;
    fichier = fopen(nomFichier, "r") ;
    int c ;
    if (fichier != NULL) {
         do {
            c = fgetc(fichier);
            if (c == '\n' || c == '\r' ||c == EOF)
            {
                lig ++;
                col = 0;
                if (c == '\r') {
                    c = fgetc(fichier);
                }
            } else {
                //printf("%d,%d,%c \n",lig,col,c);
                tab[lig][col] = c;
                col ++;
            }


        } while (c != EOF) ;

        fclose(fichier);
    }else {
        printf("fichier introuvable ??????");
    }

    return tab;
}


//Fonction permettant de remplacer les caracteres d'une chaine de caracteres par des caracteres vides
void char_array_empty(char* char_array) {
    for (int i = 0; char_array[i] != '\0'; i++) {
        //if (!(char_array[i] >= '0' && char_array[i] <= '9'))
        {
            printf("\nchar_array[i] =%c",char_array[i]);
            char_array[i] = ' ';
        }
    }
}
/*
Fonction permettant de lire le fichier de sauvegarde
*/
void lire_sauvgarde(world_t* world) {
    int lig = 0;
    int col = 0;
    FILE* fichier = NULL ;
    fichier = fopen("sorties/Sauvegarde.txt", "r") ;


    char* nb_coup= malloc(sizeof(char)*3);
    char* nb_coup_tot= malloc(sizeof(char)*3);
    char* nb_lvl= malloc(sizeof(char)*1);

        //Convertion des caracteres présent dans la mémoire en caractere vide
        char_array_empty(nb_coup);
        char_array_empty(nb_coup_tot);
        char_array_empty(nb_lvl);
    //parcours du fichier
   int c ;

    if (fichier != NULL) {
        
         do {
            c = fgetc(fichier);
            if (c == '\n' || c == '\r' ||c == EOF)
            {
                lig ++;
                col = 0;
                if (c == '\r') {
                    c = fgetc(fichier);
                }
            } else {
                if (lig == 0 && col >= 11)
                {
                    world->pseudo[col-11] = c ;
                }     
                if (lig == 1 && col >= 11)
                {
                    nb_lvl[col-11] = c ;             
                }
                if (lig == 4 && col >= 11){
                    nb_coup[col-11] = c ;
                }
                if (lig == 5 && col >= 11){
                    nb_coup_tot[col-11] = c  ;
                    printf("c = %c",c);
                }
                col ++;
            }
        } while (c != EOF) ;
    


        //Convertions des chaines de caracteres en entier
        world->nbCoups = atoi(nb_coup);
        world->CoupsTot = atoi(nb_coup_tot);
        world->current_level =  atoi(nb_lvl);

        //liberation de la memoire
        free(nb_coup);
        free(nb_coup_tot);
        free(nb_lvl);
        fclose(fichier);
    }
}
/*
Fonction permettant de lire le fichier de sauvegarde, notament récuperer les coordonnees de la balle
*/
void lire_sauv_ball(world_t* world) {
    int lig = 0;
    int col = 0;
    char* x_ball= malloc(sizeof(char)*5);
    char* y_ball= malloc(sizeof(char)*5);
    FILE* fichier = NULL ;
    fichier = fopen("sorties/sauvegarde.txt", "r") ;
    int c ;
        char_array_empty(x_ball);
        char_array_empty(y_ball);
    if (fichier != NULL) {
        
         do {
            c = fgetc(fichier);
            if (c == '\n' || c == '\r' ||c == EOF)
            {
                lig ++;
                col = 0;
                if (c == '\r') {
                    c = fgetc(fichier);
                }
            } else {
                if (lig == 2 && col >= 11){
                    x_ball[col-11] = c ;
                }
                if (lig == 3 && col >= 11){
                    y_ball[col-11] = c ;
                }

                col ++;
            }
        } while (c != EOF) ;


        world->ball.x = atoi(x_ball);
        world->ball.y = atoi(y_ball);


        free(y_ball);
        free(x_ball);
        fclose(fichier);
    }else {
        printf("fichier introuvable ");
    }
    world->init_sauv = false ; // Chargement de la sauvegarde terminer
    
}












/*
Fonction permettant d'enregister le score du joueur dans un fichier texte.
*/
void enregistre_score(const char *filename,world_t* world) {
  // Ouvrir le fichier en écriture en fin de fichier
  FILE *file = fopen(filename, "a");
char* ligne = malloc(sizeof(char)*64) ;
char_array_empty(ligne);
sprintf(ligne,"%s%s%d%s",world->pseudo," ",world->CoupsTot,"\n");

  // Écrire la ligne dans le fichier
  fprintf(file, ligne);
  // Fermer le fichier
  fclose(file);
  free(ligne);
}

/*
 Retourner un nouveau tableau, dans lequel toutes les occurrences du
 caractère ancien sont remplacées par le caractère nouveau.
*/
char** modifier_caractere(char** tab, int n, int m, char ancien, char nouveau) {

    char** res = allouer_tab_2D(n,m);
    

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (tab[i][j] == ancien ) {
                res[i][j] = nouveau;
            } else {
                res[i][j] = tab[i][j];
            }
        }
    }

    desallouer_tab_2D(tab,n);
    return res;
}
void apply_texture(SDL_Texture *texture,SDL_Renderer *renderer,int x, int y,int w,int h,double angle){
    SDL_Rect dst = {0, 0, 0, 0};
    
    dst.w = w; 
    dst.h= h;
    dst.x = x;
    dst.y=y;
    if (angle !=0){
    SDL_RenderCopyEx(renderer, texture, NULL, &dst,angle,NULL,SDL_FLIP_NONE);
    }
    else{SDL_RenderCopy(renderer, texture, NULL, &dst);
    }

}
/*
 Écrire le tableau tab de taille n × m dans un fichier dont le nom est nomFichier.
*/
void ecrire_fichier(const char* nomFichier, char** tab, int n, int m) {

    FILE* fichier = NULL ;

    fichier = fopen(nomFichier, "w") ;

    if (fichier != NULL) {

        for (int i = 0 ; i < n; i++) {

            for (int j = 0; j < m; j++) {

                if (j == m-1 ) {
                    fputc('\n', fichier);
                } else {
                    fputc(tab[i][j], fichier);
                }

            }
            
        }
    }

    fclose(fichier);
}

SDL_Texture* charger_image (const char* nomfichier, SDL_Renderer* renderer) {

    SDL_Surface* image = SDL_LoadBMP(nomfichier);
    if(image == NULL)
    {
        fprintf(stderr, "Erreur pendant chargement image BMP: %s", SDL_GetError());
        return NULL;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    if(texture == NULL)
    {
        fprintf(stderr, "Erreur pendant creation de la texture liee a l'image chargee: %s", SDL_GetError());
        return NULL;
    }
    return texture;

}

SDL_Texture* charger_image_transparente(const char* nomfichier, SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b) {
    SDL_Surface *tmp = NULL;
    SDL_Texture *texture = NULL;
    tmp = SDL_LoadBMP(nomfichier);

    // Récupérer la valeur (RGB) du pixel au format donné.
    Uint32 valRGB = SDL_MapRGB(tmp->format, r, g, b);
    // Définir la couleur (pixel transparent) dans une surface.
    SDL_SetColorKey( tmp, SDL_TRUE, valRGB) ;

    if(tmp == NULL)
    {
        fprintf(stderr, "Erreur pendant chargement surface BMP: %s", SDL_GetError());
        return NULL;
    }
    texture = SDL_CreateTextureFromSurface(renderer, tmp);
    SDL_FreeSurface(tmp);
    if(texture == NULL)
    {
        fprintf(stderr, "Erreur pendant creation de la texture liee a l'surface chargee: %s", SDL_GetError());
        return NULL;
    }
    return texture;
    
}


/*
* affiche le trou demandé dans le renderer
*/

void display_arrow(world_t* world){
    
        world->ball.power = 0;
        world->arrow.angle = 0 ;
        world->ball.angle = 0 ;
        int posx = 0 ;
        int posy = 0 ;       
        SDL_GetMouseState(&posx,&posy); 
        world->arrow.x = world->ball.x  ;
        world->arrow.y = world->ball.y  ;
        world->arrow.w  = 20 ;
        world->arrow.h  = 20 ;
        world->arrow.is_visible = 1 ;
        //création des coordonées du point a
        int a_x = world->ball.x + world->ball.w/2 ;
        int a_y = world->ball.y + world->ball.w/2;
        //création des coordonées du point c
        int c_x = posx ;
        int c_y = posy ;
        int  c = sqrt((c_x - a_x  )*(c_x - a_x  ) + (c_y - a_y )*(c_y - a_y )  );
        //création des coordonées du point b
        int b_x = a_x;
        int b_y = a_x + c; 

        int b = sqrt((b_x -a_x)*(b_x - a_x)  + (b_y - a_y)*(b_y - a_y) );
        int a = sqrt((b_x - posx)*(b_x - posx) + (b_y - posy)*(b_y - posy) );

        //création des variables pour la formule
        
        int x1 = c*c + b*b;
        int x2 = a*a;
        float x3 = 2*b*c;
        float x4 = x1 -x2;
        float formule = x4/x3 ; // lois des cosinus
        world->ball.angle = (acos(formule));

        if (posx > a_x  ){ 
            world->ball.angle = (world->ball.angle*-1);
        }
        world->arrow.angle = world->ball.angle ;
        world->arrow.angle -=PI/2;
        world->ball.angle -=PI/2;
        world->arrow.angle = world->arrow.angle * 180/PI;
        
}
bool entre(int v1,int v2,int v3){
 return v1<=v2 && v2<=v3 ;
    
}

/*
Fonction de detection de collision entre 2 sprites
*/
bool sprites_collide(sprite_t sp2, sprite_t sp1){

    if(entre(sp1.x,sp2.x,sp1.x+sp1.w) && entre(sp1.y,sp2.y,sp1.y + sp1.h)){
        return true;
    }
    if (entre(sp1.x,sp2.x + sp2.w,sp1.x+sp1.w) && entre(sp1.y,sp2.y+sp2.h,sp1.y + sp1.h))
    {
        return true;
    }
    if (entre(sp1.x,sp2.x,sp1.x+sp1.w) && entre(sp1.y,sp2.y+sp2.h,sp1.y + sp1.h)){
        return true;
    }
    if (entre(sp1.y,sp2.y,sp1.y + sp1.h) && entre(sp1.x,sp2.x + sp2.w,sp1.x+sp1.w))
    {
        return true;
    }

    return false;
}
/*
Fonction detectant si le pointeur de la souris est en collision avec un sprite
*/
bool pointeur_collision(sprite_t sp1){
    int posx = 0 ;
    int posy = 0 ;       
    SDL_GetMouseState(&posx,&posy); 
    if (entre(sp1.x,posx,sp1.x+sp1.w) && entre(sp1.y,posy,sp1.y+sp1.h)){
        return true ;
    }
    return false;

}




// fonction pour enregistrer les champs d'une structure world_s dans un fichier texte
void enregistrer_world_s(const char *nom_fichier, const struct world_s *world)
{
  // ouvrir le fichier en mode écriture
  FILE *fichier = fopen(nom_fichier, "w");

  if (fichier != NULL)
  {
    // écrire les valeurs des champs de la structure dans le fichier
    fprintf(fichier, "Pseudo :   %s\n", world->pseudo);
    fprintf(fichier, "Levels :   %d\n", world->current_level);
    fprintf(fichier, "ball_x :   %d\n", world->ball.x);
    fprintf(fichier, "ball_y :   %d\n", world->ball.y);
    fprintf(fichier, "nbCoups:   %d\n", world->nbCoups);
    fprintf(fichier, "nbCoupsTot:%d\n", world->CoupsTot);



    // fermer le fichier
    fclose(fichier);
  }
}
/*
Fonction permettant de savoir si un fichier existe
*/
bool fichier_exist(const char* nomFichier){
    FILE* fichier = NULL ;
    fichier = fopen(nomFichier, "r") ;  
    if (fichier == NULL)
    {
        return false ;
    }
    else{
        fclose(fichier);
        return true ;
    }

    
}
/*
Fonction permettant de connaitre le nombres de niveaux grace aux fichiers hole(num).txt
*/
int nombres_niveau(){
    int f  = 1;
    char* nom_niveau = malloc(sizeof(char)*32);
    sprintf(nom_niveau, "niveaux/hole1.txt");
    while(fichier_exist(nom_niveau)){
        f++ ;
        sprintf(nom_niveau, "niveaux/hole%d.txt", f);
    }
    free(nom_niveau);
    return f - 1;

}
