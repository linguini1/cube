// Vector functionality
#include "../include/vector.h"
#include <assert.h>
#include <malloc.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// Vectors
Vec3D *make_vector(double x, double y, double z) {

    // Allocate on heap
    Vec3D *v = malloc(sizeof(Vec3D));
    assert(v != NULL);

    // Populate
    v->x = x;
    v->y = y;
    v->z = z;
    v->w = 1.0;

    return v;
}

Vec3D *rotate_vector(Vec3D const *vector, double angle, int axis) {

    assert((0 < axis) & (axis < 4)); // 1-3 are valid (x, y, z) respectively

    // Create new vector
    Vec3D *new_vec = make_vector(0.0, 0.0, 0.0);

    // X axis
    if (axis == 1) {
        new_vec->x = vector->x;
        new_vec->y = vector->y * cos(angle) - vector->z * sin(angle);
        new_vec->z = vector->y * sin(angle) + vector->z * cos(angle);
    }

    // Y axis
    else if (axis == 2) {
        new_vec->x = vector->x * cos(angle) + vector->z * sin(angle);
        new_vec->y = vector->y;
        new_vec->z = vector->x * -sin(angle) + vector->z * cos(angle);
    }

    // Z axis
    else {
        new_vec->x = vector->x * cos(angle) - vector->y * sin(angle);
        new_vec->y = vector->x * sin(angle) + vector->y * cos(angle);
        new_vec->z = vector->z;
    }

    return new_vec;
}

void print_vector(Vec3D const *vector) { printf("(%f, %f, %f, %f)\n", vector->x, vector->y, vector->z, vector->w); }

// Matrices
Matrix *make_matrix(void) {
    Matrix *matrix = malloc(sizeof(Matrix));
    assert(matrix != NULL);
    return matrix;
}

void zero_populate(Matrix *matrix) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            matrix->cells[i][j] = 0.0;
        }
    }
}

Matrix *make_translation_matrix(Vec3D const *translation, double scale) {

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

Matrix *make_projection_matrix(double cam_distance, double z) {

    Matrix *proj_matrix = make_matrix();

    // Populate with 0s
    zero_populate(proj_matrix);

    // Projection parameters
    double normalized_z = 1.0 / (cam_distance - z);
    proj_matrix->cells[0][0] = normalized_z;
    proj_matrix->cells[1][1] = normalized_z;
    proj_matrix->cells[3][3] = 1.0;

    return proj_matrix;
}

void matrix_multiplication(Vec3D *vector, Matrix const *matrix) {

    // Unpack vector into array for looping
    double *vector_fields[4] = {&(vector->x), &(vector->y), &(vector->z), &(vector->w)};
    double sums[4] = {0.0};

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
        for (int j = 0; j < 4; j++) {
            printf("%f, ", matrix->cells[i][j]);
        }
        printf("\n");
    }
}
