

// GENERAL INCLUDE LIBRARIES

// C Lib Include Section
#include <stdio.h>
#include <string.h>
#include <sys/param.h>

// FreeRTOS Lib Include Section
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"

// Esp Basis Lib Include Section
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "esp_netif.h"
#include "esp_err.h"

// Externel Lib Include Section 
#include "nvs_flash.h"



// GENERAL DEFINES 

#define STATUS_OK                       0
#define STATUS_FAIL                     -1
#define WIFI_MSG_TAG                    "WiFI : "
#define SOCKET_MSG_TAG                  "SOCKET : "


