#include <stdio.h>
#include <string.h>

#include "../gpio/include/led.h"
#include "include/cJSON.h"

void parseJsonMsg(char *jsonString)
{
    cJSON *root = cJSON_Parse(jsonString);
    char *method = cJSON_GetObjectItem(root, "method")->valuestring;

    if (strcmp(method, "setLedPWM") == 0)
    {
        double intensidade = cJSON_GetObjectItem(root, "params")->valuedouble;
        intensity = intensidade;
    }
}
