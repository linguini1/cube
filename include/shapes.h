#include <SDL.h>
#include "vector.h"

// Constants
#define PI 3.141592653f

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
void colour_transition(RGB *colour, float angle);
void reset_angle(float *angle);

// Cube functions
Cube *make_cube();
void free_cube(Cube *cube);
void translate_cube(Cube *cube, Matrix const *matrix);
Cube *rotate_cube(Cube const *cube, float angle, int axis);
void project_cube(Cube *cube, float distance);
void draw_cube(SDL_Renderer *renderer, Cube const *cube);
void print_cube(Cube const *cube);