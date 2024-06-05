
#include "Socket_Defns.h"

char recv_data_buffer[10] ;
static int msg_status_int = 0;
static int family_addr_int = 0; 
static int ip_protocol_int = 0; 
static int socket_status_int = 0;
static uint8_t socket_conn_try = 0;
static char host_ip_addr_array[] = SOCKET_HOST_IP_ADDR;

uint8_t Socket_Connection_Hand(void){


    struct sockaddr_in host_info_struct;
    host_info_struct.sin_addr.s_addr = inet_addr(host_ip_addr_array);
    host_info_struct.sin_family = AF_INET;
    host_info_struct.sin_port = htons(SOCKET_HOST_PORT);
    family_addr_int = AF_INET;
    ip_protocol_int = IPPROTO_IP;

    socket_status_int = socket(family_addr_int, SOCK_STREAM, ip_protocol_int);

    ESP_LOGI(SOCKET_MSG_TAG, "Socket created, connecting to %s:%d", host_ip_addr_array, SOCKET_HOST_PORT);


    while(socket_conn_try < SOCKET_CONN_MAX_RETRY){

        int conn_status_int = connect(socket_status_int, (struct sockaddr*) &host_info_struct, sizeof(struct sockaddr_in6));

        if (conn_status_int != STATUS_OK){
            ESP_LOGE(SOCKET_MSG_TAG, "Socket unable to connect: errno %d", errno);
            socket_conn_try++ ;
        }
        
        else{
            ESP_LOGI(SOCKET_MSG_TAG, "Successfully connected");
            socket_conn_try = 0;
            break;
        }
    }

    return STATUS_OK;
}

uint8_t Socket_Dissconnection_Hand(void){

    shutdown(socket_status_int, 0);
    close(socket_status_int);

    return STATUS_OK;

}


uint16_t Socket_Message_Sender_Hand(void *data_start_addr, size_t data_size, int flag){

    msg_status_int = send(socket_status_int, data_start_addr, data_size,flag);

    ESP_LOGE(SOCKET_MSG_TAG, "MESSAGE SEND TRIED ");

    if(msg_status_int < STATUS_OK){
        
        ESP_LOGE(SOCKET_MSG_TAG, "Error occurred during sending: errno %d", errno);
        return msg_status_int;
    }

    ESP_LOGE(SOCKET_MSG_TAG, "MESSAGE SENDED ");

    return msg_status_int;
}


char *Socket_Message_Recv_Hand(){

  int is_recv_succes = recv(socket_status_int, recv_data_buffer, sizeof(recv_data_buffer)  - 1, 0);

  ESP_LOGE(SOCKET_MSG_TAG, "Recv Msg accepted ");

  if (is_recv_succes < 0) {
    ESP_LOGE(SOCKET_MSG_TAG, "Recv msg failed: errno %d", errno);
  }

  else {
    ESP_LOGI(SOCKET_MSG_TAG, "Received %d bytes from %s:", is_recv_succes, host_ip_addr_array);
      
  }

  return recv_data_buffer;
}