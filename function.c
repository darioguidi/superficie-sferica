#include "function.h"

void DrawPoint(SDL_Renderer *renderer, Point *point)
{
    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    SDL_Rect rect = (SDL_Rect) {point->x, SCREEN_HEIGHT - point->y, SIZE_POINT, SIZE_POINT};
    SDL_RenderFillRect(renderer, &rect);
}

void DrawSurface(SDL_Renderer *renderer, int number_points, float phi, float theta)
{
    Point center = {SCREEN_OFFSET_X, SCREEN_OFFSET_Y, 0.0f};
    float radius = 200.0f;  // Raggio della sfera

    float offset = 2.0f / number_points;
    float increment = PI * (3.0f - sqrt(5.0f)); // sfera di Fibonacci

    for (int i = 0; i < number_points; i++) {
        float y = ((i * offset) - 1.0f) + (offset / 2.0f);
        float r = sqrt(1.0f - y * y);
        float local_theta = i * increment;

        float x = r * cos(local_theta);
        float z = r * sin(local_theta);

        // Rotazione attorno all'asse X (phi)
        float y1 = y * cosf(phi) - z * sinf(phi);
        float z1 = y * sinf(phi) + z * cosf(phi);

        // Rotazione attorno all'asse Y (theta)
        float x2 = x * cosf(theta) + z1 * sinf(theta);
        float z2 = -x * sinf(theta) + z1 * cosf(theta);

        // Calcolo luminosità in base a z2 (profondità)
        float brightness = (z2 + 1.0f) / 2.0f; // normalizza da 0 a 1
        int color = (int)(brightness * 255);
        if(color < 0) color = 0;
        if(color > 255) color = 255;

        SDL_SetRenderDrawColor(renderer, color, color, color, 255);

        Point point;
        point.x = center.x + radius * x2;
        point.y = center.y + radius * y1;

        SDL_Rect rect = { (int)point.x, SCREEN_HEIGHT - (int)point.y, SIZE_POINT, SIZE_POINT };
        SDL_RenderFillRect(renderer, &rect);
    }
}