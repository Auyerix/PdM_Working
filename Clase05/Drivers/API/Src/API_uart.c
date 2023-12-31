
#include <stdint.h>
#include <stdbool.h>
#include "API_uart.h"
#include "stm32f4xx_hal.h"
#include <stdio.h>

//instancia de la  estructura: huart2
static UART_HandleTypeDef huart2;


bool_t uartInit(void){

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
		return false;
	}
	else{
		char parametros[100];


		sprintf(parametros,"\nBaudRate=%ld\nWordLength=%ld\nStopBits=%ld\nParity=%ld \n",huart2.Init.BaudRate,huart2.Init.WordLength,huart2.Init.StopBits,huart2.Init.Parity);

		HAL_UART_Transmit(&huart2, parametros , sizeof(parametros), 100);

		//Demora bloqueante para observar los valores de la uart
		HAL_Delay(2000);


		return true;
	}



}

void uartSendString(uint8_t * pstring){

	//variable utilizada para la cuenta de caracteres hasta llegar  '\0'
	uint8_t i = 0;

	//Cuenta de caracteres en la cadena apuntada por pstring
	while (* pstring++ !='\0'){
		i++;
	}
	//Llama a la HAL con la huart correspoendiente, el valor del puntero retornado al valor inicial
	//luego de la cuenta de caracteres (se le resta i y 1 para llegar al origen) y el largo leido en la
	//variable i luego del while

	HAL_UART_Transmit(&huart2, pstring - i - 1 , i , 200);

	//HAL_UART_Transmit(&huart2, (const uint8_t*) "Hola\n", sizeof("Hola\n"), 1000);
	//HAL_UART_Transmit(&huart2, pstring, sizeof (pstring), 200);
	//HAL_UART_Transmit(&huart2, pstring, 10, 200);

}

void uartSendStringSize(uint8_t * pstring, uint16_t size){

	HAL_UART_Transmit(&huart2, pstring, size, 200);

}



