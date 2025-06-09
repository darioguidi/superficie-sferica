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

    

    return 0;
}