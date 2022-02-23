/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "esp_log.h"
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "esp_wifi.h"

#include "i2c_commands.h"
#include "wifi.c"
#include "rest_server.c"

#define SLAVE_ADDRESS CONFIG_SLAVE_ADDRESS

#define WEB_MOUNT_POINT "/web"

static void test_i2c_comm(void *args)
{
    ESP_LOGI("TESTE", "Iniciando o teste...");

        uint16_t interval = 2000;

    while (true) {
        turn_led_on(SLAVE_ADDRESS);
        vTaskDelay(interval / portTICK_PERIOD_MS);
        turn_led_off(SLAVE_ADDRESS);
        vTaskDelay(interval / portTICK_PERIOD_MS);

        set_fan_power(SLAVE_ADDRESS, 1);
        set_fan_on(SLAVE_ADDRESS, 1);
        vTaskDelay(interval / portTICK_PERIOD_MS);

        for (int i=2; i<=5; i++) {
            set_fan_power(SLAVE_ADDRESS, i);
            vTaskDelay(interval / portTICK_PERIOD_MS);
        }
        
        set_fan_off(SLAVE_ADDRESS);
        vTaskDelay(interval / portTICK_PERIOD_MS);


        set_fan_power(SLAVE_ADDRESS, 1);
        set_fan_on(SLAVE_ADDRESS, 2);
        vTaskDelay(interval / portTICK_PERIOD_MS);

        for (int i=2; i<=5; i++) {
            set_fan_power(SLAVE_ADDRESS, i);
            vTaskDelay(interval / portTICK_PERIOD_MS);
        }

        set_lamp_on(SLAVE_ADDRESS);
        vTaskDelay(interval / portTICK_PERIOD_MS);

        set_lamp_off(SLAVE_ADDRESS);
        vTaskDelay(interval / portTICK_PERIOD_MS);
        
    }
}

void app_main(void)
{
    /* Print chip information */
    esp_chip_info_t chip_info;
    esp_chip_info(&chip_info);
    printf("This is %s chip with %d CPU core(s), WiFi%s%s, ",
            CONFIG_IDF_TARGET,
            chip_info.cores,
            (chip_info.features & CHIP_FEATURE_BT) ? "/BT" : "",
            (chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : "");

    printf("silicon revision %d, ", chip_info.revision);

    printf("%dMB %s flash\n", spi_flash_get_chip_size() / (1024 * 1024),
            (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");

    printf("Minimum free heap size: %d bytes\n", esp_get_minimum_free_heap_size());


    //Initialize NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
      ESP_ERROR_CHECK(nvs_flash_erase());
      ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    ESP_LOGI("WiFi", "ESP_WIFI_MODE_STA");
    wifi_init_sta();


    TaskHandle_t task_handle = NULL;

    ESP_ERROR_CHECK(i2c_master_init());

    ESP_ERROR_CHECK(start_rest_server(WEB_MOUNT_POINT));
    // xTaskCreate(test_i2c_comm, "test_i2c_comm", 2048, NULL, 5, &task_handle);

}
