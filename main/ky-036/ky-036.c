#include <stdio.h>
#include "include/ky-036.h"
#include "driver/gpio.h"
#include "../mqtt/include/mqtt.h"

int touch = 0;

void touchRead()
{
    const int pinoSensor = 4; // PINO DIGITAL UTILIZADO PELO SENSOR:  "D4" - ESP32
    char mensagem[50];
    gpio_set_direction(pinoSensor, GPIO_MODE_INPUT); // DEFINE O PINO COMO ENTRADA
    touch = gpio_get_level(pinoSensor);
    if (touch == 1)
    {
        printf("Sensor ligado!\n");
    }
    else
    { // SENÃO, FAZ
        printf("Sensor desligado\n");
    }
    sprintf(mensagem, "{\"touch\": %d}", touch);
    mqtt_envia_mensagem("v1/devices/me/attributes", mensagem);
}