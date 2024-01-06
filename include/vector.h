#ifndef _VECTOR_H_
#define _VECTOR_H_

// Vector functionality

// Types
typedef struct vector3d {
    double x;
    double y;
    double z;
    double w;
} Vec3D;

typedef struct matrix {
    double cells[4][4];
} Matrix;

// Vectors
Vec3D *make_vector(double x, double y, double z);
Vec3D *rotate_vector(Vec3D const *vector, double angle, int axis);
void print_vector(Vec3D const *vector);

// Matrices
Matrix *make_matrix(void);
void zero_populate(Matrix *matrix);
Matrix *make_projection_matrix(double cam_distance, double z);
Matrix *make_translation_matrix(Vec3D const *translation, double scale);
void matrix_multiplication(Vec3D *vector, Matrix const *matrix);
void print_matrix(Matrix const *matrix);

#endif // _VECTOR_H_
