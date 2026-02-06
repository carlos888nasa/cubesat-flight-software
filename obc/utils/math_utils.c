#include <stdio.h>
#include <math.h> 
#include "math_utils.h"

vec3_add(Vec3 a, Vec3 b){
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