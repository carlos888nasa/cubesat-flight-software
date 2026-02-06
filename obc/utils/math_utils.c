#include <stdio.h>
#include <math.h> 
#include "math_utils.h"

Vec3 vec3_add(Vec3 a, Vec3 b){
    Vec3 result; 
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    result.z = a.z + b.z;
    return result;
}

Vec3 vec3_sub(Vec3 a, Vec3 b){
    Vec3 result; 
    result.x = a.x - b.x;
    result.y = a.y - b.y;
    result.z = a.z - b.z;
    return result; 
}

Vec3 vec3_scale(Vec3 v, float scalar){
    Vec3 result; 
    result.x = v.x * scalar;
    result.y = v.y * scalar;
    result.z = v.z * scalar;
    return result; 
}

float vec3_length(Vec3 v){
    return sqrtf(powf(v.x, 2) + powf(v.y, 2) + powf(v.z, 2));
}

Vec3 vec3_normalize(Vec3 v){
    Vec3 result; 
    float magnitud = sqrtf(powf(v.x, 2) + powf(v.y, 2) + powf(v.z, 2));
    result.x = v.x/magnitud;
    result.y = v.y/magnitud;
    result.z = v.z/magnitud; 
}

float vec3_dot(Vec3 a, Vec3 b){
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vec3 vec3_cross(Vec3 a, Vec3 b){
    Vec3 result; 
    result.x = a.y * b.z - a.z * b.y;
    result.y = a.z * b.x - a.x * b.z;
    result.z = a.x * b.y - a.y * b.x;
    return result; 
}