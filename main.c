#include "function.h"

float phi_sphere = 0.0f;
float theta_sphere = 0.0f;

float theta_plane_x = 0.0f;
float theta_plane_y = 0.0f;
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

    int length_plane, step;
    float radius;

    printf("Quanti punti devono rappresentare la superficie sferica? \n");
    scanf("%d", &step);
    printf("Inserire raggio della sfera\n");
    scanf("%f", &radius);
    printf("Quanto deve essere grande il tuo piano?\n");
    scanf("%d", &length_plane);

    Point *plane = malloc((4 * length_plane) * sizeof(Point));
    int number_points_sphere = step * step; 
    Point *surface = malloc(number_points_sphere * sizeof(Point));

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

                // Rotazione piano asse X
                if(event.key.keysym.sym == SDLK_s){   
                    theta_plane_x -= 0.1f;
                }
                if(event.key.keysym.sym == SDLK_w){  
                    theta_plane_x += 0.1f;
                }

                // Rotazione piano asse Z 
                if(event.key.keysym.sym == SDLK_e){   
                    theta_plane_z += 0.1f;
                }
                if(event.key.keysym.sym == SDLK_q){   
                    theta_plane_z -= 0.1f;
                }
                
                // Rotazione piano asse Y 
                if(event.key.keysym.sym == SDLK_d){   
                    theta_plane_y += 0.1f;
                }
                if(event.key.keysym.sym == SDLK_a){   
                    theta_plane_y -= 0.1f;
                }

                if(event.key.keysym.sym == SDLK_UP){   
                    theta_sphere += 0.1f;
                }
                if(event.key.keysym.sym == SDLK_DOWN){   
                    theta_sphere -= 0.1f;
                }

                if(event.key.keysym.sym == SDLK_RIGHT){   
                    phi_sphere += 0.1f;
                }
                if(event.key.keysym.sym == SDLK_LEFT){   
                    phi_sphere -= 0.1f;
                }

            }
        }

        SDL_SetRenderDrawColor(renderer, 0,0,0,255);
        SDL_RenderClear(renderer);

        DrawSurface(renderer, surface, step, radius, phi_sphere, theta_sphere);
        DrawPlane(renderer, plane, length_plane, theta_plane_x, theta_plane_y, theta_plane_z);

        phi_sphere+=0.0005f;
        theta_sphere+=0.0005f;

        SDL_RenderPresent(renderer);
    }

    free(plane);
    free(surface);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}