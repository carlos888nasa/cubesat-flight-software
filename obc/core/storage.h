#ifndef STORAGE_H
#define STORAGE_H

#include <stdint.h>
#include <stdbool.h>
#include "utils/math_utils.h"

bool storage_init();
void storage_log_data(uint32_t time_ms, float voltage, Vec3 position, Vec3 velocity);
void storage_close();

#endif