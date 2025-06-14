#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800
#define SCREEN_OFFSET_X SCREEN_WIDTH/2
#define SCREEN_OFFSET_Y SCREEN_HEIGHT/2
#define SIZE_POINT 2

#define SPHERE_C_X = SCREEN_OFFSET_X
#define SPHERE_C_Y = SCREEN_OFFSET_Y
#define RADIUS_C = 20
#define PI 3.14f

extern float phi_sphere;
extern float theta_sphere;

extern float theta_plane_x;
extern float theta_plane_y;
extern float theta_plane_z;

typedef struct {
    float x;
    float y;
    float z;
} Point;

void DrawPoint(SDL_Renderer *renderer, Point *point);
void DrawPointPlane(SDL_Renderer *renderer, Point *point);
void DrawSurface(SDL_Renderer *renderer, Point *surface, int step, float radius, float phi_sphere, float theta_sphere);
void DrawPlane(SDL_Renderer *renderer,Point *plane, int length, float theta_plane_x, float theta_plane_y, float theta_plane_z);