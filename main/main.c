#include <stdio.h>
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

SemaphoreHandle_t conexaoWifiSemaphore;
SemaphoreHandle_t conexaoMQTTSemaphore;

void conectadoWifi(void *params)
{
    while (true)
    {
        if (xSemaphoreTake(conexaoWifiSemaphore, portMAX_DELAY))
        {
            // Processamento Internet
            mqtt_start();
        }
    }
}

void trataComunicacaoComServidor(void *params)
{
    char mensagem[50];
    char JsonAtributos[200];
    if (xSemaphoreTake(conexaoMQTTSemaphore, portMAX_DELAY))
    {

        while (true)
        {
            readTempAndUmid();
            sprintf(mensagem, "{\"temperature\": %d}", temperature);
            mqtt_envia_mensagem("v1/devices/me/telemetry", mensagem);

            sprintf(JsonAtributos, "{\"quantidade de pinos\": 5,\n\"umidade\": %d}", humidity);
            mqtt_envia_mensagem("v1/devices/me/attributes", JsonAtributos);
            vTaskDelay(1000 / portTICK_PERIOD_MS);
        }
    }
}

void ledHandle(void *params)
{
    if (xSemaphoreTake(conexaoMQTTSemaphore, portMAX_DELAY))
    {
        while (true)
        {
            ledPWM();
            vTaskDelay(1000 / portTICK_PERIOD_MS);
        }
    }
}

void touchHandle(void *params)
{

    if (xSemaphoreTake(conexaoMQTTSemaphore, portMAX_DELAY))
    {
        while (true)
        {
            touchRead();
            vTaskDelay(1000 / portTICK_PERIOD_MS);
        }
    }
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

    conexaoWifiSemaphore = xSemaphoreCreateBinary();
    conexaoMQTTSemaphore = xSemaphoreCreateBinary();
    wifi_start();
    gpioSetLed();

    xTaskCreate(&conectadoWifi, "Conexão ao MQTT", 4096, NULL, 1, NULL);
    // xTaskCreate(&trataComunicacaoComServidor, "Comunicação com Broker", 4096, NULL, 1, NULL);
    // xTaskCreate(&ledHandle, "Configurando Led", 4096, NULL, 1, NULL);
    xTaskCreate(&touchHandle, "Configurando Led", 4096, NULL, 1, NULL);
}
