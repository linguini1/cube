#include <SDL.h>
#include "vector.h"

// Constants
#define PI 3.141592653f

// Types
typedef struct cube {
    Vec3D *vertices;
} Cube;

typedef struct rgb {
    unsigned int r;
    unsigned int g;
    unsigned int b;
} RGB;

// Functions
int *to_binary(int num);
int to_decimal(int const *binary);

Cube *make_cube(float side_length);

void translate_cube(Cube *cube, Vec3D *origin);
Cube *rotate_cube(Cube const *cube, float angle, int axis);

void draw_cube(SDL_Renderer *renderer, Cube const *cube);
void colour_transition(RGB *colour, float angle);