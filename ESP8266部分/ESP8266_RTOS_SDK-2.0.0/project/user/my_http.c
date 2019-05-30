/*
 * my_http.c
 *
 *  Created on: 2015年7月24日
 *      Author: Administrator
 */
#include "my_http.h"
#include "string.h"

#include "tcp_client.h"
#include "lwip/lwip/ip_addr.h"
#include "uart.h"
#include "espressif/esp8266/ets_sys.h"
#include "espressif/esp_system.h"
#include "espressif/esp_libc.h"
#include "espressif/esp_sta.h"
#include "espressif/c_types.h"
#include "espressif/esp_misc.h"
#include "tcp_client.h"
#include "user_config.h"




//外部声明变量
extern struct espconn *pespconn;
extern AllFlag_t *AllFlag;


//剖析URL
void ICACHE_FLASH_ATTR http_parse_request_url(char *URL, char *host,char *filename, unsigned short *port) {


	char *PA;
	char *PB;

	memset(host, 0, sizeof(host));
	memset(filename, 0, sizeof(filename));

	*port = 0;

	if (!(*URL)){                             //鍒ゆ柇浼犲叆鍙傛暟鏄惁鏄疷RL
		printf("\r\n ----- URL return -----  \r\n");
		return;
	}

	PA = URL;

	if (!strncmp(PA, "http://", strlen("http://"))) {        //鍒ゆ柇鏄痟ttp鍗忚杩樻槸https鍗忚
		PA = URL + strlen("http://");
	} else if (!strncmp(PA, "https://", strlen("https://"))) {
		PA = URL + strlen("https://");
	}

	PB = strchr(PA, '/');     //瀵绘壘host鍦板潃缁撴潫浣嶇疆

	if (PB) {
		printf("\r\n ----- PB=true -----  \r\n");
		memcpy(host, PA, strlen(PA) - strlen(PB));       //鑾峰彇涓绘満缃戝潃
		if (PB + 1) {
			memcpy(filename, PB + 1, strlen(PB - 1));    //鑾峰彇璇锋眰鍙傛暟
			filename[strlen(PB) - 1] = 0;
		}
		host[strlen(PA) - strlen(PB)] = 0;

		printf(host,strlen(host));

	} else {
		printf("\r\n ----- PB=false -----  \r\n");
		memcpy(host, PA, strlen(PA));
		host[strlen(PA)] = 0;
		printf(host,strlen(host));
	}

	PA = strchr(host, ':');

	if (PA){
		*port = atoi(PA + 1);
	}else{
		*port = 80;
	}
}

//寻找DNS解析，并且配置
void ICACHE_FLASH_ATTR user_esp_dns_found(const char *name, ip_addr_t *ipaddr,void *arg) {

	struct ip_info info;
	wifi_get_ip_info(STATION_IF, &info);
	my_station_init(ipaddr, &info.ip, port);

}

//定义Get请求的实现
void ICACHE_FLASH_ATTR startHttpQuestByGET(char *URL){
	struct ip_addr addr;
	espconn_disconnect(pespconn); //确保之前的连接已经断开
	espconn_delete(pespconn);
	AllFlag->GetStart=Error;
	memset(buffer,0,1024);
	http_parse_request_url(URL,host,filename,&port);
	sprintf(buffer,GET,filename,host);
	espconn_gethostbyname(&user_tcp_conn,host, &addr,
	user_esp_dns_found);
}


//定义Post请求的实现
void ICACHE_FLASH_ATTR startHttpQuestByPOST(char *URL,char *method,char *postdata){
	struct ip_addr addr;
	memset(buffer,0,1024);
	espconn_disconnect(pespconn); 
	espconn_delete(pespconn);
	AllFlag->GetStart=Error;
	http_parse_request_url(URL,host,filename,&port);
	sprintf(buffer,POST,filename,strlen(postdata),host,postdata);
	espconn_gethostbyname(&user_tcp_conn,host, &addr,
	user_esp_dns_found);
}












