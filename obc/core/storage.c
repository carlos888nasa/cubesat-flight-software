#include <stdio.h>
#include <stdint.h>
#include "storage.h"

static FILE *logfile;

bool storage_init(){
    logfile = fopen("../logs/flight_data.csv", "w");
    if (logfile == NULL) {
        fprintf(stderr, "[FDIR] ALERT: Hardware failure in memory (SD). Black box deactivated.\n");
        return false;
    }else {
        fprintf(logfile, "Time_ms,Voltage_V,Pos_X,Pos_Y,Pos_Z,Vel_X,Vel_Y,Vel_Z,Quat_W,Quat_X,Quat_Y,Quat_Z\n");
        return true;
    }
}

void storage_log_data(uint32_t time_ms, float voltage, Vec3 position, Vec3 velocity, Quaternion orientation) {
    if (logfile == NULL) {
        fprintf(stderr, "Log file not initialized.\n");
        return;
    }
    fprintf(logfile, "%u,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.4f,%.4f,%.4f,%.4f\n",
            time_ms, voltage,
            position.x, position.y, position.z,
            velocity.x, velocity.y, velocity.z,
            orientation.w, orientation.x, orientation.y, orientation.z);

    fflush(logfile);
}

void storage_close() {
    if (logfile != NULL) {
        fclose(logfile);
    }
}