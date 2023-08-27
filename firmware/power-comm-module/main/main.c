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
#include "esp_vfs_semihost.h"
#include "esp_vfs_fat.h"
#include "esp_spiffs.h"
#include "nvs_flash.h"
#include "esp_netif.h"
#include "esp_event.h"

#include "lwip/apps/netbiosns.h"
#include "mdns.h"
#include "lwip/apps/netbiosns.h"
#include "esp_wifi.h"

#include "i2c_commands.h"
#include "wifi.c"
#include "rest_server.c"

#define SLAVE_ADDRESS CONFIG_SLAVE_ADDRESS

#define MDNS_INSTANCE "esp home web server"
#define WEB_MOUNT_POINT "/www"
#define MDNS_HOST_NAME "ModuledSmartHome"

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

static void initialise_mdns(void)
{
    mdns_init();
    mdns_hostname_set(MDNS_HOST_NAME);
    mdns_instance_name_set(MDNS_INSTANCE);

    mdns_txt_item_t serviceTxtData[] = {
        {"board", "esp32"},
        {"path", "/"}
    };

    ESP_ERROR_CHECK(mdns_service_add("ESP32-WebServer", "_http", "_tcp", 80, serviceTxtData,
                                     sizeof(serviceTxtData) / sizeof(serviceTxtData[0])));
}

esp_err_t init_fs(void)
{
    esp_vfs_spiffs_conf_t conf = {
        .base_path = WEB_MOUNT_POINT,
        .partition_label = NULL,
        .max_files = 5,
        .format_if_mount_failed = false
    };
    esp_err_t ret = esp_vfs_spiffs_register(&conf);

    if (ret != ESP_OK) {
        if (ret == ESP_FAIL) {
            ESP_LOGE(TAG, "Failed to mount or format filesystem");
        } else if (ret == ESP_ERR_NOT_FOUND) {
            ESP_LOGE(TAG, "Failed to find SPIFFS partition");
        } else {
            ESP_LOGE(TAG, "Failed to initialize SPIFFS (%s)", esp_err_to_name(ret));
        }
        return ESP_FAIL;
    }

    size_t total = 0, used = 0;
    ret = esp_spiffs_info(NULL, &total, &used);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to get SPIFFS partition information (%s)", esp_err_to_name(ret));
    } else {
        ESP_LOGI(TAG, "Partition size: total: %d, used: %d", total, used);
    }
    return ESP_OK;
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

    esp_ota_img_states_t ota_state = ESP_OTA_IMG_UNDEFINED;
    esp_ota_get_state_partition(esp_ota_get_running_partition(), &ota_state);
    if(ota_state == ESP_OTA_IMG_PENDING_VERIFY) {
        ESP_LOGI("START UP", "Marking app as valid and cancelling rollback");\
        esp_ota_mark_app_valid_cancel_rollback();
    }

    //Configure IOs
    gpio_set_direction(GPIO_NUM_19, GPIO_MODE_OUTPUT);
    gpio_set_level(GPIO_NUM_19, 0);
    gpio_set_direction(GPIO_NUM_23, GPIO_MODE_INPUT);
    gpio_pullup_en(GPIO_NUM_23);
    gpio_pullup_en(GPIO_NUM_32);
    gpio_pullup_en(GPIO_NUM_33);

    //Initialize NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
      ESP_ERROR_CHECK(nvs_flash_erase());
      ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    ESP_LOGI("WiFi", "ESP_WIFI_MODE_STA");
    wifi_init_sta();


    ESP_ERROR_CHECK(i2c_master_init());

    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_netif_init());
    // ESP_ERROR_CHECK(esp_event_loop_create_default());
    initialise_mdns();
    // netbiosns_init();
    // netbiosns_set_name(MDNS_HOST_NAME);

    ESP_ERROR_CHECK(init_fs());
    ESP_ERROR_CHECK(start_rest_server(WEB_MOUNT_POINT));

}
