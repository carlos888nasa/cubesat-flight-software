#include <stdio.h>
#include <stdint.h>
#include "core/scheduler.h"
#include "core/power.h"
#include "gnc/attitude.h"
#include "comms/commands.h"

int main() {

    float battery_voltage;

    scheduler_init();
    attitude_init();
    power_init();
    printf("[MAIN] Started sistem \n");

    uint32_t cycle_counter = 0;

    while (1) {

        scheduler_start_cycle();
        power_update();

        battery_voltage = power_get_battery_voltage();

        if (battery_voltage <= 0) {

            printf("[CRITICAL] BATTERY DEPLETED - SYSTEM SHUTDOWN IMMINENT\n");
            return 1;

        }else if (battery_voltage < 3.5) {

            printf("[ALERT] LOW BATTERY: %.2fV - SHUTTING DOWN NON-ESSENTIAL SYSTEMS\n", battery_voltage);

        }else {
            attitude_update();

            if (cycle_counter == 50) {
                printf("[EARTH] Sending PING command...\n");
                comms_process_command(CMD_PING);
            }


            if (cycle_counter == 100) {
                printf("[EARTH] Sending REBOOT command...\n");
                comms_process_command(CMD_REBOOT);
            }

        }

        if (cycle_counter % 10 == 0) {

                Attitude data = attitude_get();

                uint32_t uptime = scheduler_get_uptime_ms();
                printf("[MAIN] Tick: %d | Uptime: %u ms | Pos X: %.2f m | Velocity rottation Z: %.2f rad/s\n", cycle_counter, uptime, data.position.x, data.angular_velocity.z);
            }
            
            cycle_counter++;
    
            bool cycle_ok = scheduler_wait_next_cycle();

            if (!cycle_ok) {
                printf("[ALERT] OVERRUN! The %d cycle took longer than 100ms.\n", cycle_counter);
            }

    }
            
    return 0;
}