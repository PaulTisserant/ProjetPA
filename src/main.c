#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "fonctions_fichiers.h"


int main(){
    

        /*****************************************************          SDL           ******************************************************************/


    SDL_Window* fenetre; // Déclaration de la fenêtre
    SDL_Event evenements; // Événements liés à la fenêtre
    bool terminer = false;


    int ligne = 0;
    int colonne = 0;

    taille_fichier("hole2.txt", &ligne, &colonne);




    if(SDL_Init(SDL_INIT_VIDEO) < 0) // Initialisation de la SDL
    {
        printf("Erreur d’initialisation de la SDL: %s",SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }


    // Créer la fenêtre
    fenetre = SDL_CreateWindow("Fenetre SDL", SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED, colonne*32, ligne*32, SDL_WINDOW_RESIZABLE);


    if(fenetre == NULL) // En cas d’erreur
    {
        printf("Erreur de la creation d’une fenetre: %s",SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }


    // Mettre en place un contexte de rendu de l’écran
    SDL_Renderer* ecran;
    ecran = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED);

    SDL_Texture* fond = charger_image( "pavage.bmp", ecran );
    SDL_Texture*  hole = charger_image_transparente("hole.bmp",ecran,0,255,255);
    SDL_Texture*  ball = charger_image_transparente("ball.bmp",ecran,0,255,255);
    SDL_Texture*  arrow = charger_image("arrow.bmp",ecran);

                int a ,b ,c ;
                a = 150 ,c=200,  b=c;

                int x1 = c*c + b*b;
                int x2 = a*a;
                float x3 = 2*b*c;
                float x4 = x1 -x2;
                float formule = x4/x3 ; // lois des cosinus
                //printf("x1 : %i,x2:%i,x3:%f,x4:%f, tot :%f",x1,x2,x3,x4,formule) ;
                //printf(" acos :%Lf",acosl(formule));

    int power = 0;

    char** terrain = lire_fichier("hole2.txt");
    
    SDL_Rect SrcR_fond[ligne*colonne] ;
    SDL_Rect DestR_fond[ligne*colonne];

    SDL_Rect SrcR_hole;
    SDL_Rect DestR_hole;

    SDL_Rect SrcR_ball;
    SDL_Rect DestR_ball;

    SDL_Rect SrcR_arrow;
    SDL_Rect DestR_arrow;   
    displayHole(&SrcR_fond, &DestR_fond, &SrcR_hole, &DestR_hole, &SrcR_ball, &DestR_ball, "hole2.txt");

    // Boucle principale
    while(!terminer){

        SDL_RenderClear(ecran);

        

        int posx = 0 ;
        int posy = 0;
        long double angle =0;
        SDL_GetMouseState(&posx,&posy);
        display_arrow(&SrcR_arrow,&DestR_arrow,&DestR_ball, posx, posy,&angle);







        SDL_RenderCopy(ecran, fond, NULL, NULL);
        for (int i = 0; i < ligne*colonne; i++) {
            SDL_RenderCopy(ecran,fond,&SrcR_fond[i],&DestR_fond[i]);
        }

        SDL_RenderCopy(ecran, hole,&SrcR_hole,&DestR_hole);
        SDL_RenderCopy(ecran, ball,&SrcR_ball,&DestR_ball);
        SDL_RenderCopyEx(ecran, arrow,&SrcR_arrow,&DestR_arrow,angle,NULL,SDL_FLIP_NONE);

        //SDL_PollEvent ...

        

        
        SDL_PollEvent( &evenements );


        
        
        
        switch(evenements.type)
        {
            case SDL_QUIT:
                terminer = true; 
            break;

            case SDL_KEYDOWN:
                switch(evenements.key.keysym.sym) {
                    
                    case SDLK_q:
                        terminer = true; 
                    break; 
                    
                    case SDLK_SPACE:
                        printf("enfoncée");
                        power += 1;
                       
                        DestR_ball.x += 10 * cos(angle);
                        DestR_ball.y += 10 * sin(angle);
                    break; 
                        
                }
            break;
            case SDL_KEYUP:
                    case SDLK_SPACE:
                        printf("relachée");
                        printf("%d",power);
                    break; 
            break;    
            case SDL_MOUSEBUTTONDOWN:
                
                if (evenements.button.button == SDL_BUTTON_LEFT){
                    printf("pressed");
                }
                
            break;    
        }

        SDL_RenderPresent(ecran);
    }


    // Libérer de la mémoire

    SDL_DestroyTexture(fond);
    SDL_DestroyTexture(arrow);

    SDL_DestroyTexture(hole);
    SDL_DestroyTexture(ball);
    SDL_DestroyRenderer(ecran);

    // Quitter SDL
    SDL_DestroyWindow(fenetre);
    SDL_Quit();
    return 0;
}