#include "logs.h"
#include <stdio.h>
#include "esp_timer.h"

char logs[MAX_LOGS][LOG_MESSAGE_SIZE];
int log_index = 0;
void log_message(const char *message) {
    int64_t now_us = esp_timer_get_time();
    int end = snprintf(logs[log_index], sizeof(logs[log_index]), "{\"%lld\": \"%s\"}", now_us, message);
    logs[log_index][end] = '\0';
    log_index = (log_index + 1) % MAX_LOGS;
}
char** get_logs() {
    return (char**) logs;
}
int get_log_index() {
    return log_index;
}