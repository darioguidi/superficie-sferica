#include "function.h"

void DrawPoint(SDL_Renderer *renderer, Point *point)
{
    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    SDL_Rect rect = (SDL_Rect) {point->x, SCREEN_HEIGHT - point->y, SIZE_POINT, SIZE_POINT};
    SDL_RenderFillRect(renderer, &rect);
}

void DrawSurface(SDL_Renderer *renderer, int number_points, float radius)
{
    Point *surface = malloc(number_points*sizeof(Point));
    Point center = {SCREEN_OFFSET_X, SCREEN_OFFSET_Y, 0.0f};

    float offset = 2.0f / number_points;
    float increment = PI * (3.0f - sqrt(5.0f)); // sfera di Fibonacci


    for (int i = 0; i < number_points; i++) {
        float y = ((i * offset) - 1.0f) + (offset / 2.0f);
        float r = sqrt(1.0f - y * y);
        float theta = i * increment;

        float x = r * cosf(theta);
        float z = r * sinf(theta);

        surface[i].x = center.x + radius * x;
        surface[i].y = center.y + radius * y;
        surface[i].z = center.z + radius * z;
        DrawPoint(renderer, (surface+i));
    }
    free(surface);
}

void DrawPlane(SDL_Renderer *renderer, int length)
{
    Point *plane = malloc((4*length)*sizeof(Point));
    float offset = length/2;
    Point center = {SCREEN_OFFSET_X, SCREEN_OFFSET_Y, 0.0f};
    int index = 0;

    for(int j=0;j<length;j++){
        (plane+index)->x = (center.x-offset)+j;
        (plane+index)->y = 0;
        (plane+index)->z = (center.z+offset);
        DrawPoint(renderer, (plane+j));
        index++;
    }
    for(int j=0;j<length;j++){
        (plane+index)->x = (center.x-offset);
        (plane+index)->y = 0;
        (plane+index)->z = (center.z-offset)+j;
        DrawPoint(renderer, (plane+j));
        index++;
    }
    for(int j=0;j<length;j++){
        (plane+index)->x = (center.x-offset)+j;
        (plane+index)->y = 0;
        (plane+index)->z = (center.z-offset);
        DrawPoint(renderer, (plane+j));
        index++;
    }
    for(int j=0;j<length;j++){
        (plane+index)->x = (center.x+offset);
        (plane+index)->y = 0;
        (plane+index)->z = (center.z-offset)+j;
        DrawPoint(renderer, (plane+j));
        index++;
    }
    
    free(plane);
}