#include <stdio.h>
#include <stdint.h>
#include "core/scheduler.h"
#include "gnc/attitude.h"

int main() {
    scheduler_init();
    attitude_init();
    printf("[MAIN] Started sistem \n");

    uint32_t cycle_counter = 0;

    while (1) {

        scheduler_start_cycle();
        attitude_update();

        if (cycle_counter % 10 == 0) {

            Attitude data = attitude_get();

            uint32_t uptime = scheduler_get_uptime_ms();
            printf("[MAIN] Tick: %d | Uptime: %u ms | Pos X: %.2f m\n", cycle_counter, uptime, data.position.x);
        }
        
        cycle_counter++;
  
        bool cycle_ok = scheduler_wait_next_cycle();

        if (!cycle_ok) {
            printf("[ALERTA] !OVERRUN! El ciclo %d tardó más de 100ms\n", cycle_counter);
        }
    }

    return 0;
}