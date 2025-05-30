#include "http.h"
#include "config.h"
#include "logs.h"
extern const uint8_t index_html_start[] asm("_binary_index_html_start");
extern const uint8_t index_html_end[]   asm("_binary_index_html_end");

esp_err_t index_handler(httpd_req_t *req) {
    httpd_resp_set_type(req, "text/html");
    return httpd_resp_send(req, (const char *)index_html_start, index_html_end - index_html_start);
}

esp_err_t dht_get_handler(httpd_req_t *req) {
    printf("HTTP: Reading DHT22 sensor...\n");
    char resp[64];
    snprintf(resp, sizeof(resp), "{\"temp\": %.1f, \"hum\": %.1f}", temperature, humidity);

    httpd_resp_set_type(req, "application/json");
    httpd_resp_send(req, resp, strlen(resp));
    return ESP_OK;
}

esp_err_t soil_get_handler(httpd_req_t *req) {
    printf("HTTP: Reading soil humidity...\n");
    char resp[64];
    snprintf(resp, sizeof(resp), "{\"humidity\": %d}", soil_humidity);

    httpd_resp_set_type(req, "application/json");
    httpd_resp_send(req, resp, strlen(resp));
    return ESP_OK;
}
esp_err_t water_get_handler(httpd_req_t *req) {
    printf("HTTP: Starting water plant...\n");
    char resp[64];
    snprintf(resp, sizeof(resp), "{\"water\": \"started for 10 seconds\"}");
    water_plant();
    httpd_resp_set_type(req, "application/json");
    httpd_resp_send(req, resp, strlen(resp));
    return ESP_OK;
}
esp_err_t logs_get_handler(httpd_req_t *req) {
    printf("HTTP: Transmitting logs...\n");
    char resp[MAX_LOGS * LOG_MESSAGE_SIZE + 20]; // +2 for brackets
    char (*logs)[LOG_MESSAGE_SIZE] = (char (*)[LOG_MESSAGE_SIZE]) get_logs();
    int log_index = get_log_index();
    int offset = 0;
    offset = snprintf(resp, sizeof(resp) - offset, "{\"logs\": [");
    for (int i = 0; i < log_index; i++) {
        offset += snprintf(resp + offset, sizeof(resp) - offset, logs[i]);
        if(i < log_index - 1) {
            offset += snprintf(resp + offset, sizeof(resp) - offset, ", ");
        }
    }
    offset += snprintf(resp + offset, sizeof(resp) - offset, "]}");
    resp[offset] = '\0'; 
    httpd_resp_set_type(req, "application/json");
    httpd_resp_send(req, resp, offset);

    return ESP_OK;
}

httpd_handle_t start_webserver(void) {
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    httpd_handle_t server = NULL;

    if (httpd_start(&server, &config) == ESP_OK) {
        httpd_uri_t index_uri = {
            .uri       = "/",
            .method    = HTTP_GET,
            .handler   = index_handler
        };
        httpd_register_uri_handler(server, &index_uri);
        httpd_uri_t dht_uri = {
            .uri      = "/dht",
            .method   = HTTP_GET,
            .handler  = dht_get_handler,
            .user_ctx = NULL
        };
        httpd_register_uri_handler(server, &dht_uri);
        httpd_uri_t soil_uri = {
            .uri      = "/soil",
            .method   = HTTP_GET,
            .handler  = soil_get_handler,
            .user_ctx = NULL
        };
        httpd_register_uri_handler(server, &soil_uri);
        httpd_uri_t water_uri = {
            .uri      = "/water",
            .method   = HTTP_GET,
            .handler  = water_get_handler,
            .user_ctx = NULL
        };
        httpd_register_uri_handler(server, &water_uri);
        httpd_register_uri_handler(server, &soil_uri);
        httpd_uri_t logs_uri = {
            .uri      = "/logs",
            .method   = HTTP_GET,
            .handler  = logs_get_handler,
            .user_ctx = NULL
        };
        httpd_register_uri_handler(server, &logs_uri);
    }
    return server;
}