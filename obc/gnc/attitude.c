#include <stdio.h>
#include "attitude.h"
#include "utils/math_utils.h"

#define ATTITUDE_UPDATE_INTERVAL_s 0.1f

static Attitude current_attitude;

void attitude_init() {
    current_attitude.position = (Vec3){0.0f, 0.0f, 0.0f};
    current_attitude.velocity = (Vec3){5.0f, 0.0f, 0.0f};
    current_attitude.orientation = (Vec3){0.0f, 0.0f, 0.0f}; 
}

void attitude_update() {
    // Simulate attitude changes based on velocity
    Vec3 displacement = vec3_scale(current_attitude.velocity, ATTITUDE_UPDATE_INTERVAL_s); 
    current_attitude.position = vec3_add(current_attitude.position, displacement);
    current_attitude.orientation.y += 0.01f; // Simulate a slow yaw rotation
}  

Attitude attitude_get() {
    return current_attitude;
}