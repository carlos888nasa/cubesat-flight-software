#ifndef MATH_UTILS_H
#define MATH_UTILS_H

#include <stdint.h>
#include <math.h>

typedef struct  {
    float x;
    float y;
    float z;
}Vec3;

Vec3 vec3_add(Vec3 a, Vec3 b);
Vec3 vec3_sub(Vec3 a, Vec3 b);
Vec3 vec3_scale(Vec3 v, float scalar);
float vec3_length(Vec3 v);
Vec3 vec3_normalize(Vec3 v);
float vec3_dot(Vec3 a, Vec3 b);
Vec3 vec3_cross(Vec3 a, Vec3 b);

#endif
