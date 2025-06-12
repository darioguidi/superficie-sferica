#include "function.h"

void DrawPoint(SDL_Renderer *renderer, Point *point)
{
    float focal_length = 200.0f;
    float z = point->z + focal_length;

    if (z <= 0) return;

    int screen_x = (int)((point->x * focal_length) / z) + SCREEN_WIDTH / 2;
    int screen_y = (int)((-point->y * focal_length) / z) + SCREEN_HEIGHT / 2;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_Rect rect = (SDL_Rect){screen_x, screen_y, SIZE_POINT, SIZE_POINT};
    SDL_RenderFillRect(renderer, &rect);
}

void DrawSurface(SDL_Renderer *renderer, int number_points, float radius)
{
    Point *surface = malloc(number_points * sizeof(Point));

    // Centro della sfera nello spazio 3D (centrato e distante dalla camera)
    Point center = {0.0f, 0.0f, 300.0f};

    float offset = 2.0f / number_points;
    float increment = PI * (3.0f - sqrt(5.0f)); // Distribuzione Fibonacci

    for (int i = 0; i < number_points; i++) {
        float y = ((i * offset) - 1.0f) + (offset / 2.0f);
        float r = sqrt(1.0f - y * y);
        float theta = i * increment;

        float x = r * cosf(theta);
        float z = r * sinf(theta);

        surface[i].x = center.x + radius * x;
        surface[i].y = center.y + radius * y;
        surface[i].z = center.z + radius * z;

        DrawPoint(renderer, &surface[i]);
    }

    free(surface);
}

void DrawPlane(SDL_Renderer *renderer, int length)
{
    Point *plane = malloc((4 * length) * sizeof(Point));
    float offset = length / 2.0f;

    // Centro del piano nello spazio 3D (centrato e davanti alla camera)
    Point center = {0.0f, 0.0f, 300.0f};
    int index = 0;

    // Bordi del piano
    for (int j = 0; j < length; j++) {
        plane[index].x = -offset + j;
        plane[index].y = 1;
        plane[index].z = offset;
        DrawPoint(renderer, &plane[index]);
        index++;
    }

    for (int j = 0; j < length; j++) {
        plane[index].x = -offset;
        plane[index].y = 1;
        plane[index].z = -offset + j;
        DrawPoint(renderer, &plane[index]);
        index++;
    }

    for (int j = 0; j < length; j++) {
        plane[index].x = -offset + j;
        plane[index].y = 1;
        plane[index].z = -offset;
        DrawPoint(renderer, &plane[index]);
        index++;
    }

    for (int j = 0; j < length; j++) {
        plane[index].x = offset;
        plane[index].y = 1;
        plane[index].z = -offset + j;
        DrawPoint(renderer, &plane[index]);
        index++;
    }

    // Spostamento rispetto al centro
    for (int i = 0; i < 4 * length; i++) {
        plane[i].x += center.x;
        plane[i].y += center.y;
        plane[i].z += center.z;
        
        // Rotazione asse X
        float y_temp = plane[i].y;
        float z_temp = plane[i].z;
        plane[i].y = y_temp * cos(theta_plane_x) - z_temp * sin(theta_plane_x);
        plane[i].z = y_temp * sin(theta_plane_x) + z_temp * cos(theta_plane_x);

        // Rotazione asse Z
        float x_temp = plane[i].x;
        float y_temp2 = plane[i].y;
        plane[i].x = x_temp * cos(theta_plane_z) - y_temp2 * sin(theta_plane_z);
        plane[i].y = x_temp * sin(theta_plane_z) + y_temp2 * cos(theta_plane_z);
    }

    free(plane);
}
