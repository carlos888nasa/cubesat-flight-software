#include <stdio.h>
#include "attitude.h"
#include "utils/math_utils.h"

#define ATTITUDE_UPDATE_INTERVAL_s 0.1f

static Attitude current_attitude;

void attitude_init() {
    current_attitude.position = (Vec3){0.0f, 0.0f, 0.0f};
    current_attitude.velocity = (Vec3){5.0f, 0.0f, 0.0f};
    current_attitude.orientation = (Vec3){0.0f, 0.0f, 0.0f}; 
    current_attitude.angular_velocity = (Vec3){0.0f, 0.0f, 0.5f};
}

void attitude_update() {

    float Kp = 0.1f;

    // Simulate attitude changes based on velocity
    Vec3 displacement = vec3_scale(current_attitude.velocity, ATTITUDE_UPDATE_INTERVAL_s); 
    current_attitude.position = vec3_add(current_attitude.position, displacement);

    // P controller for rotation
    Vec3 delta_velocity = vec3_scale(current_attitude.angular_velocity, -Kp);
    delta_velocity = vec3_scale(delta_velocity, ATTITUDE_UPDATE_INTERVAL_s);
    current_attitude.angular_velocity = vec3_add(current_attitude.angular_velocity, delta_velocity);
    current_attitude.angular_velocity = vec3_scale(current_attitude.angular_velocity, ATTITUDE_UPDATE_INTERVAL_s);
    current_attitude.orientation = vec3_add(current_attitude.orientation, current_attitude.angular_velocity);
}  

Attitude attitude_get() {
    return current_attitude;
}