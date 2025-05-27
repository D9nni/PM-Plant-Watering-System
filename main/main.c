#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_adc/adc_oneshot.h"
#include "esp_timer.h"
#include "nvs_flash.h"
#include "dht.h"
#include "config.h"
#include "wifi.h"
#include "http.h"
#include "logs.h"

#define GPIO_WATER_START 3
#define GPIO_HUMIDTY_SENSOR 0
#define GPIO_DHT22 4

#define MIN_HUMIDITY 45

float temperature = 0.0f, humidity = 0.0f;
float soil_humidity = 0.0f;


void water_plant() {
        // deschide valva de apa
        log_message("Starting to water the plant.");
        gpio_set_level(GPIO_WATER_START, 1);
        vTaskDelay(pdMS_TO_TICKS(10000));
        
        // inchide valva de apa
        gpio_set_level(GPIO_WATER_START, 0);
        log_message("Finished watering the plant.");

}

void app_main(void)
{
    log_message("Starting plant watering system...");
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ESP_ERROR_CHECK(nvs_flash_init());
    }
    wifi_init_sta();
    start_webserver();
    // configureaza pinul pentru valva de apa
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << GPIO_WATER_START),
        .mode = GPIO_MODE_OUTPUT_OD,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&io_conf);

    // configureaza pinul pentru senzorul de umiditate
    gpio_config_t io_conf1 = {
        .pin_bit_mask = (1ULL << GPIO_HUMIDTY_SENSOR),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&io_conf1);

    // configureaza pinul pentru DHT22
    // (DHT22 este un senzor de umiditate si temperatura)
    gpio_config_t io_conf2 = {
        .pin_bit_mask = (1ULL << GPIO_DHT22),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&io_conf2);

    //configureaza adc-ul pentru senzorul de umiditate a solului
    adc_oneshot_unit_handle_t adc_handle;
    adc_oneshot_unit_init_cfg_t unit_cfg = {
        .unit_id = ADC_UNIT_1,
        .ulp_mode = ADC_ULP_MODE_DISABLE
    };

    // Initializeaza ADC unit
    ESP_ERROR_CHECK(adc_oneshot_new_unit(&unit_cfg, &adc_handle));

    // Configureaza canalul ADC (GPIO0 = ADC_CHANNEL_0) pentr
    adc_oneshot_chan_cfg_t chan_cfg = {
        .bitwidth = ADC_BITWIDTH_DEFAULT,
        .atten = ADC_ATTEN_DB_12         
    };
    ESP_ERROR_CHECK(adc_oneshot_config_channel(adc_handle, ADC_CHANNEL_0, &chan_cfg));

    int raw = 0;

    while(1) { 
        vTaskDelay(pdMS_TO_TICKS(10000)); // o data la 10 secunde fa verificarile
        ESP_ERROR_CHECK(adc_oneshot_read(adc_handle, ADC_CHANNEL_0, &raw));
        soil_humidity = ((4095 - raw) / 4096.0) * 100;
        printf("Soil humidity is: %.2f%%\n", soil_humidity);
        if(soil_humidity < MIN_HUMIDITY) {
            char message[50];
            sprintf(message, "Soil humidity is low: %.2f%%\n", soil_humidity);
            log_message(message);
            water_plant();
        } else {
            log_message("Soil humidity is sufficient.");
        }
        ESP_ERROR_CHECK(dht_read_float_data(DHT_TYPE_AM2301, GPIO_DHT22, &humidity, &temperature));
        printf("Read DHT22 sensor: Humidity: %.2f%%, Temperature: %.2f°C\n", humidity, temperature);

    
    }
}
