// Vector functionality
#include "vector.h"
#include <malloc.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

// Vectors
Vec3D *make_vector(float x, float y, float z) {

    // Allocate on heap
    Vec3D *v = malloc(sizeof(Vec3D));
    assert(v != NULL);

    // Populate
    v->x = x;
    v->y = y;
    v->z = z;
    v->w = 1.0f;

    return v;

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

void print_vector(Vec3D const *vector) {
    printf("(%f, %f, %f, %f)", vector->x, vector->y, vector->z, vector->w);
}

void *translate_vector(Vec3D const *vector, Vec3D const *translation) {
    1 + 1;
}

// Matrices
