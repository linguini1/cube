#ifndef _SHAPES_H_
#define _SHAPES_H_

#include "vector.h"
#include <SDL2/SDL.h>

// Constants
#define PI 3.141592653

// Types
typedef struct cube {
    Vec3D vertices[8];
} Cube;

typedef struct rgb {
    unsigned int r;
    unsigned int g;
    unsigned int b;
} RGB;

// Helper functions
int *to_binary(int num);
int to_decimal(int const *binary);
void colour_transition(RGB *colour, double angle);
void reset_angle(double *angle);

// Cube functions
Cube *make_cube(void);
void free_cube(Cube *cube);
void translate_cube(Cube *cube, Matrix const *matrix);
Cube *rotate_cube(Cube const *cube, double angle, int axis);
void project_cube(Cube *cube, double distance);
void draw_cube(SDL_Renderer *renderer, Cube const *cube);
void print_cube(Cube const *cube);

#endif // _SHAPES_H_
