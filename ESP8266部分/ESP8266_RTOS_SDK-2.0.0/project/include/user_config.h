/*
 * ESPRSSIF MIT License
 *
 * Copyright (c) 2015 <ESPRESSIF SYSTEMS (SHANGHAI) PTE LTD>
 *
 * Permission is hereby granted for use on ESPRESSIF SYSTEMS ESP8266 only, in which case,
 * it is free of charge, to any person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the Software is furnished
 * to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#ifndef __USER_CONFIG_H__
#define __USER_CONFIG_H__

#include "c_types.h"

#define AP_CACHE           0

#if AP_CACHE
#define AP_CACHE_NUMBER    5
#endif


#define WIFI_SSID 		"hsq"
#define WIFI_PASSWORD	"961110hsq"

#define HOST	"192.168.43.23"
#define PORT	8080

#define Connect 1
#define DisConnect 0
#define Success 1
#define Error 0
#define GetWeatherData 1
#define GetTimData 2
#define GetLocalData 3

typedef struct ALLFALGSTR {
    uint8 ConnectWifi;     //标志连接wifi是否成功  ，1->成功,0->失败
	uint8 ConnectSever;    //连接服务器标志位
    uint8 GetDataType;     //获取数据的类型
	uint8 GetStart;        //获取状态
} AllFlag_t;

// 是否使用SSL
#define SSL_CLIENT_ENABLE		0
#if SSL_CLIENT_ENABLE
#define SSL_CLIENT_KEY_ADDR		0x9A
#define SSL_CA_ADDR				0x9B
#endif

#endif

