/* HTTP Restful API Server

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <string.h>
#include <fcntl.h>
#include "esp_http_server.h"
#include "esp_system.h"
#include "esp_log.h"
#include "esp_vfs.h"
#include "cJSON.h"
#include "ota.c"
#include "esp_ota_ops.h"
#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"

#include "i2c_commands.h"

#define SLAVE_ADDRESS CONFIG_SLAVE_ADDRESS

static const char *REST_TAG = "esp-rest";
#define REST_CHECK(a, str, goto_tag, ...)                                              \
    do                                                                                 \
    {                                                                                  \
        if (!(a))                                                                      \
        {                                                                              \
            ESP_LOGE(REST_TAG, "%s(%d): " str, __FUNCTION__, __LINE__, ##__VA_ARGS__); \
            goto goto_tag;                                                             \
        }                                                                              \
    } while (0)

#define FILE_PATH_MAX (ESP_VFS_PATH_MAX + 128)
#define SCRATCH_BUFSIZE (10240)

typedef struct rest_server_context
{
    char base_path[ESP_VFS_PATH_MAX + 1];
    char scratch[SCRATCH_BUFSIZE];
} rest_server_context_t;

static esp_err_t read_req_content(httpd_req_t *req, char **content) {
    int total_len = req->content_len;
    int cur_len = 0;
    char *buf = ((rest_server_context_t *)(req->user_ctx))->scratch;
    int received = 0;
    if (total_len >= SCRATCH_BUFSIZE)
    {
        /* Respond with 500 Internal Server Error */
        httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "content too long");
        return ESP_FAIL;
    }
    while (cur_len < total_len)
    {
        received = httpd_req_recv(req, buf + cur_len, total_len);
        if (received <= 0)
        {
            /* Respond with 500 Internal Server Error */
            httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "Failed to post control value");
            return ESP_FAIL;
        }
        cur_len += received;
    }
    buf[total_len] = '\0';
    *content = buf;
    return ESP_OK;
}

#define CHECK_FILE_EXTENSION(filename, ext) (strcasecmp(&filename[strlen(filename) - strlen(ext)], ext) == 0)

/* Set HTTP response content type according to file extension */
static esp_err_t set_content_type_from_file(httpd_req_t *req, const char *filepath)
{
    const char *type = "text/plain";
    if (CHECK_FILE_EXTENSION(filepath, ".html"))
    {
        type = "text/html";
    }
    else if (CHECK_FILE_EXTENSION(filepath, ".js"))
    {
        type = "application/javascript";
    }
    else if (CHECK_FILE_EXTENSION(filepath, ".css"))
    {
        type = "text/css";
    }
    else if (CHECK_FILE_EXTENSION(filepath, ".png"))
    {
        type = "image/png";
    }
    else if (CHECK_FILE_EXTENSION(filepath, ".ico"))
    {
        type = "image/x-icon";
    }
    else if (CHECK_FILE_EXTENSION(filepath, ".svg"))
    {
        type = "text/xml";
    }
    return httpd_resp_set_type(req, type);
}

/* Send HTTP response with the contents of the requested file */
static esp_err_t rest_common_get_handler(httpd_req_t *req)
{
    char filepath[FILE_PATH_MAX];

    rest_server_context_t *rest_context = (rest_server_context_t *)req->user_ctx;
    strlcpy(filepath, rest_context->base_path, sizeof(filepath));
    if (req->uri[strlen(req->uri) - 1] == '/')
    {
        strlcat(filepath, "/index.html", sizeof(filepath));
    }
    else
    {
        strlcat(filepath, req->uri, sizeof(filepath));
    }
    int fd = open(filepath, O_RDONLY, 0);
    if (fd == -1)
    {
        ESP_LOGE(REST_TAG, "Failed to open file : %s", filepath);
        /* Respond with 500 Internal Server Error */
        httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "Failed to read existing file");
        return ESP_FAIL;
    }

    set_content_type_from_file(req, filepath);

    char *chunk = rest_context->scratch;
    ssize_t read_bytes;
    do
    {
        /* Read file in chunks into the scratch buffer */
        read_bytes = read(fd, chunk, SCRATCH_BUFSIZE);
        if (read_bytes == -1)
        {
            ESP_LOGE(REST_TAG, "Failed to read file : %s", filepath);
        }
        else if (read_bytes > 0)
        {
            /* Send the buffer contents as HTTP response chunk */
            if (httpd_resp_send_chunk(req, chunk, read_bytes) != ESP_OK)
            {
                close(fd);
                ESP_LOGE(REST_TAG, "File sending failed!");
                /* Abort sending file */
                httpd_resp_sendstr_chunk(req, NULL);
                /* Respond with 500 Internal Server Error */
                httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "Failed to send file");
                return ESP_FAIL;
            }
        }
    } while (read_bytes > 0);
    /* Close file after sending complete */
    close(fd);
    ESP_LOGI(REST_TAG, "File sending complete");
    /* Respond with an empty chunk to signal HTTP response completion */
    httpd_resp_send_chunk(req, NULL, 0);
    return ESP_OK;
}

/* handler for lamp control */
static esp_err_t lamp_on_off_post_handler(httpd_req_t *req)
{
    char *content;
    if(read_req_content(req, &content) != ESP_OK){
        return ESP_FAIL;
    }

    cJSON *root = cJSON_Parse(content);
    int state = cJSON_GetObjectItem(root, "state")->valueint;

    char *stateTxt;

    esp_err_t ret;
    if (state == 0)
    {
        stateTxt = "OFF";
        ret = set_lamp_off(SLAVE_ADDRESS);
    }

    else
    {
        stateTxt = "ON";
        ret = set_lamp_on(SLAVE_ADDRESS);
    }

    if (ret == ESP_OK)
    {
        ESP_LOGI(REST_TAG, "Lamp control: state = %s", stateTxt);
        cJSON_Delete(root);
        httpd_resp_sendstr(req, "Post control value successfully");
        return ESP_OK;
    }
    else
    {
        ESP_LOGE(REST_TAG, "Failed to set lamp control");
        cJSON_Delete(root);
        httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "Failed to post control value");
        return ESP_FAIL;
    }
}

/* handler for fan dir control */
static esp_err_t fan_on_dir_off_post_handler(httpd_req_t *req)
{
    char *content;
    if(read_req_content(req, &content) != ESP_OK){
        return ESP_FAIL;
    }

    cJSON *root = cJSON_Parse(content);
    int state = cJSON_GetObjectItem(root, "state")->valueint;
    int dir = cJSON_GetObjectItem(root, "dir")->valueint;

    esp_err_t ret = NULL;

    if (state == 0)
    {
        ESP_LOGI(REST_TAG, "Fan control: state = OFF");
        ret = set_fan_off(SLAVE_ADDRESS);
    }

    else if (state == 1)
    {
        ESP_LOGI(REST_TAG, "Fan control: state = ON; Direction: %d", dir);
        ret = set_fan_on(SLAVE_ADDRESS, dir);
    }

    if (ret == ESP_OK)
    {
        cJSON_Delete(root);
        httpd_resp_sendstr(req, "Post control value successfully");
        return ESP_OK;
    }
    else
    {
        ESP_LOGE(REST_TAG, "Failed to set fan control");
        cJSON_Delete(root);
        httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "Failed to post control value");
        return ESP_FAIL;
    }
}

static esp_err_t fan_pow_post_handler(httpd_req_t *req)
{
    int total_len = req->content_len;
    int cur_len = 0;
    char *buf = ((rest_server_context_t *)(req->user_ctx))->scratch;
    int received = 0;
    if (total_len >= SCRATCH_BUFSIZE)
    {
        /* Respond with 500 Internal Server Error */
        httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "content too long");
        return ESP_FAIL;
    }
    while (cur_len < total_len)
    {
        received = httpd_req_recv(req, buf + cur_len, total_len);
        if (received <= 0)
        {
            /* Respond with 500 Internal Server Error */
            httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "Failed to post control value");
            return ESP_FAIL;
        }
        cur_len += received;
    }
    buf[total_len] = '\0';

    cJSON *root = cJSON_Parse(buf);
    int power = cJSON_GetObjectItem(root, "power")->valueint;

    ESP_LOGI(REST_TAG, "Setting Fan Power to: %d", power);

    esp_err_t ret;

    ret = set_fan_power(SLAVE_ADDRESS, power);

    if (ret == ESP_OK)
    {
        cJSON_Delete(root);
        httpd_resp_sendstr(req, "Post control value successfully");
        return ESP_OK;
    }
    else
    {
        ESP_LOGE(REST_TAG, "Failed to set fan power");
        cJSON_Delete(root);
        httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "Failed to post control value");
        return ESP_FAIL;
    }
}

static void vTimerCallback(TimerHandle_t pxTimer)
{
    ESP_LOGI(REST_TAG, "Restarting ESP...");
    esp_restart();
}

static esp_err_t ota_post_handler(httpd_req_t *req)
{
    esp_err_t ret = ota_update();
    if (ret == ESP_OK)
    {
        httpd_resp_sendstr(req, "Firmware upgraded!");

        TimerHandle_t timer = xTimerCreate("Timer_to_restart", (5000 / portTICK_PERIOD_MS), pdFALSE, "timer1", vTimerCallback);

        if (timer == NULL)
        {
            ESP_LOGI(REST_TAG, "Timer for restart NOT created");
        }
        else
        {
            xTimerStart(timer, 0);
        }
        return ESP_OK;
    }
    else
    {
        httpd_resp_sendstr(req, "Something gets wrong during firmware upgrading!");
        return ESP_FAIL;
    }
}

static esp_err_t ota_rollback_handler(httpd_req_t *req)
{
    httpd_resp_sendstr(req, "Rolling back and rebooting!");
    esp_ota_mark_app_invalid_rollback_and_reboot();
    return ESP_OK;
}

static esp_err_t handshake_get_handler(httpd_req_t *req)
{
    //checking token
    char* valid_token_test = "test123";
    char* header_name = "token";
    size_t header_size = httpd_req_get_hdr_value_len(req, header_name) +1;
    char token_received[header_size];
    httpd_req_get_hdr_value_str(req, header_name, token_received, header_size);

    ESP_LOGI("DEBUG", "Token Received: %s", token_received);

    if(strcmp(token_received, valid_token_test) == 0) {
        ESP_LOGI("DEBUG", "Token is Valid");
        httpd_resp_sendstr(req, "ACK");
        return ESP_OK;
    } else {
        ESP_LOGI("DEBUG", "Token is Invalid");
        httpd_resp_sendstr(req, "INVALID_TOKEN");
        return ESP_OK;
    }

}

static esp_err_t app_version_get_handler(httpd_req_t *req)
{
    httpd_resp_sendstr(req, esp_ota_get_app_description()->version);
    return ESP_OK;
}

esp_err_t start_rest_server(const char *base_path)
{

    REST_CHECK(base_path, "wrong base path", err);
    rest_server_context_t *rest_context = calloc(1, sizeof(rest_server_context_t));
    REST_CHECK(rest_context, "No memory for rest context", err);
    strlcpy(rest_context->base_path, base_path, sizeof(rest_context->base_path));

    httpd_handle_t server = NULL;
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    config.uri_match_fn = httpd_uri_match_wildcard;

    ESP_LOGI(REST_TAG, "Starting HTTP Server");
    REST_CHECK(httpd_start(&server, &config) == ESP_OK, "Start server failed", err_start);

    /* URI handler for lamp control */
    httpd_uri_t handshake_get_uri = {
        .uri = "/api/handshake",
        .method = HTTP_GET,
        .handler = handshake_get_handler,
        .user_ctx = rest_context};
    httpd_register_uri_handler(server, &handshake_get_uri);

    /* URI handler for lamp control */
    httpd_uri_t lamp_on_off_post_uri = {
        .uri = "/api/lamp_control",
        .method = HTTP_POST,
        .handler = lamp_on_off_post_handler,
        .user_ctx = rest_context};
    httpd_register_uri_handler(server, &lamp_on_off_post_uri);

    /* URI handler for fan control */
    httpd_uri_t fan_on_dir_off_post_uri = {
        .uri = "/api/fan_control",
        .method = HTTP_POST,
        .handler = fan_on_dir_off_post_handler,
        .user_ctx = rest_context};
    httpd_register_uri_handler(server, &fan_on_dir_off_post_uri);

    /* URI handler for fan_pow control */
    httpd_uri_t fan_pow_post_uri = {
        .uri = "/api/fan_power",
        .method = HTTP_POST,
        .handler = fan_pow_post_handler,
        .user_ctx = rest_context};
    httpd_register_uri_handler(server, &fan_pow_post_uri);

    /* URI handler for OTA Update */
    httpd_uri_t ota_post_uri = {
        .uri = "/api/upgrade_firmware",
        .method = HTTP_POST,
        .handler = ota_post_handler,
        .user_ctx = rest_context};
    httpd_register_uri_handler(server, &ota_post_uri);

    /* URI handler for OTA Rollback */
    httpd_uri_t ota_rollback_uri = {
        .uri = "/api/firmware_rollback",
        .method = HTTP_POST,
        .handler = ota_rollback_handler,
        .user_ctx = rest_context};
    httpd_register_uri_handler(server, &ota_rollback_uri);

    /* URI handler for get App Version */
    httpd_uri_t app_version_get_uri = {
        .uri = "/api/app_version",
        .method = HTTP_GET,
        .handler = app_version_get_handler,
        .user_ctx = rest_context};
    httpd_register_uri_handler(server, &app_version_get_uri);

    /* URI handler for getting web server files */
    httpd_uri_t common_get_uri = {
        .uri = "/*",
        .method = HTTP_GET,
        .handler = rest_common_get_handler,
        .user_ctx = rest_context};
    httpd_register_uri_handler(server, &common_get_uri);

    return ESP_OK;
err_start:
    free(rest_context);
err:
    return ESP_FAIL;
}
