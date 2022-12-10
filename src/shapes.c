// Functions for building the cube shapes
#include "shapes.h"
#include <assert.h>
#include <stdlib.h>
#include <math.h>

// Helpers
int *to_binary(int num) {
    assert(0 <= num & num < 8); // Only works for 3-bit

    // Declare the binary representation array
    int *binary = malloc(sizeof(int) * 3);
    assert(binary != NULL);

    // Convert decimal to binary
    for (int i = 0; i < 3; i++){
        int bin = num >> i;
        if (bin & 1){
            binary[i] = 1;
        } else {
            binary[i] = 0;
        }
    }

    return binary;
}

int to_decimal(int const *binary) {
    int num = 0;
    for (int i = 0; i < 3; i++) {
        num += (int)(binary[i] * pow(2, i));
    }

    return num;
}

void colour_transition(RGB *colour, float angle) {

    // All colours are 1/3 out of phase
    float r = sinf(angle);
    float g = sinf(angle + 2.0f * PI / 3.0f);
    float b = sinf(angle + + 4.0f * PI / 3.0f);

    // Changing RGB struct
    colour->r = (int) fabs((255 * r));
    colour->g = (int) fabs((255 * g));
    colour->b = (int) fabs((255 * b));

}

// Cube
Cube *make_cube(float side_length) {

    Cube *cube = malloc(sizeof(Cube));
    cube->vertices = malloc(sizeof(Vec3D) * 8);

    assert(cube->vertices != NULL);

    for (int i = 0; i < 8; i++) {

        int *bin = to_binary(i);

        // 0.5 so that cube is one unit side lengths centered at origin
        // Base coordinates is -, +, -
        // For each bit in binary representation of index, 1 flips the sign, 0 sign stays the same
        // -2b + 1 = 1 when b is 0, -1 when b is 1
        cube->vertices[i] = *make_vector(
                (float)(bin[0] * -2 + 1) * -0.5f * side_length,
                (float)(bin[1] * -2 + 1) * 0.5f * side_length,
                (float)(bin[2] * -2 + 1) * -0.5f * side_length
        );
    }

    return cube;
}

void translate_cube(Cube *cube, Vec3D *origin) {
    for (int i = 0; i < 8; i++){
        cube->vertices[i].x += origin->x;
        cube->vertices[i].y += origin->y;
        cube->vertices[i].z += origin->z;
    }
}

Cube *rotate_cube(Cube const *cube, float angle, int axis) {

    // Copy cube with rotation applied
    Cube *new_cube = malloc(sizeof(Cube));
    assert(new_cube != NULL);
    new_cube->vertices = malloc(sizeof(Vec3D) * 8);
    assert(new_cube->vertices != NULL);

    for (int i = 0; i < 8; i++) {
        Vec3D reference_vec = cube->vertices[i];
        new_cube->vertices[i] = *rotate_vector(&reference_vec, angle, axis);
    }

    return new_cube;
}

void draw_cube(SDL_Renderer *renderer, Cube const *cube){

    for (int i = 0; i < 4; i++) {

        int j = 2 * i + ((i - 1) * (i - 2)) / 2; // Map i to the correct vertex number, j

        // Convert index to binary
        int *bin = to_binary(j);
        Vec3D home = cube->vertices[j];

        // Draw a line between each vertex and its three neighbours
        for (int k = 0; k < 3; k++) {

            bin[k] = !bin[k]; // Flip bit
            int index = to_decimal(bin); // Get neighbour index

            Vec3D next = cube->vertices[index];
            SDL_RenderDrawLineF(
                    renderer,
                    home.x, home.y,
                    next.x, next.y
            );

            bin[k] = !bin[k]; // Flip bit back
        }
    }
}