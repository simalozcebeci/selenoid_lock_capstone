



// Hand Made Libraries Section
#include "General_Defns.h"

// External Libraries Section
#include "lwip/err.h"
#include "lwip/sys.h"



// WiFi Defines Section
#define WIFI_SSID                       "Kanuni sultan suleyman"
#define WIFI_PASS                       "CG//1598++8951yigit"
#define WIFI_MAX_RETRY                  5   
#define WIFI_AUTH_MODE_TRESH            WIFI_AUTH_WPA2_PSK
#define WIFI_CONNECTED_BIT              BIT0
#define WIFI_FAIL_BIT                   BIT1


// Funtion Prototyp Section 

void WiFi_IP_Event_Handler(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data);

void WiFi_Init_Sta(void);