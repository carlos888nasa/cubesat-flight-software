#include <stdio.h>
#include "commands.h"
#include "core/scheduler.h"

void comms_process_command(__uint8_t cmd_id){

    switch (cmd_id){
    case CMD_NOOP:
        break;
    case CMD_PING:
        printf("[COMMS] Pong!");
        break;
    case CMD_REBOOT:
        printf("[SYSTEM] Restarting OBC...");
        scheduler_init();
        break;
    case CMD_ENABLE_GNC:
        printf("[GNC] Control Activated");
        break;
    default:
        printf("[ERROR] Unknown command");
        break;
    }

}