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

SemaphoreHandle_t conexaoWifiSemaphore;
SemaphoreHandle_t conexaoMQTTSemaphore;

void mqttTask(void *params)
{
    xTaskCreate(&conectadoWifi, "Conexão ao MQTT", 4096, NULL, 1, NULL);
}

void dht11Task(void *params)
{
    xTaskCreate(&tempUmidData, "Comunicação com Broker", 4096, NULL, 1, NULL);
}

void ledPWMTask(void *params)
{
    xTaskCreate(&ledHandle, "Configurando Led", 4096, NULL, 1, NULL);
}

void ky036Task(void *params)
{
    xTaskCreate(&touchHandle, "Sensor de Toque", 4096, NULL, 1, NULL);
}

void ky003Task(void *params)
{
    xTaskCreate(&digitalHallHandle, "Sensor Hall", 4096, NULL, 1, NULL);
}

void energyMode()
{
    conexaoWifiSemaphore = xSemaphoreCreateBinary();
    conexaoMQTTSemaphore = xSemaphoreCreateBinary();
    wifi_start();
    gpioSetLed();

    pthread_t tid[5];

    pthread_create(&tid[0], NULL, (void *)mqttTask, (void *)NULL);
    // pthread_create(&tid[1], NULL, (void *)dht11Task, (void *)NULL);
    pthread_create(&tid[2], NULL, (void *)ledPWMTask, (void *)NULL);
    pthread_create(&tid[3], NULL, (void *)ky036Task, (void *)NULL);
    pthread_create(&tid[4], NULL, (void *)ky003Task, (void *)NULL);

    pthread_join(tid[0], NULL);
    // pthread_join(tid[1], NULL);
    pthread_join(tid[2], NULL);
    pthread_join(tid[3], NULL);
    pthread_join(tid[4], NULL);
}

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
