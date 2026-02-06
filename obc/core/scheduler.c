#define _POSIX_C_SOURCE 199309L

#include <stdio.h>
#include <time.h>
#include <stdint.h>
#include <stdbool.h>
#include "core/scheduler.h"

#define life_cycle_ms 100

static struct timespec start_time;
static struct timespec start_time_cycle;
static struct timespec end_time_cycle;
static struct timespec elapsed_time_ms;
static struct timespec current_time;

void scheduler_init() {
    
    clock_gettime(CLOCK_MONOTONIC, &start_time);

}

void scheduler_start_cycle() {

    clock_gettime(CLOCK_MONOTONIC, &start_time_cycle);

}

bool scheduler_wait_next_cycle() {

    clock_gettime(CLOCK_MONOTONIC, &end_time_cycle);

    long long int time = (end_time_cycle.tv_nsec - start_time_cycle.tv_nsec) + (end_time_cycle.tv_sec - start_time_cycle.tv_sec) * 1000000000;
    elapsed_time_ms.tv_nsec = (life_cycle_ms * 1000000) - time;

    if (elapsed_time_ms.tv_nsec < 0){

        fprintf(stderr, "Warning: Cycle time exceeded! Elapsed time: %ld ms\n", -elapsed_time_ms.tv_nsec / 1000000);
        elapsed_time_ms.tv_nsec = 0; // No need to wait, we're already late
        return false; // Indicate that the cycle was not completed in time

    }else{

        nanosleep(&elapsed_time_ms, NULL);
        return true; // Indicate that the cycle was completed successfully
    }

}

uint32_t scheduler_get_uptime_ms() {

    clock_gettime(CLOCK_MONOTONIC, &current_time);

    uint32_t uptime_ms = (current_time.tv_sec - start_time.tv_sec) * 1000 + (current_time.tv_nsec - start_time.tv_nsec) / 1000000;

    return uptime_ms;


}
