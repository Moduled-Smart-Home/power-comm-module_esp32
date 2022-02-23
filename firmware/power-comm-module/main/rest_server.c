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
#include "mdns.h"

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

typedef struct rest_server_context {
    char base_path[ESP_VFS_PATH_MAX + 1];
    char scratch[SCRATCH_BUFSIZE];
} rest_server_context_t;

#define CHECK_FILE_EXTENSION(filename, ext) (strcasecmp(&filename[strlen(filename) - strlen(ext)], ext) == 0)

/* Set HTTP response content type according to file extension */
static esp_err_t set_content_type_from_file(httpd_req_t *req, const char *filepath)
{
    const char *type = "text/plain";
    if (CHECK_FILE_EXTENSION(filepath, ".html")) {
        type = "text/html";
    } else if (CHECK_FILE_EXTENSION(filepath, ".js")) {
        type = "application/javascript";
    } else if (CHECK_FILE_EXTENSION(filepath, ".css")) {
        type = "text/css";
    } else if (CHECK_FILE_EXTENSION(filepath, ".png")) {
        type = "image/png";
    } else if (CHECK_FILE_EXTENSION(filepath, ".ico")) {
        type = "image/x-icon";
    } else if (CHECK_FILE_EXTENSION(filepath, ".svg")) {
        type = "text/xml";
    }
    return httpd_resp_set_type(req, type);
}

/* handler for lamp control */
static esp_err_t lamp_on_off_post_handler(httpd_req_t *req)
{
    int total_len = req->content_len;
    int cur_len = 0;
    char *buf = ((rest_server_context_t *)(req->user_ctx))->scratch;
    int received = 0;
    char *stateTxt;
    if (total_len >= SCRATCH_BUFSIZE) {
        /* Respond with 500 Internal Server Error */
        httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "content too long");
        return ESP_FAIL;
    }
    while (cur_len < total_len) {
        received = httpd_req_recv(req, buf + cur_len, total_len);
        if (received <= 0) {
            /* Respond with 500 Internal Server Error */
            httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "Failed to post control value");
            return ESP_FAIL;
        }
        cur_len += received;
    }
    buf[total_len] = '\0';

    cJSON *root = cJSON_Parse(buf);
    int state = cJSON_GetObjectItem(root, "state")->valueint;

    esp_err_t ret;

    if(state ==0){
        stateTxt  = "OFF";
        ret = set_lamp_off(SLAVE_ADDRESS);
    }

    else {
        stateTxt  = "ON";
        ret = set_lamp_on(SLAVE_ADDRESS);
    }

    if (ret == ESP_OK) {
        ESP_LOGI(REST_TAG, "Lamp control: state = %s", stateTxt);
        cJSON_Delete(root);
        httpd_resp_sendstr(req, "Post control value successfully");
        return ESP_OK;
    }
    else {
        ESP_LOGE(REST_TAG, "Failed to set lamp control");
        cJSON_Delete(root);
        httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "Failed to post control value");
        return ESP_FAIL;
    }
}


/* handler for fan dir control */
static esp_err_t fan_on_dir_off_post_handler(httpd_req_t *req)
{
    int total_len = req->content_len;
    int cur_len = 0;
    char *buf = ((rest_server_context_t *)(req->user_ctx))->scratch;
    int received = 0;
    if (total_len >= SCRATCH_BUFSIZE) {
        /* Respond with 500 Internal Server Error */
        httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "content too long");
        return ESP_FAIL;
    }
    while (cur_len < total_len) {
        received = httpd_req_recv(req, buf + cur_len, total_len);
        if (received <= 0) {
            /* Respond with 500 Internal Server Error */
            httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "Failed to post control value");
            return ESP_FAIL;
        }
        cur_len += received;
    }
    buf[total_len] = '\0';

    cJSON *root = cJSON_Parse(buf);
    int state = cJSON_GetObjectItem(root, "state")->valueint;
    int dir = cJSON_GetObjectItem(root, "dir")->valueint;

    esp_err_t ret = NULL;

    if(state == 0){
        ESP_LOGI(REST_TAG, "Fan control: state = OFF");
        ret = set_fan_off(SLAVE_ADDRESS);
    }

    else if(state == 1) {
        ESP_LOGI(REST_TAG, "Fan control: state = ON; Direction: %d", dir);
        ret = set_fan_on(SLAVE_ADDRESS, dir);
    }

    if (ret == ESP_OK) {
        cJSON_Delete(root);
        httpd_resp_sendstr(req, "Post control value successfully");
            return ESP_OK;
    }
    else {
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
    if (total_len >= SCRATCH_BUFSIZE) {
        /* Respond with 500 Internal Server Error */
        httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "content too long");
        return ESP_FAIL;
    }
    while (cur_len < total_len) {
        received = httpd_req_recv(req, buf + cur_len, total_len);
        if (received <= 0) {
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

    if (ret == ESP_OK) {
        cJSON_Delete(root);
        httpd_resp_sendstr(req, "Post control value successfully");
        return ESP_OK;
    }
    else {
        ESP_LOGE(REST_TAG, "Failed to set fan power");
        cJSON_Delete(root);
        httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "Failed to post control value");
        return ESP_FAIL;
    }
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

    /* URI handler for fetching system info */
   
    /* URI handler for lamp control */
    httpd_uri_t lamp_on_off_post_uri = {
        .uri = "/api/lamp_control",
        .method = HTTP_POST,
        .handler = lamp_on_off_post_handler,
        .user_ctx = rest_context
    };
    httpd_register_uri_handler(server, &lamp_on_off_post_uri);

    /* URI handler for fan control */
    httpd_uri_t fan_on_dir_off_post_uri = {
        .uri = "/api/fan_control",
        .method = HTTP_POST,
        .handler = fan_on_dir_off_post_handler,
        .user_ctx = rest_context
    };
    httpd_register_uri_handler(server, &fan_on_dir_off_post_uri);

    /* URI handler for fan_pow control */
    httpd_uri_t fan_pow_post_uri = {
        .uri = "/api/fan_power",
        .method = HTTP_POST,
        .handler = fan_pow_post_handler,
        .user_ctx = rest_context
    };
    httpd_register_uri_handler(server, &fan_pow_post_uri);

    return ESP_OK;
err_start:
    free(rest_context);
err:
    return ESP_FAIL;
}
