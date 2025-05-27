#include "esp_wifi.h"

#define WIFI_SSID "Redmi 10 2022"
#define WIFI_PASS "12345678"

void wifi_event_handler(void* arg, esp_event_base_t event_base,
                               int32_t event_id, void* event_data);

void wifi_init_sta(void);