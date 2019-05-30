/*
 * user_wifi.c
 */

#include "uart.h"
#include "espressif/esp8266/ets_sys.h"
#include "espressif/esp_system.h"
#include "espressif/esp_libc.h"
#include "espressif/esp_sta.h"
#include "espressif/c_types.h"
#include "espressif/esp_misc.h"
#include "tcp_client.h"
#include "user_config.h"
#include "my_http.h"


extern AllFlag_t *AllFlag;
/*
 * function: user_set_station_config
 * parameter: u8* ssid - WiFi SSID
 *            u8 password - WiFi password
 */
void ICACHE_FLASH_ATTR
user_set_station_config(u8* ssid1, u8* password1) {
	u8	ssid[32] = "yxcf2015";
	u8	password[64] = "qwertyuiop[]";
	struct station_config stationConf;
	stationConf.bssid_set = 0;		//need	not	check	MAC	address	of	AP
	memcpy(&stationConf.ssid, ssid, 32);
	memcpy(&stationConf.password, password, 64);
	wifi_station_set_config(&stationConf);
}

/*
 * function: wifi_handle_event_cb
 * parameter: System_Event_t *evt
 */
void wifi_event_handler_cb(System_Event_t *evt) {
	printf("event %x\n", evt->event_id);
//	int i=0;
	switch (evt->event_id) {
	case EVENT_STAMODE_CONNECTED:
		printf("connect to ssid %s, channel %d\n",
				evt->event_info.connected.ssid,
				evt->event_info.connected.channel);
//				printf("mac:");
//				for(i=0;i<6;i++)
//				{
//					printf("%x ",evt->event_info.connected.bssid[i]);
//				}
//				printf("\n");
		break;
	case EVENT_STAMODE_DISCONNECTED:
		printf("disconnect from ssid %s, reason %d\n",
				evt->event_info.disconnected.ssid,
				evt->event_info.disconnected.reason);
		break;
	case EVENT_STAMODE_AUTHMODE_CHANGE:
		printf("mode: %d -> %d\n", evt->event_info.auth_change.old_mode,
				evt->event_info.auth_change.new_mode);
		break;

	// 获取到IP地址吿	
	case EVENT_STAMODE_GOT_IP:
		printf("ip123:" IPSTR ",mask:" IPSTR ",gw:" IPSTR ,
				IP2STR(&evt->event_info.got_ip.ip),
				IP2STR(&evt->event_info.got_ip.mask),
				IP2STR(&evt->event_info.got_ip.gw));
				MAC2STR(&evt->event_info.connected.bssid);
		printf("\n");
		AllFlag->ConnectWifi=Success;
		break;
	case EVENT_SOFTAPMODE_STACONNECTED:
		printf("station: " MACSTR "join, AID = %d\n",
				MAC2STR(evt->event_info.sta_connected.mac),
				evt->event_info.sta_connected.aid);
		break;
	case EVENT_SOFTAPMODE_STADISCONNECTED:
		printf("station: " MACSTR "leave, AID = %d\n",
				MAC2STR(evt->event_info.sta_disconnected.mac),
				evt->event_info.sta_disconnected.aid);
		break;
	default:
		break;
	}
}

/*
 * function: user_wifi_init
 */
void ICACHE_FLASH_ATTR
user_wifi_init(void) {
	struct	station_config	config;
#if 0
	user_set_station_config(WIFI_SSID, WIFI_PASSWORD);

	wifi_set_opmode(STATION_MODE);
	wifi_station_get_config_default	(&config);
	printf("ssid=%s  password=%s\n",config.ssid,config.password);
	wifi_station_set_config(&config);

	wifi_set_event_handler_cb(wifi_handle_event_cb);
	wifi_station_connect();
#endif

	wifi_set_opmode(STATION_MODE);
	
    bzero(&config, sizeof(struct station_config));
	wifi_station_get_config(&config);
    sprintf(config.ssid, WIFI_SSID);
    sprintf(config.password, WIFI_PASSWORD);
    wifi_station_set_config(&config);

    wifi_set_event_handler_cb(wifi_event_handler_cb); 

    wifi_station_connect();
}
