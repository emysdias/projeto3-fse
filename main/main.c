#include <stdio.h>

#include "nvs_flash.h"

#include "light-sleep/include/light-sleep.h"
#include "energy-mode/include/energy_mode.h"

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
