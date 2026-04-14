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
    return sqrtf(v.x*v.x + v.y*v.y + v.z*v.z);
}

Vec3 vec3_normalize(Vec3 v){
    Vec3 result; 
    float magnitud = vec3_length(v);
    result.x = v.x/magnitud;
    result.y = v.y/magnitud;
    result.z = v.z/magnitud; 
    return result;
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

Quaternion quat_identity(){
    return (Quaternion){1.0f, 0.0f, 0.0f, 0.0f};
}

float quat_length(Quaternion q){
    return sqrtf(q.w * q.w + q.x * q.x + q.y * q.y + q.z * q.z);
}

Quaternion quat_normalize(Quaternion q){
    float len = quat_length(q);
    if (len > 0.0f) {
        return (Quaternion){q.w / len, q.x / len, q.y / len, q.z / len};
    }
    return quat_identity();
}

Quaternion quat_conjugate(Quaternion q){
    return (Quaternion){q.w, -q.x, -q.y, -q.z};
}

Quaternion quat_multiply(Quaternion q1, Quaternion q2){
    return (Quaternion){
        q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z,
        q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y,
        q1.w * q2.y - q1.x * q2.z + q1.y * q2.w + q1.z * q2.x,
        q1.w * q2.z + q1.x * q2.y - q1.y * q2.x + q1.z * q2.w
    };
}

Quaternion quat_from_axis_angle(float axis_x, float axis_y, float axis_z, float angle_rad){
    float half_angle = angle_rad/2.0f;
    float sin_half = sinf(half_angle);
    return (Quaternion){
        cosf(half_angle),
        axis_x*sin_half,
        axis_y*sin_half,
        axis_z*sin_half
    };
}