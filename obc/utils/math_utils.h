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

typedef struct  {
    float w;
    float x;
    float y;
    float z;
}Quaternion;

Quaternion quat_identity();
float quat_length(Quaternion q);
Quaternion quat_normalize(Quaternion q);
Quaternion quat_conjugate(Quaternion q);
Quaternion quat_multiply(Quaternion a, Quaternion b);
Quaternion quat_from_axis_angle(float axis_x, float axis_y, float axis_z, float angle_rad);

#endif
