// Functions for building the cube shapes
#include <shapes.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

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

Cube *make_cube(float side_length) {

    Cube *cube = malloc(sizeof(Cube));
    cube->vertices = malloc(sizeof(Vec3D) * 8);

    assert(cube->vertices != NULL);

    for (int i = 0; i < 8; i++) {

        int *bin = to_binary(i);

        cube->vertices[i] = (Vec3D) {(float)bin[0] * side_length,
                                     (float)bin[1] * side_length,
                                     (float)bin[2] * side_length};
    }

    return cube;
}

void scale_cube(Cube *cube, float scalar) {
    for (int i = 0; i < 8; i++){
        cube->vertices[i].x *= scalar;
        cube->vertices[i].y *= scalar;
        cube->vertices[i].z *= scalar;
    }
}

void translate_cube(Cube *cube, Vec3D *origin) {
    for (int i = 0; i < 8; i++){
        cube->vertices[i].x += origin->x;
        cube->vertices[i].y += origin->y;
        cube->vertices[i].z += origin->z;
    }
}

Vec3D *rotate_vector(Vec3D const *vector, float angle, int axis){

    assert(0 < axis & axis < 4); // 1-3 are valid (x, y, z) respectively

    // Create new vector
    Vec3D *new_vec = malloc(sizeof(Vec3D));
    assert(new_vec != NULL);

    // X axis
    if (axis == 1) {
        new_vec->x = vector->x;
        new_vec->y = vector->y * cosf(angle) - vector->z * sinf(angle);
        new_vec->z = vector->y * sinf(angle) + vector->z * cosf(angle);
    }

    // Y axis
    else if (axis == 2) {
        new_vec->x = vector->x * cosf(angle) + vector->z * sinf(angle);
        new_vec->y = vector->y;
        new_vec->z = vector->x * -sinf(angle) + vector->z * cosf(angle);
    }

    // Z axis
    else {
        new_vec->x = vector->x * cosf(angle) - vector->y * sinf(angle);
        new_vec->y = vector->x * sinf(angle) + vector->y * cosf(angle);
        new_vec->z = vector->z;
    }

    return new_vec;
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

    for (int i = 0; i < 8; i++) {
        // Convert index to binary
        int *bin = to_binary(i);
        Vec3D home = cube->vertices[i];

        // Draw a line between each vertex and its three neighbours
        for (int j = 0; j < 3; j++) {
            bin[j] = !bin[j]; // Flip bit
            int index = to_decimal(bin);

            Vec3D next = cube->vertices[index];
            SDL_RenderDrawLineF(
                    renderer,
                    home.x, home.y,
                    next.x, next.y
            );

            bin[j] = !bin[j]; // Flip bit back
        }
    }
}