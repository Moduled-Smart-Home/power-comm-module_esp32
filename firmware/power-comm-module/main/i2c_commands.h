typedef enum {LED_ON, LED_OFF, FAN_OFF, FAN_ON_DIR1, FAN_ON_DIR2, POT1, POT2, POT3, POT4, POT5} command_t;

esp_err_t i2c_master_init(void);
void turn_led_on(uint8_t slave_address);
void turn_led_off(uint8_t slave_address);
void set_power_level(uint8_t slave_address, uint8_t power_level);
void set_fan_on (uint8_t slave_address, uint8_t dir);
void set_fan_off (uint8_t slave_address);