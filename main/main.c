#include <stdio.h>
#include <pthread.h>

#include "nvs_flash.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_http_client.h"
#include "esp_log.h"
#include "freertos/semphr.h"
#include "driver/gpio.h"

#include "wifi/include/wifi.h"
#include "mqtt/include/mqtt.h"
#include "gpio/include/led.h"
#include "dht11/include/sensor_read.h"
#include "ky-036/include/ky-036.h"
#include "ky-003/include/ky-003.h"
#include "light-sleep/include/light-sleep.h"
#include "energy-mode/include/energy_mode.h"

void app_main(void)
{
    // Inicializa o NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    if (LOW_POWER)
    {
        batteryMode();
    }
    else
    {
        energyMode();
    }
}
