#include <stdio.h>

#include "driver/gpio.h"
#include "esp_event.h"
#include "freertos/semphr.h"

#include "../mqtt/include/mqtt.h"
#include "include/ky-036.h"

int touch = 0;

void touchRead()
{
    char mensagem[50];
    gpio_set_direction(TOUCH_GPIO, GPIO_MODE_INPUT);
    touch = gpio_get_level(TOUCH_GPIO);
    printf("Touch: %d\n", touch);
    if (touch == 1)
    {
        printf("Sensor ligado!\n");
    }
    else
    {
        printf("Sensor desligado\n");
    }
    sprintf(mensagem, "{\"touch\": %d}", touch);
    mqtt_envia_mensagem("v1/devices/me/attributes", mensagem);
}

void touchHandle(void *params)
{

    while (true)
    {
        touchRead();
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}