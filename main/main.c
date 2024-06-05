
#include "blinklet.h"
#include "WiFi_Defns.h"
#include "Socket_Defns.h"

char*  recv_data;
static bool data_recieved = 1;
static char *end_message = "END";
char *Init_Msg = "INIT_DRLOCK" ;
uint8_t init_msg_length = 11 ;


void app_main(void){

    esp_err_t nsv_return = nvs_flash_init();

    if (nsv_return == ESP_ERR_NVS_NO_FREE_PAGES || nsv_return == ESP_ERR_NVS_NEW_VERSION_FOUND) {
      ESP_ERROR_CHECK(nvs_flash_erase());
      nsv_return = nvs_flash_init();
    }
    ESP_ERROR_CHECK(nsv_return);
    
    WiFi_Init_Sta();

    Socket_Connection_Hand();

    configure_led();

    Socket_Message_Sender_Hand(Init_Msg, init_msg_length, 1);
    while (true){
        ESP_LOGE("MAIN LOOP","ONLOOP");
      
        recv_data = Socket_Message_Recv_Hand();
        data_recieved = (bool)(((int) *recv_data) - 48);

       if(data_recieved == true){
        s_on();//kilitli
        ESP_LOGE("Open Tag","next state");
        }
        else{
            s_off();//kilit acik
    }
    }


    // xTaskCreate(Tcp_Client_Task, "tcp_client", 4096, NULL, 5, NULL);




}
