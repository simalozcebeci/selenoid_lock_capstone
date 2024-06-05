#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "sdkconfig.h"

static const char *TAG = "example";

#define BLINK_GPIO 27
#define CONFIG_BLINK_PERIOD 50000
void s_on(void);
void s_off(void);
void configure_led(void);