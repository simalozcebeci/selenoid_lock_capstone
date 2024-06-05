

// Hand Made Libraries Section
#include "General_Defns.h"

// External Libraries Section
#include "protocol_examples_common.h"
#include "addr_from_stdin.h"
#include "lwip/err.h"
#include "lwip/sockets.h"


// Socket Defines Section
#define SOCKET_HOST_IP_ADDR             "192.168.1.148"   
#define SOCKET_HOST_PORT                120
#define SOCKET_CONN_MAX_RETRY           5


// Funtion Prototyp Section 
char* Socket_Message_Recv_Hand();
uint8_t Socket_Connection_Hand(void);
uint8_t Socket_Dissconnection_Hand(void);
uint16_t Socket_Message_Sender_Hand(void *data_start_addr, size_t data_size, int flag);
