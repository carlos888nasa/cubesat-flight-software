#include <stdio.h>
#include "attitude.h"
#include "utils/math_utils.h"

#define ATTITUDE_UPDATE_INTERVAL_s 0.1f

static Attitude current_attitude;


void attitude_init() {
    current_attitude.position = (Vec3){0.0f, 0.0f, 0.0f};
    current_attitude.velocity = (Vec3){5.0f, 0.0f, 0.0f};
    current_attitude.orientation = quat_identity(); 
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

    float speed_rads = vec3_length(current_attitude.angular_velocity);
    
    if(speed_rads > 0.00001f){
        float angle_turned = speed_rads*ATTITUDE_UPDATE_INTERVAL_s;
        Vec3 axis = vec3_normalize(current_attitude.angular_velocity);
        Quaternion delta_q = quat_from_axis_angle(axis.x, axis.y, axis.z, angle_turned);
        current_attitude.orientation = quat_multiply(current_attitude.orientation, delta_q);
        current_attitude.orientation = quat_normalize(current_attitude.orientation);
    }
}  

Attitude attitude_get() {
    return current_attitude;
}