/*
 * tcp_client.h
 *
 *  Created on: 2017��7��3��
 *      Author: Administrator
 */

#ifndef _TCP_CLIENT_H_
#define _TCP_CLIENT_H_


#include "lwip/lwip/ip_addr.h"
//#include "user_interface.h"

#include "uart.h"
#include "espressif/esp8266/ets_sys.h"
#include "espressif/esp_system.h"
#include "espressif/esp_libc.h"
#include "espressif/esp_sta.h"
#include "espressif/c_types.h"
#include "espressif/esp_misc.h"
#include "espressif/esp_timer.h"

#include "freertos/mpu_wrappers.h"
//#include "user_interface.h"
#include "espconn.h"

#include "tcp_client.h"
#include "user_config.h"



char buffer[1024];
#define GET "GET /%s HTTP/1.1\r\nContent-Type: text/html;charset=utf-8\r\nAccept: */*\r\nHost: %s\r\nConnection: Keep-Alive\r\n\r\n"
#define POST "POST /%s HTTP/1.1\r\nAccept: */*\r\nContent-Length: %d\r\nContent-Type: application/json\r\nHost: %s\r\nConnection: Keep-Alive\r\n\r\n%s"
extern struct espconn user_tcp_conn;
void TcpConsoleThreadInit(void);
extern void tcp_client_init(u8* ip, u16 port);
void my_station_init(struct ip_addr *remote_ip,struct ip_addr *local_ip,int remote_port);
#endif /* _TCP_CLIENT_H_ */
