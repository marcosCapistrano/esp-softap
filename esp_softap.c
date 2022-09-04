#include "esp_softap.h"
#include <string.h>

#include "esp_wifi.h"
#include "esp_log.h"

#define ESP_SOFTAP_SSID CONFIG_ESP_SOFTAP_SSID
#define ESP_SOFTAP_PASS CONFIG_ESP_SOFTAP_PASSWORD
#define ESP_SOFTAP_CHANNEL CONFIG_ESP_SOFTAP_CHANNEL
#define ESP_SOFTAP_MAX_STA_CONN CONFIG_ESP_SOFTAP_MAX_STA_CONN

static const char* TAG = "ESP-SOFTAP";

/*
Example of an implementation of a wifi event handler:

static void wifi_event_handler(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data) 
{
    if (event_id == WIFI_EVENT_AP_STACONNECTED) {
        wifi_event_ap_staconnected_t* event = (wifi_event_ap_staconnected_t*)event_data;
        ESP_LOGI(TAG, "station " MACSTR " join, AID=%d", MAC2STR(event->mac), event->aid);
    } else if (event_id == WIFI_EVENT_AP_STADISCONNECTED) {
        wifi_event_ap_stadisconnected_t* event = (wifi_event_ap_stadisconnected_t*)event_data;
        ESP_LOGI(TAG, "station " MACSTR " leave, AID=%d", MAC2STR(event->mac), event->aid);
    }
}

*/

void esp_softap_init(void) 
{
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_ap();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    wifi_config_t wifi_config = {
        .ap = {
            .ssid = ESP_SOFTAP_SSID,
            .ssid_len = strlen(ESP_SOFTAP_SSID),
            .channel = ESP_SOFTAP_CHANNEL,
            .password = ESP_SOFTAP_PASS,
            .max_connection = ESP_SOFTAP_MAX_STA_CONN,
            .authmode = WIFI_AUTH_WPA_WPA2_PSK
        },
    };

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_AP, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());

    ESP_LOGI(TAG, "SOFT AP initialized! SSID:%s password:%s channel:%d", ESP_SOFTAP_SSID, ESP_SOFTAP_PASS, ESP_SOFTAP_CHANNEL);
}