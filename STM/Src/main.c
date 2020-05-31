/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "string.h"
#include "esp_01.h"
//#include "Setings.h"
#include <stdio.h>
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define RX_BUF_MASK 1024-1
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */
void clear_rx_buf(void);
uint8_t check_answer(char *str,uint16_t wait);
void usart1_send_string(const char str[]);
void usart2_send_string(const char str[]);
void esp_Start2(void);
void usart1_reciv_string(void);
void Clear_buffer(void);
void recive(void);
void clear_Mess(void);
void send(char str[] , uint32_t time);

const char server_Ip [15]= "192.168.8.102";
const char acsessPoint[20]="MTS424D-8942";
const char acsessPass[20]="9ifdrfrr";
const char serverIp [15]= "192.168.8.102";
const char conn_TCP2 []= "AT+CIPSTART=\"TCP\",\"192.168.8.102\",9076\r\n";

//void recive(void);
#define ITM_Port8(n)    (*((volatile unsigned char *)(0xE0000000+4*n)))
#define ITM_Port16(n)   (*((volatile unsigned short*)(0xE0000000+4*n)))
#define ITM_Port32(n)   (*((volatile unsigned long *)(0xE0000000+4*n)))
#define DEMCR           (*((volatile unsigned long *)(0xE000EDFC)))
#define TRCENA           0x01000000

struct __FILE { int handle;};
FILE __stdout;
FILE __stdin;

int fputc(int ch, FILE *f) {
   if (DEMCR & TRCENA) {

while (ITM_Port32(0) == 0){};
    ITM_Port8(0) = ch;
  }
  return(ch);
}

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
char test[] = "AT\r\n";
char sendbuf[50];
char rx_buf[1024]="";
volatile uint16_t rx_pos=0;

//const char conn_TCP2 []= "AT+CIPSTART=\"TCP\",\"192.168.8.100\",9076\r\n";
const uint16_t serverPort = 9076;

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
//=================================SETTINGS======================================//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//

char mess[50]="";

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */
  

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	uint8_t step=0;
	char str[] = "";
	char send[]="";
	//char test_string []= " hello";
	
	
__HAL_UART_ENABLE_IT(&huart1, UART_IT_RXNE);	
esp_Start2();
uint32_t foto = 0;
sprintf(str,"%s%s","\r\nINIT FINISHED","\r\n");
HAL_UART_Transmit(&huart2,(uint8_t*)str,strlen(str),1000);

char send_[]="im STM";
char *tok;
char mess[50]="";
uint16_t some_data = 777;
uint8_t Flag= 1;
  while (1)
  {
		
		
		if(Flag==1)
			{
					 sprintf(mess,"%s%c",send_,'\0');
					 if(DEBUG)printf("adc_value = %s\r\n", mess);
					 if(DEBUG)printf("send_TSP_sizeof_message\r\n");	
					 sprintf(sendbuf,"%s%d%s%c",send_TSP,strlen(mess),"\r\n",'\0');
					 usart1_send_string(sendbuf);
					 HAL_Delay(50);	
           if(DEBUG)printf("send_TSP_message\r\n");
           usart1_send_string(mess);
	         if(DEBUG)usart2_send_string(rx_buf);
					 clear_Mess();
					 if(check_answer("SEND OK",2000))
						 {
							 Flag=0;
							 usart2_send_string("send END\r\n");
						 }
			}
					 sprintf(mess,"%d%c",some_data,'\0');
					 if(DEBUG)printf("adc_value = %s\r\n", mess);
					 if(DEBUG)printf("send_TSP_sizeof_message\r\n");	
					 sprintf(sendbuf,"%s%d%s%c",send_TSP,strlen(mess),"\r\n",'\0');
					 usart1_send_string(sendbuf);
					 HAL_Delay(50);	

           usart1_send_string(mess);

			
			
			
		
			if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14)==GPIO_PIN_SET)
			{
				HAL_UART_Transmit(&huart2,(uint8_t*)"SVETIIIIIK \n\r",16,2000);
				foto = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14);
				HAL_UART_Transmit(&huart2,(uint8_t*)foto,sizeof(foto),2000);
			}
			foto = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14);
			HAL_UART_Transmit(&huart2,(uint8_t*)foto,sizeof(foto),2000);
	if(check_answer("LED1",1000))
			{
			HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_8);
			}
	if(check_answer("LED2",1000))
			{
			HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_6);
			}
	if(check_answer("LED3",1000))
			{
			HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_7);
			}
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage 
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, RED_LED_3_Pin|RED_LED_2_Pin|RED_LED_1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LD2_Pin */
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LDPIN_Pin */
  GPIO_InitStruct.Pin = LDPIN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(LDPIN_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : RED_LED_3_Pin RED_LED_2_Pin RED_LED_1_Pin */
  GPIO_InitStruct.Pin = RED_LED_3_Pin|RED_LED_2_Pin|RED_LED_1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void USART1_IRQHandler(void){
    unsigned char rx_b;    
    if (USART1->SR & USART_SR_RXNE) 
	{     
		    rx_b = USART1->DR;
		    rx_buf[rx_pos++]=rx_b;//extern
	     	rx_pos &= RX_BUF_MASK;
		   	printf("%c",rx_b);
	}
      rx_buf[rx_pos+1]='\0';
}

void clear_rx_buf(void){
 for(;rx_pos!=0;rx_pos--)
		rx_buf[rx_pos]='\0';
	rx_pos=0;
}

void clear_Mess(void){
 for(uint16_t i = 0;i < 50;i++)
	mess[i]='\0';
	//rx_pos=0;
}
void usart1_send_string(const char str[]){
HAL_UART_Transmit(&huart1,(uint8_t*)str,strlen(str),100);
}

void usart2_send_string(const char str[]){
HAL_UART_Transmit(&huart2,(uint8_t*)str,strlen(str),100);
}

void usart1_reciv_string(){
HAL_UART_Receive_IT(&huart1,(uint8_t*)rx_buf,1024);
//HAL_UART_Transmit(&huart1,(uint8_t*)str,strlen(str),100);
}


uint8_t check_answer(char *str,uint16_t wait){
uint32_t time_Ms_Now = HAL_GetTick();
char *istr = NULL;
	while(istr==NULL && ((HAL_GetTick()-time_Ms_Now)< wait)){
			istr=strstr(rx_buf,str);
		} 
		if(istr!=NULL){
			clear_rx_buf();
			return 1;	
		}else return 0;
}


void Clear_buffer()
{
	int i = 0;
while(1)
	{
		rx_buf[i] = '\0';
		if(i == strlen(rx_buf))
			break;
	}

}

	void esp_Start2(void){
//usart1_send_string(restart);
uint8_t step=0;
	
while(1){
	
	switch(step){
		 case(0):	
			usart2_send_string("send_string(at_test)\r\n");
		 usart1_send_string(at_test);
			if (check_answer("OK",1000))step++;	
		break;
		case(1):
			usart2_send_string("send_string(echoOff)\r\n");
			usart1_send_string(echoOff);
			if (check_answer("OK",1000))step++;
		break;
		case(2):
			usart2_send_string("send_string(station_mode)\r\n");
			usart1_send_string(station_mode);
			if (check_answer("OK",1000))step++;
		break;
		case(3):	
		usart2_send_string("send_string(restart)\r\n");
			usart1_send_string(restart);
		  HAL_Delay(2500);
      clear_rx_buf();
      step++;
		break;
		case(4):
			usart2_send_string("send_string(conect_to_AP)\r\n");	
			sprintf(sendbuf,"%s%s%s%s%s","AT+CWJAP=\"",acsessPoint,"\",\"",acsessPass,"\"\r\n");
		  usart1_send_string(sendbuf);
			if (check_answer("OK",10000))
			step++;
		break;
		case(5):			
			usart2_send_string("send_string(conect_to_AP_ststus)\r\n");	
			usart1_send_string(conect_AP_status);
		  if (check_answer("OK",5000))step++;
		break;
		case(6):
			usart2_send_string("send_string(get_IP)\r\n");
			usart1_send_string(get_IP);
		  if (check_answer("OK",1000))step++;
		break;
		case(7):
			usart2_send_string("NoMultConn\r\n");
			usart1_send_string(NoMultConn);
		  if (check_answer("OK",1000))step++;
		break;
		case(8):
			usart2_send_string("connect to server\r\n");	
		  usart1_send_string(conn_TCP2);          // connect to server
		  if (check_answer("CONNECT",3000))
					step++;
		break;
			case(9):
				usart2_send_string("info about connect:\r\n");
				usart1_send_string(info);          // connect to server
			HAL_UART_Transmit(&huart2,(uint8_t*)rx_buf,strlen(rx_buf),1000);
		  if (check_answer("OK",1000))
				{
					step++;
				}
		break;
	}
if (step==10)break;
	HAL_Delay(200);
 }
}

void send(char str[] , uint32_t time)
{				
				char *tok;
				tok = strtok (str, " \r\n");
				//sprintf(adc_Value,"%s%c",tok,'\0');
	      //sprintf(adc_Value,"%d%c",adc_value,'\0');
        //if(DEBUG)usart2_send_string("send_TSP_sizeof_message\r\n");	
	      sprintf(sendbuf,"%s%d%c",send_TSP,strlen(tok),'\0');		
				//usart2_send_string("BREAKPOINT 5\r\n");	
        //usart1_send_string_slow(sendbuf);
				//usart2_send_string("BREAKPOINT 6\r\n");
				//usart2_send_string("BREAKPOINT 7\r\n");		
        if(DEBUG)usart2_send_string("send_TSP_message\r\n");
        //usart2_send_string("BREAKPOINT 8\r\n");
				usart1_send_string(tok);
				//delay(time);
				HAL_Delay(time);
				//delay(500000);
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
