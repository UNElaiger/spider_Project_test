#ifndef ESP_01_H
#define ESP_01_H
#define DEBUG 1 
#define restart       "AT+RST\r\n"      //Restart module
#include <stdint.h>
extern const char at_test[];
extern const char echoOff[];      //6 disable repetition of entered commands
extern const char restore[];      //Restore factory default settings
extern const char uart_baud[];    //Baudrate range
extern const char uartFastbaud[]; //Baudrate range//921600
extern const char station_mode[]; //station mode
extern const char conect_to_AP [];
//const char conect_to_AP [] =  "AT+CWJAP=\"360WiFi\",\"amkhalyawa\"\r\n";
extern const char disconectAP [];
extern const char conect_AP_status[];
extern const char NoMultConn[];
extern const char rst [];
extern const char get_IP [];
extern const char conn_TCP [];
extern const char send_TSP [];
extern const char getStream [];
extern const char show_mac [];
extern const char info[];
void start_ap_server(void);
void esp_01_ini(void);
void clear_rx_buf(void);
void esp_01_usart_setup(uint32_t baud);
void usart_recive_str(char* str);
void usart1_send_string(const char* str);
#endif
