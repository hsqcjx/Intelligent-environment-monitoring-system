/*
 * tcp_client.c
 */


#include "tcp_client.h"
#include "console_queue.h"


#define NoData      0
#define GetWeather  1
#define GetTIme     2
static char GetDataState=0;

#define TCP_BUF_LEN		512
static u8 tcp_rev_buff[TCP_BUF_LEN];
static u16 rev_data_len;
struct espconn user_tcp_conn;

struct espconn TcpClient_conn_init;

struct espconn *TcpClient_conn;


struct espconn *pespconn;

extern AllFlag_t *AllFlag;



/*
 * function:tcp_client_discon_cb
 */
static void ICACHE_FLASH_ATTR
tcp_client_discon_cb(void *arg) {
	AllFlag->ConnectSever=Error;
	printf("tcp_client_discon_cb\n");
}

/*
 * function: tcp_client_recv
 */
static void ICACHE_FLASH_ATTR
tcp_client_recv(void *arg, char *pdata, unsigned short len) {
	printf("tcp_client_recv\n");
	printf("lenth:%d\r\n", len);
	printf("data:%s\r\n", pdata);
	// TODO:
#if 0
	os_memset(tcp_rev_buff, 0, TCP_BUF_LEN);
	memcpy(tcp_rev_buff, pdata, len);
	rev_data_len = len;
#endif

}

/*
 * function: tcp_client_connect_cb
 */
static void ICACHE_FLASH_ATTR
tcp_client_connect_cb(void *arg) {
	TcpClient_conn = arg;

	espconn_regist_disconcb(TcpClient_conn, tcp_client_discon_cb);
	espconn_regist_recvcb(TcpClient_conn, tcp_client_recv);
	//espconn_regist_reconcb(pesp_conn, tcp_client_recon_cb);

	printf("tcp_client_connect_cb\r\n");

	u8 *hello = "Hello World!";
	AllFlag->ConnectSever=Success;

	espconn_send(TcpClient_conn, hello, strlen(hello));

}




#include "string.h"
//成功接收到服务器返回数据函数
void ICACHE_FLASH_ATTR user_tcp_recv_cb(void *arg, char *pdata,
	unsigned short len) {
	printf("\r\n ----- start receiver data----- \r\n ");
	AllFlag->GetStart=Success;   //获取数据成功
	pdata=strstr(pdata,"sysTime1");
	pdata=strstr(pdata,":");
	pdata+=2;
	uart0_tx_buffer(pdata, strlen(pdata));
	printf("\r\n -----end receiver data-----  \r\n ");
	
}

	
//断开服务器成功的回调函数
void ICACHE_FLASH_ATTR user_tcp_discon_cb(void *arg) {
	uart0_sendStr("断开连接成功！\r\n ");
}

//连接失败的回调函数，err为错误代码
void ICACHE_FLASH_ATTR user_tcp_recon_cb(void *arg, sint8 err) {
	printf("连接错误，错误代码为%d\r\n", err);
//	espconn_connect((struct espconn *) arg);
}

//成功连接到服务器的回调函数
void ICACHE_FLASH_ATTR user_tcp_connect_cb(void *arg) {
	pespconn = arg;
	espconn_regist_recvcb(pespconn, user_tcp_recv_cb);
	espconn_regist_disconcb(pespconn, user_tcp_discon_cb);

	uart0_sendStr("\r\n ----- request data start----- \r\n");
	uart0_tx_buffer(buffer, strlen(buffer));
	uart0_sendStr("\r\n -----request data end-----  \r\n");

	espconn_sent(pespconn, buffer, strlen(buffer));

}
void ICACHE_FLASH_ATTR my_station_init(struct ip_addr *remote_ip,
		struct ip_addr *local_ip, int remote_port) {
	uint8 ret=0;
	printf("my_station_init\n");
	//配置
	user_tcp_conn.type = ESPCONN_TCP;
	user_tcp_conn.state = ESPCONN_NONE;
	user_tcp_conn.proto.tcp = (esp_tcp *) os_zalloc(sizeof(esp_tcp));
	memcpy(user_tcp_conn.proto.tcp->local_ip, local_ip, 4);
	memcpy(user_tcp_conn.proto.tcp->remote_ip, remote_ip, 4);
	user_tcp_conn.proto.tcp->local_port = espconn_port();
	user_tcp_conn.proto.tcp->remote_port = remote_port;
	//注册
	printf("register callback function\n");
	espconn_regist_connectcb(&user_tcp_conn, user_tcp_connect_cb);
	espconn_regist_reconcb(&user_tcp_conn, user_tcp_recon_cb);
	//连接服务器
	printf("link sever\n");
	printf("connect to "IPSTR":%d \r\n",
			IP2STR(user_tcp_conn.proto.tcp->remote_ip),
			user_tcp_conn.proto.tcp->remote_port);
	ret=espconn_connect(&user_tcp_conn);
	if(ret==0)
	{
		printf("link sever success\n");
	}
}
/*
 * function: tcp_client_init
 * parameter: u8* ip - server ip
 *            u16 port - server port
 */
void ICACHE_FLASH_ATTR
tcp_client_init(u8* ip, u16 port) {
	static esp_tcp esptcp;
	u32 u32_ip = ipaddr_addr(ip);
	s8 rc = 0;
	
	espconn_disconnect(pespconn); //确保之前的连接断开
	espconn_disconnect(TcpClient_conn); //确保之前的连接断开
	printf("tcp_client_init\n");

	TcpClient_conn_init.type = ESPCONN_TCP;
	TcpClient_conn_init.state = ESPCONN_NONE;
	TcpClient_conn_init.proto.tcp = (esp_tcp *) os_zalloc(sizeof(esp_tcp));

	memcpy(TcpClient_conn_init.proto.tcp->remote_ip, &u32_ip, 4);//set server ip
	TcpClient_conn_init.proto.tcp->remote_port = port;			//set server port
	TcpClient_conn_init.proto.tcp->local_port = espconn_port();

	espconn_regist_connectcb(&TcpClient_conn_init, tcp_client_connect_cb);


	rc = espconn_connect(&TcpClient_conn_init);

	printf("connect to "IPSTR":%d rc=%d\r\n",
			IP2STR(TcpClient_conn_init.proto.tcp->remote_ip),
			TcpClient_conn_init.proto.tcp->remote_port, rc);

}












