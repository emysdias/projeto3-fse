#include <stdio.h>
#include <string.h>

#include "../gpio/include/led.h"
#include "include/cJSON.h"
#include "../ky-036/include/ky-036.h"
#include "../mqtt/include/mqtt.h"

void parseJsonMsg(char *jsonString, char *topic)
{
    cJSON *root = cJSON_Parse(jsonString);
    char *method = cJSON_GetObjectItem(root, "method")->valuestring;

    if (strcmp(method, "setLedPWM") == 0)
    {
        double intensidade = cJSON_GetObjectItem(root, "params")->valuedouble;
        intensity = intensidade;
    }
    else if (strcmp(method, "checkTouch") == 0)
    {
        char mensagem[50];
        sprintf(mensagem, "{\"touch\": %d}", touch);
        mqtt_envia_mensagem("v1/devices/me/attributes", mensagem);
    }
}
