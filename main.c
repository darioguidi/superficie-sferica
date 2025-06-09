#include "function.h"

int main(void)
{
    if(SDL_Init(SDL_INIT_VIDEO) != 0){
        printf("Errore creazione del sdl\n");
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow(
        "Sphere Intersection",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_RESIZABLE
    );

    if(window == NULL){
        printf("Errore creazione della finestra\n");
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1,SDL_RENDERER_ACCELERATED);
    if(renderer == NULL){
        printf("Errore creazione del renderer\n");
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    int number_points;
    printf("Quanti punti devono rappresentare la superficie sferica? \n");
    scanf("%d", &number_points);


    int running = 1;
    SDL_Event event;

    while(running){
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                printf("Chiusura del programma\n");
                running=0;
            }
        }

        SDL_SetRenderDrawColor(renderer,0,0,0,0);
        SDL_RenderClear(renderer);
        SDL_DrawSurface(renderer, number_points);

    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}