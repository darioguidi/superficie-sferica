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

void DrawSurface(SDL_Renderer *renderer, int step, float radius, float phi_sphere, float theta_sphere)
{
    int number_points = step * step;
    Point *surface = malloc(number_points * sizeof(Point));
    if (!surface) return; // sempre bene controllare

    Point center = {0.0f, 0.0f, 300.0f};

    int i = 0;
    for (int t = 0; t < step; t++) {
        float theta = ((float)t / (step - 1)) * PI + theta_sphere;

        for (int p = 0; p < step; p++) {
            float phi = ((float)p / (step - 1)) * 2 * PI + phi_sphere;

            surface[i].x = center.x + radius * sinf(theta) * cosf(phi);
            surface[i].y = center.y + radius * sinf(theta) * sinf(phi);
            surface[i].z = center.z + radius * cosf(theta);

            DrawPoint(renderer, &surface[i]);
            i++;
        }
    }
    free(surface);
}


void DrawPlane(SDL_Renderer *renderer,int length, float theta_plane_x, float theta_plane_y, float theta_plane_z)
{
    Point *plane = malloc((4 * length) * sizeof(Point));
    float offset = length / 2.0f;

    // Centro del piano nello spazio 3D (centrato e davanti alla camera)
    Point center = {0.0f, 0.0f, 300.0f};
    int index = 0;

    // Bordi del piano - calcolo dei punti
    for (int j = 0; j < length; j++) {
        plane[index].x = -offset + j;
        plane[index].y = 1;
        plane[index].z = offset;
        index++;
    }

    for (int j = 0; j < length; j++) {
        plane[index].x = -offset;
        plane[index].y = 1;
        plane[index].z = -offset + j;
        index++;
    }

    for (int j = 0; j < length; j++) {
        plane[index].x = -offset + j;
        plane[index].y = 1;
        plane[index].z = -offset;
        index++;
    }

    for (int j = 0; j < length; j++) {
        plane[index].x = offset;
        plane[index].y = 1;
        plane[index].z = -offset + j;
        index++;
    }

    // Applicazione trasformazioni (traslazione e rotazione) PRIMA del disegno
    for (int i = 0; i < 4 * length; i++) {
        // Traslazione
        plane[i].x += center.x;
        plane[i].y += center.y;
        plane[i].z += center.z;
        
        float x_temp, y_temp, z_temp;

        // Rotazione asse X
        y_temp = plane[i].y;
        z_temp = plane[i].z;
        plane[i].y = y_temp * cos(theta_plane_x) - z_temp * sin(theta_plane_x);
        plane[i].z = y_temp * sin(theta_plane_x) + z_temp * cos(theta_plane_x);

        // Rotazione asse Z
        x_temp = plane[i].x;
        y_temp = plane[i].y;
        plane[i].x = x_temp * cos(theta_plane_z) - y_temp * sin(theta_plane_z);
        plane[i].y = x_temp * sin(theta_plane_z) + y_temp * cos(theta_plane_z);

        // Rotazione asse Y
        x_temp = plane[i].x;
        z_temp = plane[i].z;
        plane[i].x = x_temp * cos(theta_plane_y) + z_temp * sin(theta_plane_y);
        plane[i].z = -x_temp * sin(theta_plane_y) + z_temp * cos(theta_plane_y);
    }

    // Disegno dopo aver trasformato i punti
    for (int i = 0; i < 4 * length; i++) {
        DrawPoint(renderer, &plane[i]);
    }

    free(plane);
}

/*
void collision(Point *plane, Point *sphere)
{
    int number_points_sphere = sizeof(sphere)/sizeof(Point);

    for(int i=0; i<number_points_sphere;i++){

    }
}*/

