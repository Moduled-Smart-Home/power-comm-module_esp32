#ifndef I2C_COMMANDS_H
#define I2C_COMMANDS_H

typedef enum {LED_ON, LED_OFF, FAN_OFF, FAN_ON_DIR1, FAN_ON_DIR2, POT1, POT2, POT3, POT4, POT5, LAMP_ON, LAMP_OFF} command_t;

esp_err_t i2c_master_init(void);
esp_err_t turn_led_on(uint8_t slave_address);
esp_err_t turn_led_off(uint8_t slave_address);
esp_err_t set_fan_power(uint8_t slave_address, uint8_t power_level);
esp_err_t set_fan_on (uint8_t slave_address, uint8_t dir);
esp_err_t set_fan_off (uint8_t slave_address);
esp_err_t set_lamp_on (uint8_t slave_address);
esp_err_t set_lamp_off (uint8_t slave_address);

#endif