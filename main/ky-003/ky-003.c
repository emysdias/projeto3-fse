#include <stdio.h>
#include "include/ky-003.h"
#include "driver/gpio.h"
#include "../mqtt/include/mqtt.h"

int magnetic = 0;

void proximityHallRead()
{
    const int pinoSensor = 36; // PINO DIGITAL UTILIZADO PELO SENSOR:  "TX2" - ESP32
    char mensagem[50];
    gpio_set_direction(pinoSensor, GPIO_MODE_INPUT); // DEFINE O PINO COMO ENTRADA
    magnetic = gpio_get_level(pinoSensor);
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