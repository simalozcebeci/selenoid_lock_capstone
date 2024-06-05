#include "blinklet.h"

void s_on(void)
{
    /* Set the GPIO level according to the state (LOW or HIGH)*/
    gpio_set_level(BLINK_GPIO, 1);
    ESP_LOGE("Open Tag", "Pin On High");
    
}
void s_off(void)
{
    /* Set the GPIO level according to the state (LOW or HIGH)*/
    gpio_set_level(BLINK_GPIO, 0);
    ESP_LOGE("Open Tag", "Pin On Low");
    ESP_LOGE("Open Tag","false state");
    
}
void configure_led(void)
{
    ESP_LOGI(TAG, "Example configured to blink GPIO LED!");
    gpio_reset_pin(BLINK_GPIO);
    /* Set the GPIO as a push/pull output */
    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);

    gpio_pulldown_en(BLINK_GPIO);
}

