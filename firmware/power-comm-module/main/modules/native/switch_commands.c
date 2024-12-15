#include "switch_commands.h"

#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"
#include "esp_log.h"
#include "esp_system.h"
#include "driver/gpio.h"

#define TAG "SWITCH_COMMANDS"

#define DEBOUNCE_MS 30
#define SHORT_MS 700
#define LONG_MS 2000

#define INPUT_IO GPIO_NUM_23

bool TOGGLED = false;
int LAST_LEVEL;
int COMMAND = 0;

switch_command_state_enum state = IDLE;

TimerHandle_t xDebounceTimer;
TimerHandle_t xWaitToggleTimer;

void debounce_timer_handler( TimerHandle_t pxTimer ){
    int ACTUAL_LEVEL = gpio_get_level(INPUT_IO);
    
    if (ACTUAL_LEVEL != LAST_LEVEL){
        TOGGLED = true;
        LAST_LEVEL = ACTUAL_LEVEL;
    }

    gpio_intr_enable(INPUT_IO);
}

static void switch_level_isr_handler(void* arg){
    gpio_intr_disable(INPUT_IO);

    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    if( xTimerStartFromISR( xDebounceTimer, &xHigherPriorityTaskWoken ) != pdPASS )
    {
    }
     
}

void wait_toggle_timer_handler(TimerHandle_t pxTimer){
    switch (state)
        {
            case WAIT_SHORT:
                xTimerChangePeriod(xWaitToggleTimer, (LONG_MS - SHORT_MS) / portTICK_PERIOD_MS, 100);
                state = WAIT_LONG;
                break;

            case WAIT_LONG:
                ESP_LOGI(TAG, "Final command is %d", COMMAND);
                COMMAND = 0;
                state = IDLE;
                break;

            default:
                break;
        }

}

void switch_toggled_event_handler(void* arg){
    while(true){
        if (TOGGLED){
            ESP_LOGI(TAG, "Toggled");
            TOGGLED = false;

            switch (state)
            {
                case IDLE:
                    COMMAND = (COMMAND << 1) + 1;
                    xTimerChangePeriod(xWaitToggleTimer, SHORT_MS / portTICK_PERIOD_MS, 100);
                    state = WAIT_SHORT;
                    break;

                case WAIT_SHORT:
                    xTimerReset(xWaitToggleTimer, 100);
                    COMMAND = (COMMAND << 1) + 1;
                    break;

                case WAIT_LONG:
                    xTimerChangePeriod(xWaitToggleTimer, SHORT_MS / portTICK_PERIOD_MS, 100);
                    COMMAND = (COMMAND << 2) + 1;
                    state = WAIT_SHORT;
                    break;
                
                default:
                    break;
            }
        }
    }
}




void initialize_switch_commands() {

    ESP_LOGI(TAG, "Initializing Switch Commands Module");
    ESP_LOGI(TAG, "portTICK_PERIOD_MS: %d", portTICK_PERIOD_MS);

    gpio_set_direction(INPUT_IO, GPIO_MODE_INPUT);
    gpio_pullup_en(INPUT_IO);
    gpio_set_intr_type(INPUT_IO, GPIO_INTR_ANYEDGE);
    gpio_intr_enable(INPUT_IO);

    //install gpio isr service
    gpio_install_isr_service(0);
    gpio_isr_handler_add(INPUT_IO, switch_level_isr_handler, NULL);

    LAST_LEVEL = gpio_get_level(INPUT_IO);


    xDebounceTimer = xTimerCreate("Debounce timer", DEBOUNCE_MS / portTICK_PERIOD_MS, pdFALSE, NULL, debounce_timer_handler);
    xWaitToggleTimer = xTimerCreate("Wait toggle timer", SHORT_MS / portTICK_PERIOD_MS, pdFALSE, NULL, wait_toggle_timer_handler);

    xTaskCreate(switch_toggled_event_handler, "switch_toggled_event_handler", 2048, NULL, 10, NULL);

    ESP_LOGI(TAG, "Switch Commands Module Initialized");
}