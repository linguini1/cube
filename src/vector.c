// Vector functionality
#include "vector.h"
#include <malloc.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

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
    Vec3D *new_vec = make_vector(0.0f, 0.0f, 0.0f);

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
    printf("(%f, %f, %f, %f)\n", vector->x, vector->y, vector->z, vector->w);
}

// Matrices
Matrix *make_matrix() {
    Matrix *matrix = malloc(sizeof(Matrix));
    assert(matrix != NULL);
    return matrix;
}

void zero_populate(Matrix *matrix) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            matrix -> cells[i][j] = 0.0f;
        }
    }
}

Matrix *make_translation_matrix(Vec3D const *translation, float scale) {

    Matrix *trans_matrix = make_matrix();
    zero_populate(trans_matrix);

    // Populate diagonals with 1s (multiplied by the scale), rest with 0s
    trans_matrix->cells[0][0] = scale;
    trans_matrix->cells[1][1] = scale;
    trans_matrix->cells[2][2] = scale;
    trans_matrix->cells[3][3] = scale;

    // Include translation values to be added
    trans_matrix->cells[0][3] = translation->x;
    trans_matrix->cells[1][3] = translation->y;
    trans_matrix->cells[2][3] = translation->z;

    return trans_matrix;
}

Matrix *make_projection_matrix(float cam_distance, float z) {

    Matrix *proj_matrix = make_matrix();

    // Populate with 0s
    zero_populate(proj_matrix);

    // Projection parameters
    float normalized_z = 1.0f / (cam_distance - z);
    proj_matrix->cells[0][0] = normalized_z;
    proj_matrix->cells[1][1] = normalized_z;
    proj_matrix->cells[3][3] = 1.0f;

    return proj_matrix;
}

void *matrix_multiplication(Vec3D *vector, Matrix const *matrix) {

    // Unpack vector into array for looping
    float *vector_fields[4] = {
        &(vector->x),
        &(vector->y),
        &(vector->z),
        &(vector->w)
    };
    float sums[4] = {0.0f};

    // Multiply
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            sums[i] += matrix->cells[i][j] * (*vector_fields[j]);
        }
    }

    // Populate vector with new vector
    for (int i = 0; i < 4; i++) {
        *vector_fields[i] = sums[i];
    }
}

void print_matrix(Matrix const *matrix) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++){
            printf("%f, ", matrix->cells[i][j]);
        }
        printf("\n");
    }
}