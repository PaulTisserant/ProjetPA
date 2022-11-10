#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "fonctions_fichiers.h"


int main() {
    

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


    // Boucle principale
    while(!terminer){

        SDL_RenderClear(ecran);

        char** terrain = lire_fichier("hole2.txt");
        
        SDL_Rect SrcR_fond[ligne*colonne] ;
        SDL_Rect DestR_fond[ligne*colonne];

        SDL_Rect SrcR_hole;
        SDL_Rect DestR_hole;

        SDL_Rect SrcR_ball;
        SDL_Rect DestR_ball;
        
        displayHole(&SrcR_fond, &DestR_fond, &SrcR_hole, &DestR_hole, &SrcR_ball, &DestR_ball, "hole2.txt");


        SDL_RenderCopy(ecran, fond, NULL, NULL);
        for (int i = 0; i < ligne*colonne; i++) {
            SDL_RenderCopy(ecran,fond,&SrcR_fond[i],&DestR_fond[i]);
        }

        SDL_RenderCopy(ecran, hole,&SrcR_hole,&DestR_hole);
        SDL_RenderCopy(ecran, ball,&SrcR_ball,&DestR_ball);

        //SDL_PollEvent ...

        

        
        SDL_PollEvent( &evenements );
        
        switch(evenements.type)
        {
            case SDL_QUIT:
                terminer = true; break;
            case SDL_KEYDOWN:
            switch(evenements.key.keysym.sym)
            {
                case SDLK_ESCAPE:
                case SDLK_q:
                    terminer = true; 
                break; 
                       
            }
        }

        SDL_RenderPresent(ecran);
    }


    // Libérer de la mémoire

    SDL_DestroyTexture(fond);
    SDL_DestroyTexture(hole);
    SDL_DestroyTexture(ball);
    SDL_DestroyRenderer(ecran);

    // Quitter SDL
    SDL_DestroyWindow(fenetre);
    SDL_Quit();
    return 0;
}