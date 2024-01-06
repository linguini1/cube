// Functions for building the cube shapes
#include "../include/shapes.h"
#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define PI_TOLERANCE 0.005

// Helpers
int *to_binary(int num) {
    assert((0 <= num) && (num < 8)); // Only works for 3-bit

    // Declare the binary representation array
    int *binary = malloc(sizeof(int) * 3);
    assert(binary != NULL);

    // Convert decimal to binary
    for (int i = 0; i < 3; i++) {
        int bin = num >> i;
        if (bin & 1) {
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

void colour_transition(RGB *colour, double angle) {

    // All colours are 1/3 out of phase
    double r = sin(angle);
    double g = sin(angle + 2.0 * PI / 3.0);
    double b = sin(angle + +4.0 * PI / 3.0);

    // Changing RGB struct
    colour->r = round(fabs(255 * r));
    colour->g = round(fabs(255 * g));
    colour->b = round(fabs(255 * b));
}

void reset_angle(double *angle) {

    bool positive_pi = (2.0 * PI - PI_TOLERANCE < *angle) && (*angle > 2.0 * PI + PI_TOLERANCE);
    bool negative_pi = (-2.0 * PI + PI_TOLERANCE > *angle) && (*angle < -2.0 * PI - PI_TOLERANCE);

    if (positive_pi || negative_pi) {
        *angle = 0.0;
    }
}

// Cube
Cube *make_cube(void) {

    Cube *cube = malloc(sizeof(Cube));

    for (int i = 0; i < 8; i++) {

        int *bin = to_binary(i);

        // 0.5 so that cube is one unit side lengths centered at origin
        // Base coordinates is -, +, -
        // For each bit in binary representation of index, 1 flips the sign, 0 sign stays the same
        // -2b + 1 = 1 when b is 0, -1 when b is 1
        cube->vertices[i] = *make_vector((double)(bin[0] * -2 + 1) * 0.5, (double)(bin[1] * -2 + 1) * 0.5,
                                         (double)(bin[2] * -2 + 1) * 0.5);
    }

    return cube;
}

void free_cube(Cube *cube) {

    // Free all vectors
    for (int i = 0; i < 8; i++) {
        free(&(cube->vertices[i]));
    }
    free(cube);
}

void translate_cube(Cube *cube, Matrix const *matrix) {

    for (int i = 0; i < 8; i++) {
        Vec3D *vertex = &(cube->vertices[i]);
        matrix_multiplication(vertex, matrix);
    }
}

Cube *rotate_cube(Cube const *cube, double angle, int axis) {

    // Copy cube with rotation applied
    Cube *new_cube = malloc(sizeof(Cube));
    assert(new_cube != NULL);

    for (int i = 0; i < 8; i++) {
        Vec3D reference_vec = cube->vertices[i];
        new_cube->vertices[i] = *rotate_vector(&reference_vec, angle, axis);
    }

    return new_cube;
}

void project_cube(Cube *cube, double distance) {

    for (int i = 0; i < 8; i++) {

        // Unpack vertices
        Vec3D *vertex = &(cube->vertices[i]);

        // Create matrix & project each vector
        Matrix *proj = make_projection_matrix(distance, vertex->z);
        matrix_multiplication(vertex, proj);
        free(proj); // Free each projection matrix
    }
}

void draw_cube(SDL_Renderer *renderer, Cube const *cube) {

    for (int i = 0; i < 4; i++) {

        int j = 2 * i + ((i - 1) * (i - 2)) / 2; // Map i to the correct vertex number, j

        // Convert index to binary
        int *bin = to_binary(j);
        Vec3D home = cube->vertices[j];

        // Draw a line between each vertex and its three neighbours
        for (int k = 0; k < 3; k++) {

            bin[k] = !bin[k];            // Flip bit
            int index = to_decimal(bin); // Get neighbour index

            Vec3D next = cube->vertices[index];
            SDL_RenderDrawLineF(renderer, home.x, home.y, next.x, next.y);

            bin[k] = !bin[k]; // Flip bit back
        }
    }
}

void print_cube(Cube const *cube) {

    for (int i = 0; i < 8; i++) {
        printf("Vertex %d: ", i);
        print_vector(&(cube->vertices[i]));
    }
}
