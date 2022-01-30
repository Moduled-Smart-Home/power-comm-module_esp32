
esp_err_t i2c_master_init(void);
void turn_led_on(uint8_t slave_address);
void turn_led_off(uint8_t slave_address);
void set_power_level(uint8_t slave_address, uint8_t power_level);