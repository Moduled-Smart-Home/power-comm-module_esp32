#include <stdio.h>
#include "esp_log.h"
#include "driver/i2c.h"

#include "i2c_commands.h"

#define _I2C_NUMBER(num) I2C_NUM_##num
#define I2C_NUMBER(num) _I2C_NUMBER(num)

#define I2C_SLAVE_SCL_IO CONFIG_I2C_SLAVE_SCL               /*!< gpio number for i2c slave clock */
#define I2C_SLAVE_SDA_IO CONFIG_I2C_SLAVE_SDA               /*!< gpio number for i2c slave data */
#define I2C_SLAVE_NUM I2C_NUMBER(CONFIG_I2C_SLAVE_PORT_NUM) /*!< I2C port number for slave dev */
#define I2C_SLAVE_TX_BUF_LEN (2 * DATA_LENGTH)              /*!< I2C slave tx buffer size */
#define I2C_SLAVE_RX_BUF_LEN (2 * DATA_LENGTH)              /*!< I2C slave rx buffer size */

#define I2C_MASTER_SCL_IO CONFIG_I2C_MASTER_SCL               /*!< gpio number for I2C master clock */
#define I2C_MASTER_SDA_IO CONFIG_I2C_MASTER_SDA               /*!< gpio number for I2C master data  */
#define I2C_MASTER_NUM I2C_NUMBER(CONFIG_I2C_MASTER_PORT_NUM) /*!< I2C port number for master dev */
#define I2C_MASTER_FREQ_HZ CONFIG_I2C_MASTER_FREQUENCY        /*!< I2C master clock frequency */
#define I2C_MASTER_TX_BUF_DISABLE 0                           /*!< I2C master doesn't need buffer */
#define I2C_MASTER_RX_BUF_DISABLE 0                           /*!< I2C master doesn't need buffer */

#define WRITE_BIT I2C_MASTER_WRITE              /*!< I2C master write */
#define READ_BIT I2C_MASTER_READ                /*!< I2C master read */
#define ACK_CHECK_EN 0x1                        /*!< I2C master will check ack from slave*/
#define ACK_CHECK_DIS 0x0                       /*!< I2C master will not check ack from slave */
#define ACK_VAL 0x0                             /*!< I2C ack value */
#define NACK_VAL 0x1  


command_t command;

/**
 * @brief i2c master initialization
 */
esp_err_t i2c_master_init(void)
{
    int i2c_master_port = I2C_MASTER_NUM;
    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = I2C_MASTER_SDA_IO,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_io_num = I2C_MASTER_SCL_IO,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = I2C_MASTER_FREQ_HZ,
        // .clk_flags = 0,          /*!< Optional, you can use I2C_SCLK_SRC_FLAG_* flags to choose i2c source clock here. */
    };
    esp_err_t err = i2c_param_config(i2c_master_port, &conf);
    if (err != ESP_OK) {
        return err;
    }
    return i2c_driver_install(i2c_master_port, conf.mode, I2C_MASTER_RX_BUF_DISABLE, I2C_MASTER_TX_BUF_DISABLE, 0);
}

static esp_err_t write_slave(i2c_port_t i2c_num, uint8_t slave_address, uint8_t data)
{
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (slave_address) | WRITE_BIT, ACK_CHECK_EN);
    i2c_master_write_byte(cmd, data, ACK_CHECK_EN);
    i2c_master_stop(cmd);
    esp_err_t ret = i2c_master_cmd_begin(i2c_num, cmd, 1000 / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);
    return ret;
}

static esp_err_t read_slave(i2c_port_t i2c_num, uint8_t slave_address, uint8_t *data_rd)
{
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (slave_address) | READ_BIT, ACK_CHECK_EN);
    i2c_master_read_byte(cmd, data_rd, NACK_VAL);
    i2c_master_stop(cmd);
    esp_err_t ret = i2c_master_cmd_begin(i2c_num, cmd, 1000 / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);
    return ret;
}

esp_err_t turn_led_on(uint8_t slave_address)
{

    ESP_LOGI("TESTE", "Turning LED on");
    esp_err_t ret = write_slave(I2C_MASTER_NUM, slave_address, LED_ON);

    if (ret == ESP_ERR_TIMEOUT) {
        ESP_LOGE("TESTE", "I2C Timeout on Sending");
    } else if (ret == ESP_OK) {
        ESP_LOGI("TESTE", "Data sent.");
    } else {
        ESP_LOGE("TESTE", "Another problem");
    } 

    return ret;
}

esp_err_t turn_led_off(uint8_t slave_address)
{
    ESP_LOGI("TESTE", "Turning LED off");
    esp_err_t ret = write_slave(I2C_MASTER_NUM, slave_address, LED_OFF);

    if (ret == ESP_ERR_TIMEOUT) {
        ESP_LOGE("TESTE", "I2C Timeout on Sending");
    } else if (ret == ESP_OK) {
        ESP_LOGI("TESTE", "Data sent.");
    } else {
        ESP_LOGE("TESTE", "Another problem");
    } 

    return ret;
}

esp_err_t set_fan_power (uint8_t slave_address, uint8_t level)
{
    uint8_t dsend = 0;
    
    switch (level) {
        case 1:
            dsend = POT1;
            break;
        case 2:
            dsend = POT2;
            break;
        case 3: 
            dsend = POT3;
            break;
        case 4:
            dsend = POT4;
            break;
        case 5:
            dsend = POT5;
            break;
    }
    
    ESP_LOGI("TESTE", "Setting power level: %d", level);

    esp_err_t ret = write_slave(I2C_MASTER_NUM, slave_address, dsend);

    if (ret == ESP_ERR_TIMEOUT) {
        ESP_LOGE("TESTE", "I2C Timeout on Sending");
    } else if (ret == ESP_OK) {
        ESP_LOGI("TESTE", "Data sent.");
    } else {
        ESP_LOGE("TESTE", "Another problem");
    } 

    return ret;
}

esp_err_t set_fan_on (uint8_t slave_address, uint8_t dir)
{
    uint8_t dsend = 0;
    
    if (dir == 1) {
        dsend = FAN_ON_DIR1;
    } else if (dir == 2) {
        dsend = FAN_ON_DIR2;
    }
    
    ESP_LOGI("TESTE", "Setting fan on. Direction: %d", dir);

    esp_err_t ret = write_slave(I2C_MASTER_NUM, slave_address, dsend);

    if (ret == ESP_ERR_TIMEOUT) {
        ESP_LOGE("TESTE", "I2C Timeout on Sending");
    } else if (ret == ESP_OK) {
        ESP_LOGI("TESTE", "Data sent.");
    } else {
        ESP_LOGE("TESTE", "Another problem");
    } 

    return ret;
}

esp_err_t set_fan_off (uint8_t slave_address)
{
    ESP_LOGI("TESTE", "Turning fan off");
    esp_err_t ret = write_slave(I2C_MASTER_NUM, slave_address, FAN_OFF);

    if (ret == ESP_ERR_TIMEOUT) {
        ESP_LOGE("TESTE", "I2C Timeout on Sending");
    } else if (ret == ESP_OK) {
        ESP_LOGI("TESTE", "Data sent.");
    } else {
        ESP_LOGE("TESTE", "Another problem");
    } 

    return ret;
}

esp_err_t set_lamp_on (uint8_t slave_address)
{
    ESP_LOGI("TESTE", "Setting lamp on.");

    esp_err_t ret = write_slave(I2C_MASTER_NUM, slave_address, LAMP_ON);

    if (ret == ESP_ERR_TIMEOUT) {
        ESP_LOGE("TESTE", "I2C Timeout on Sending");
    } else if (ret == ESP_OK) {
        ESP_LOGI("TESTE", "Data sent.");
    } else {
        ESP_LOGE("TESTE", "Another problem");
    } 

    return ret;

}

esp_err_t set_lamp_off (uint8_t slave_address)
{
    ESP_LOGI("TESTE", "Turning lamp off");
    esp_err_t ret = write_slave(I2C_MASTER_NUM, slave_address, LAMP_OFF);

    if (ret == ESP_ERR_TIMEOUT) {
        ESP_LOGE("TESTE", "I2C Timeout on Sending");
    } else if (ret == ESP_OK) {
        ESP_LOGI("TESTE", "Data sent.");
    } else {
        ESP_LOGE("TESTE", "Another problem");
    }

    return ret;
}