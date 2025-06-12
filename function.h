#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SCREEN_WIDTH 700
#define SCREEN_HEIGHT 700
#define SCREEN_OFFSET_X SCREEN_WIDTH/2
#define SCREEN_OFFSET_Y SCREEN_HEIGHT/2
#define SIZE_POINT 2

#define SPHERE_C_X = SCREEN_OFFSET_X
#define SPHERE_C_Y = SCREEN_OFFSET_Y
#define RADIUS_C = 20
#define PI 3.14f

extern float phi;
extern float theta;

extern float phi_plane_x;
extern float theta_plane_x;

extern float phi_plane_y;
extern float theta_plane_y;

extern float phi_plane_z;
extern float theta_plane_z;

typedef struct {
    float x;
    float y;
    float z;
} Point;

void DrawPoint(SDL_Renderer *renderer, Point *point);
void DrawSurface(SDL_Renderer *renderer, int number_points, float radius);
void DrawPlane(SDL_Renderer *renderer, int number_points);