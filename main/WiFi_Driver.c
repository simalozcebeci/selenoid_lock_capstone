

#include "WiFi_Defns.h"

static EventGroupHandle_t wifi_event_group_s;
static u_int16_t retry_count_s_uint = 0;

void WiFi_IP_Event_Handler(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data){


    if ( event_base == WIFI_EVENT){

        if( event_id == WIFI_EVENT_STA_START ){
            esp_wifi_connect();
        }

        else if( event_id == WIFI_EVENT_STA_DISCONNECTED ){

            if(retry_count_s_uint < WIFI_MAX_RETRY){
                esp_wifi_connect();
                retry_count_s_uint++;
            }

            else{
                xEventGroupSetBits(wifi_event_group_s,WIFI_FAIL_BIT);
            }
        }
    }

    else if (event_base == IP_EVENT){

        if (event_id == IP_EVENT_STA_GOT_IP){
            
            ip_event_got_ip_t* ip_event = (ip_event_got_ip_t*) event_data;
            
            xEventGroupSetBits(wifi_event_group_s, WIFI_CONNECTED_BIT);
        }
    }
}


void WiFi_Init_Sta(void){
    
    wifi_event_group_s = xEventGroupCreate();

    ESP_ERROR_CHECK(esp_netif_init());

    ESP_ERROR_CHECK(esp_event_loop_create_default());

    esp_netif_create_default_wifi_sta();

    wifi_init_config_t wifi_init_config = WIFI_INIT_CONFIG_DEFAULT();

    ESP_ERROR_CHECK(esp_wifi_init(&wifi_init_config));

    esp_event_handler_instance_t instance_any_id_event;
    esp_event_handler_instance_t instance_got_id_event;

    ESP_ERROR_CHECK(
        esp_event_handler_instance_register(
            WIFI_EVENT,
            ESP_EVENT_ANY_ID,
            &WiFi_IP_Event_Handler,
            NULL,
            &instance_any_id_event
        )
    );

    ESP_ERROR_CHECK(
        esp_event_handler_instance_register(
            IP_EVENT,
            IP_EVENT_STA_GOT_IP,
            &WiFi_IP_Event_Handler,
            NULL,
            &instance_got_id_event
        )
    );

    wifi_config_t wifi_config = {
        .sta = {
            .ssid = WIFI_SSID,
            .password = WIFI_PASS,
            .threshold.authmode = WIFI_AUTH_MODE_TRESH,
            .sae_pwe_h2e = WPA3_SAE_PWE_BOTH,
        },
    };

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));

    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config ));

    ESP_ERROR_CHECK(esp_wifi_start());

    EventBits_t evet_return_bit = xEventGroupWaitBits(
        wifi_event_group_s,
        WIFI_CONNECTED_BIT | WIFI_FAIL_BIT,
        pdFALSE,
        pdFALSE,
        portMAX_DELAY
        );

    if (evet_return_bit & WIFI_CONNECTED_BIT) {
    
        ESP_LOGI(
            WIFI_MSG_TAG, "connected to ap SSID:%s password:%s",
            WIFI_SSID, WIFI_PASS
        );
    } 
    
    else if (evet_return_bit & WIFI_FAIL_BIT) {
        ESP_LOGI(
            WIFI_MSG_TAG, "Failed to connect to SSID:%s, password:%s",
            WIFI_SSID, WIFI_PASS
        );
    } 
    
    else {
        ESP_LOGE(WIFI_MSG_TAG, "UNEXPECTED EVENT");
    }

}