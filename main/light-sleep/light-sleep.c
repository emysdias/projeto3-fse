#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_sleep.h"
#include "esp_log.h"
#include "esp32/rom/uart.h"
#include "driver/gpio.h"

// Driver da GPIO com funções estendidas para o modo sleep
#include "driver/rtc_io.h"

#include "../ky-003/include/ky-003.h"
#include "../ky-036/include/ky-036.h"
#include "../mqtt/include/mqtt.h"
#include "../wifi/include/wifi.h"

#define BOTAO 0

void batteryMode()
{
    // Configuração da GPIO para o botão de entrada
    esp_rom_gpio_pad_select_gpio(BOTAO);
    esp_rom_gpio_pad_select_gpio(TOUCH_GPIO);
    esp_rom_gpio_pad_select_gpio(HALL_GPIO);

    gpio_set_direction(BOTAO, GPIO_MODE_INPUT);
    gpio_set_direction(TOUCH_GPIO, GPIO_MODE_INPUT);
    gpio_set_direction(HALL_GPIO, GPIO_MODE_INPUT);
    // Habilita o botão para acordar a placa
    gpio_wakeup_enable(BOTAO, GPIO_INTR_LOW_LEVEL);
    gpio_wakeup_enable(TOUCH_GPIO, GPIO_INTR_HIGH_LEVEL);
    gpio_wakeup_enable(HALL_GPIO, GPIO_INTR_LOW_LEVEL);
    esp_sleep_enable_gpio_wakeup();

    // Configurando o Sleep Timer (em microsegundos)
    esp_sleep_enable_timer_wakeup(60 * 1000000);

    while (true)
    {

        if (rtc_gpio_get_level(BOTAO) == 0)
        {
            printf("Acordado pelo botão da ESP\n");
            printf("Aguardando soltar o botão ... \n");
            do
            {
                vTaskDelay(pdMS_TO_TICKS(10));
            } while (rtc_gpio_get_level(BOTAO) == 0);
        }
        else if (rtc_gpio_get_level(HALL_GPIO) == 0)
        {
            printf("Acordado pelo sensor de toque KY-003\n");
            printf("Aguardando sensor magnético desligar!\n");
            wifi_start();
            mqtt_start();
            do
            {
                proximityHallRead();
                vTaskDelay(1000 / portTICK_PERIOD_MS);
            } while (rtc_gpio_get_level(HALL_GPIO) == 0);
            proximityHallRead();
        }
        else if (rtc_gpio_get_level(TOUCH_GPIO) == 1)
        {
            printf("Acordado pelo Sensor Hall KY-036\n");
            printf("Aguardando soltar sensor de toque!\n");
            wifi_start();
            mqtt_start();
            do
            {
                touchRead();
                vTaskDelay(1000 / portTICK_PERIOD_MS);
            } while (rtc_gpio_get_level(TOUCH_GPIO) == 1);
            touchRead();
        }

        printf("Entrando em modo Light Sleep\n");

        // Configura o modo sleep somente após completar a escrita na UART para finalizar o printf
        uart_tx_wait_idle(CONFIG_ESP_CONSOLE_UART_NUM);

        // // Entra em modo Light Sleep
        esp_light_sleep_start();

        esp_sleep_wakeup_cause_t causa = esp_sleep_get_wakeup_cause();

        if (causa == ESP_SLEEP_WAKEUP_TIMER)
            printf("O TIMER me acordou !\n");
    }
}
