#include "function.h"

float phi = 0.0f;
float theta = 0.0f;

float phi_plane = 0.0f;
float theta_plane = 0.0f;

float theta_plane_x = 0.0f;
float theta_plane_z = 0.0f;

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;
    
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

    int number_points_sphere, length_plane;
    float radius;

    printf("Quanti punti devono rappresentare la superficie sferica? \n");
    scanf("%d", &number_points_sphere);
    printf("Inserire raggio della sfera\n");
    scanf("%f", &radius);
    printf("Quanto deve essere grande il tuo piano?\n");
    scanf("%d", &length_plane);

    int running = 1;
    SDL_Event event;

    while(running){
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                printf("Chiusura del programma\n");
                running = 0;
            }
            // Esempio di rotazione:
            else if(event.type == SDL_KEYDOWN){
                if(event.key.keysym.sym == SDLK_LEFT) theta -= 0.1f;
                if(event.key.keysym.sym == SDLK_RIGHT) theta += 0.1f;
                if(event.key.keysym.sym == SDLK_UP) phi -= 0.1f;
                if(event.key.keysym.sym == SDLK_DOWN) phi += 0.1f;
                if(event.key.keysym.sym == SDLK_LEFT && event.key.keysym.sym == SDLK_DOWN){
                    theta -=0.1f;
                    phi +=0.1f;
                } 
                if(event.key.keysym.sym == SDLK_UP && event.key.keysym.sym == SDLK_RIGHT){
                    theta += 0.1f;
                    phi -= 0.1f;
                } 
                if(event.key.keysym.sym == SDLK_LEFT && event.key.keysym.sym == SDLK_DOWN){
                    theta -=0.1f;
                    phi +=0.1f;
                } 

                // Rotazione piano asse X
                if(event.key.keysym.sym == SDLK_a){   // A per ruotare piano attorno a X negativa
                    theta_plane_x -= 0.1f;
                }
                if(event.key.keysym.sym == SDLK_d){   // D per ruotare piano attorno a X positiva
                    theta_plane_x += 0.1f;
                }

                // Rotazione piano asse Z (aggiunta)
                if(event.key.keysym.sym == SDLK_w){   // W per ruotare piano attorno a Z positiva
                    theta_plane_z += 0.1f;
                }
                if(event.key.keysym.sym == SDLK_s){   // S per ruotare piano attorno a Z negativa
                    theta_plane_z -= 0.1f;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0,0,0,255);
        SDL_RenderClear(renderer);
        DrawSurface(renderer, number_points_sphere, radius);
        DrawPlane(renderer, length_plane);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}