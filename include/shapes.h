#include <SDL.h>

// Constants
#define PI 3.141592653f

// Types
typedef struct vector3d {
    float x;
    float y;
    float z;
} Vec3D;

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

void scale_cube(Cube *cube, float scalar);
void translate_cube(Cube *cube, Vec3D *origin);
Cube *rotate_cube(Cube const *cube, float angle, int axis);

Vec3D *rotate_vector(Vec3D const *vector, float angle, int axis);

void draw_cube(SDL_Renderer *renderer, Cube const *cube);
void colour_transition(RGB *colour, float angle);