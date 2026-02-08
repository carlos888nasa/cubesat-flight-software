#ifndef COMMANDS_H
#define COMMANDS_H   

#include <stdint.h>

typedef enum {
    CMD_NOOP = 0,
    CMD_PING = 1,
    CMD_REBOOT = 2,
    CMD_ENABLE_GNC = 3,
} CommandID;

void comms_process_command(__uint8_t cmd_id);

#endif