#include "fonctions_fichiers.h"

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
        printf("fichier introuvable");
    }

    return tab;
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
    image = SDL_LoadBMP(nomfichier);
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
    
    SDL_Surface* surface = SDL_LoadBMP(nomfichier);
    surface = SDL_LoadBMP(nomfichier);

    // Récupérer la valeur (RGB) du pixel au format donné.
    Uint32 valRGB = SDL_MapRGB(surface->format, r, g, b);
    // Définir la couleur (pixel transparent) dans une surface.
    SDL_SetColorKey( surface, SDL_TRUE, valRGB) ;

    if(surface == NULL)
    {
        fprintf(stderr, "Erreur pendant chargement surface BMP: %s", SDL_GetError());
        return NULL;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
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
void displayHole(SDL_Rect* SrcR_fond, SDL_Rect  * DestR_fond, SDL_Rect* SrcR_hole, SDL_Rect* DestR_hole, SDL_Rect* SrcR_ball, SDL_Rect* DestR_ball, const char* nomFichier) {

    int ligne  = 0;
    int colonne = 0 ;

    taille_fichier(nomFichier,&ligne,&colonne);

    char** terrain = lire_fichier(nomFichier);
    




    int srcpos = 0 ;

    for (int i = 0; i < ligne; i++) {
        for (int j = 0; j < colonne; j++) 
        {
            if (terrain[i][j] == ' ') {

                SrcR_fond[srcpos].x = 0;
                SrcR_fond[srcpos].y = 0;
                SrcR_fond[srcpos].w = 32;
                SrcR_fond[srcpos].h = 32;

            }

            if (terrain[i][j] == 'O') {

                SrcR_fond[srcpos].x = 0;
                SrcR_fond[srcpos].y = 0;
                SrcR_fond[srcpos].w = 32;
                SrcR_fond[srcpos].h = 32;

                SrcR_hole->x = 0;
                SrcR_hole->y = 0;
                SrcR_hole->w = 100;
                SrcR_hole->h = 100;

                DestR_hole->x = j*32;
                DestR_hole->y = i*32;
                DestR_hole->w = 20;
                DestR_hole->h = 20; 
            }

            if (terrain[i][j] == 'X') {

                SrcR_fond[srcpos].x = 14*32;
                SrcR_fond[srcpos].y = 4*32;
                SrcR_fond[srcpos].w = 32;
                SrcR_fond[srcpos].h = 32;
            }

            if (terrain[i][j] == 'B') {

                SrcR_fond[srcpos].x = 0;
                SrcR_fond[srcpos].y = 0;
                SrcR_fond[srcpos].w = 32;
                SrcR_fond[srcpos].h = 32;

                SrcR_ball->x = 0;
                SrcR_ball->y = 0;
                SrcR_ball->w = 100;
                SrcR_ball->h = 100;

                DestR_ball->x = j*32;
                DestR_ball->y = i*32;
                DestR_ball->w = 20;
                DestR_ball->h = 20; 
            }

            srcpos++ ;
            
        }
    }

    int res ;

    for (int i = 0; i < ligne; i++) {
        for (int j = 0; j < colonne; j++) {
            res = j+colonne*i ;
            DestR_fond[res].x = j*32;
            DestR_fond[res].y = i*32;
            DestR_fond[res].w = 32;
            DestR_fond[res].h = 32;  
        }
    }

    desallouer_tab_2D(terrain, ligne);

}