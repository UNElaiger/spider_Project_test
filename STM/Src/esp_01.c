#include "esp_01.h"
#include <stdio.h> 
#include <main.h> 
const char at_test[] = "AT\r\n";
const char echoOff[] =  "ATE0\r\n";    //6 disable repetition of entered commands
const char restore [] =  "AT+RESTORE\r\n";  //Restore factory default settings
const char uart_baud [] =  "AT+UART=921600,8,1,0,0\r\n" ;//Baudrate range
const char uartFastbaud [] = "AT+UART_CUR=230400,8,1,0,0\r\n" ;//Baudrate range//921600
const char station_mode [] = "AT+CWMODE=1\r\n"; //station mode
const char conect_to_AP [] = "AT+CWJAP=\"MTS424D-8942\",\"9ifdrfrr\"\r\n";
const char disconectAP [] = "AT+ CWQAP\r\n";
const char conect_AP_status [] = "AT+CWJAP?\r\n";
const char NoMultConn[] = "AT+CIPMUX=0\r\n";
const char rst [] = "AT+RESTORE\r\n";
const char get_IP [] = "AT+CIFSR\r\n";
const char conn_TCP [] = "AT+CIPSTART=\"TCP\",\"82.209.230.70\",88\r\n";
const char send_TSP [] = "AT+CIPSEND=";
const char start_AP[] = "AT+CWSAP=\"ESP01\",\"12345678\",5,3\r\n";        //OK
const char multip_Conn[] = "AT+CIPMUX=1\r\n";//allow multiple connections    //OK
const char esp_Mode[] = "AT+CWMODE=3\r\n";//softAP(2) + station mode(1)   //OK
const char start_Server[] = "AT+CIPSERVER=1,80\r\n";//start server at HTTP port 80 //OK
const char send_Data_Comand[] = "AT+CIPSEND=0,5\r\n";
const char show_mac[] = "AT+CIPSTAMAC_CUR\r\n";//show mac adress
const char show_AP_around[] =	"AT+CWLAP\r\n";
const char info[] =	"AT+CIPSTATUS\r\n";
																	