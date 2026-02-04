#include <stdio.h>
#include "core/scheduler.h"

void scheduler_init() {
    // Inicialización del scheduler
    printf("[Scheduler] Inicializando...\n");
}

void scheduler_run() {
    // Ejecución del scheduler
    printf("[Scheduler] Ejecutando ciclo...\n");
}

bool scheduler_wait_next_cycle() {
    // Esperar hasta el siguiente ciclo del scheduler
    printf("[Scheduler] Esperando al siguiente ciclo...\n");
    return true; // Simulación de espera exitosa
}

uint32_t scheduler_get_uptime_ms() {
    // Retornar el tiempo de actividad en milisegundos
    static uint32_t uptime = 0;
    uptime += SYSTEM_CYCLE_MS; // Simulación de incremento de tiempo
    return uptime;
}
