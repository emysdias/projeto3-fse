#include <stdio.h>
#include "include/ky-003.h"
#include "driver/gpio.h"
#include "../mqtt/include/mqtt.h"
#include "esp_event.h"
#include "freertos/semphr.h"

int magnetic = 0;

void proximityHallRead()
{
    char mensagem[50];
    gpio_set_direction(HALL_GPIO, GPIO_MODE_INPUT); // DEFINE O PINO COMO ENTRADA
    magnetic = gpio_get_level(HALL_GPIO);
    printf("Magnetic: %d\n", magnetic);
    if (magnetic == 0)
    {
        printf("Sensor ligado!\n");
    }
    else
    {
        printf("Sensor desligado\n");
    }
    sprintf(mensagem, "{\"magnetic\": %d}", !magnetic);
    mqtt_envia_mensagem("v1/devices/me/attributes", mensagem);
}

void digitalHallHandle(void *params)
{

    while (true)
    {
        proximityHallRead();
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}