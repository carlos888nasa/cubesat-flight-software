#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdint.h>
#include <stdbool.h>

#define SYSTEM_CYCLE_MS 100

void scheduler_init();
void scheduler_run();
bool schedulter_wait_next_cycle();
uint32_t scheduler_get_uptime_ms();

#endif