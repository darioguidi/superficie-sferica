#include "function.h"

void DrawPoint(SDL_Renderer *renderer, Point *point)
{
    SDL_SetRenderDrawColor(renderer, 0,0,0,255);
    SDL_Rect rect = (SDL_Rect) {point->x, point->y, SIZE_POINT, SIZE_POINT};
    SDL_RenderDrawRect(renderer, &rect);
}

void DrawSurface(SDL_Renderer *renderer, int number_points)
{
    Point *surface = malloc(number_points*sizeof(Point));

    for(int i=0;i<number_points;i++){
        
        DrawPoint(renderer, surface+i);
    }
}