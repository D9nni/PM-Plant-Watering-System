#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define GPIO_WATER_START 4
#define GPIO_HUMIDTY_SENSOR 2
#define GPIO_DHT22 3

#define MIN_HUMIDITY 30
char logs[20][30];
int log_index = 0;
void log(const char *message) {
    snprintf(logs[log_index], sizeof(logs[log_index]), "%s", message);
    log_index = (log_index + 1) % 20; // Circular buffer
}

void water_plant() {
        gpio_set_level(GPIO_WATER_START, 1);
        printf("Turned water on!\n");
        vTaskDelay(pdMS_TO_TICKS(10000));
        
        // scrie LOW (0)
        gpio_set_level(GPIO_WATER_START, 0);
        printf("Turned water off!\n");
}
void app_main(void)
{
    printf("Hello from ESP32-C6!\n");

    // configureaza pinul pentru valva de apa
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << GPIO_WATER_START),
        .mode = GPIO_MODE_OUTPUT_OD,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = 0,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&io_conf);

    // configureaza pinul pentru senzorul de umiditate
    gpio_config_t io_conf1 = {
        .pin_bit_mask = (1ULL << GPIO_HUMIDTY_SENSOR),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = 0,
        .pull_down_en = 0,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&io_conf1);

    // configureaza pinul pentru DHT22
    // (DHT22 este un senzor de umiditate si temperatura)
    gpio_config_t io_conf2 = {
        .pin_bit_mask = (1ULL << GPIO_DHT22),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = 0,
        .pull_down_en = 0,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&io_conf2);


    while(1) { 
        // scrie HIGH (1)
        gpio_set_level(GPIO_WATER_START, 1);
        printf("Turned water on!\n");
        vTaskDelay(pdMS_TO_TICKS(10000));
        
        // scrie LOW (0)
        gpio_set_level(GPIO_WATER_START, 0);
        printf("Turned water off!\n");
        vTaskDelay(pdMS_TO_TICKS(10000));
    }
}
