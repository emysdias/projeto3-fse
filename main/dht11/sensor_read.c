#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"

#include "freertos/semphr.h"
#include "freertos/queue.h"

#include "include/dht11.h"
#include "../mqtt/include/mqtt.h"

int temperature = 0;
int humidity = 0;

extern SemaphoreHandle_t conexaoMQTTSemaphore;

void readTempAndUmid()
{
    DHT11_init(GPIO_NUM_16);

    struct dht11_reading data_read = DHT11_read();

    if (data_read.status != 0 || data_read.temperature <= 0)
    {
        printf("Problema com a leitura do DHT11\n");
    }
    else
    {
        temperature = data_read.temperature;
        humidity = data_read.humidity;
    }
}

void tempUmidData(void *params)
{
    char mensagem[50];
    char JsonAtributos[200];
    while (xSemaphoreTake(conexaoMQTTSemaphore, portMAX_DELAY))
    {

        while (true)
        {
            readTempAndUmid();
            sprintf(mensagem, "{\"temperature\": %d}", temperature);
            mqtt_envia_mensagem("v1/devices/me/telemetry", mensagem);

            sprintf(JsonAtributos, "{\"umidade\": %d}", humidity);
            mqtt_envia_mensagem("v1/devices/me/attributes", JsonAtributos);
            vTaskDelay(1000 / portTICK_PERIOD_MS);
        }
    }
}