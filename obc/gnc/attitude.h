#ifndef ATTITUDE_H
#define ATTITUDE_H

#include <stdio.h>
#include "utils/math_utils.h"

typedef struct {
    Vec3 position;
    Vec3 velocity;
    Vec3 orientation; // Euler angles: roll, pitch, yaw
    Vec3 angular_velocity; // Roll, pitch, yaw rates
} Attitude;

void attitude_init();
void attitude_update();
Attitude attitude_get();

#endif