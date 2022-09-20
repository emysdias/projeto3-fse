#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"

#include "include/dht11.h"

int temperature = 0;
int humidity = 0;

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