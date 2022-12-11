// Vector functionality

// Types
typedef struct vector3d {
    float x;
    float y;
    float z;
    float w;
} Vec3D;

typedef struct matrix {
    float cells[4][4];
} Matrix;

// Vectors
Vec3D *make_vector(float x, float y, float z);
Vec3D *rotate_vector(Vec3D const *vector, float angle, int axis);
void print_vector(Vec3D const *vector);

// Matrices
Matrix *make_matrix();
Matrix *make_projection_matrix(float fov, float aspect, float z_near, float z_far);
Matrix *make_translation_matrix(Vec3D const *translation, float scale);
void *matrix_multiplication(Vec3D *vector, Matrix const *matrix);
void print_matrix(Matrix const *matrix);