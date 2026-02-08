#include <stdio.h>
#include "power.h"

static float battery_voltage;

void power_init() {
    printf("[POWER] Power system initialized.\n");
    battery_voltage = 5.0; 
}

void power_update() {
    battery_voltage -= 0.01; 
}

float power_get_battery_voltage() {
    return battery_voltage;
}