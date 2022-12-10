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

// Functions
Vec3D *make_vector(float x, float y, float z);

Vec3D *rotate_vector(Vec3D const *vector, float angle, int axis);

void *translate_vector(Vec3D const *vector, Vec3D const *translation);

void print_vector(Vec3D const *vector);