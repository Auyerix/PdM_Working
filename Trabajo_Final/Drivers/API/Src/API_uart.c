
#include <stdint.h>
#include <stdbool.h>
#include "API_uart.h"
#include "stm32f4xx_hal.h"
#include <stdio.h>
//se incluye string.h para el uso de strlen()
#include <string.h>

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


		sprintf(parametros,"\nBaudRate=%ld\n\rWordLength=%ld\n\rStopBits=%ld\n\rParity=%ld\n\r",huart2.Init.BaudRate,huart2.Init.WordLength,huart2.Init.StopBits,huart2.Init.Parity);

		//casteo de parámetros para evitar el warning: (const uint8_t *)parametros es decir le digo que parámetros ya
		//no es chart (realizado)
		//Atención: sprintf devuelve la cantidad de caracteres escritos, se podría usar para escribir la cantidad de
		//caracteres en lugar de sizeof
		//Atención: en lugar de sizeof se podría utilizar strlen para que realmente llegue hasta el '\0' (realizado)
		//Atención: acá también se podría usar la función uartSendString que envía hasta '\0'

		//HAL_UART_Transmit(&huart2, (const uint8_t *)parametros , sizeof(parametros), 100);
		HAL_UART_Transmit(&huart2, (const uint8_t *)parametros , strlen(parametros), 100);

		//Demora bloqueante para observar los valores iniciales de la uart
		HAL_Delay(2000);


		return true;
	}



}

void uartSendString(uint8_t * pstring){

	//variable utilizada para la cuenta de caracteres hasta llegar  '\0'
	uint8_t i = 0;

	//Cuenta de caracteres en la cadena apuntada por pstring
	//Rutina de while no bloqueante con el if y break
	while (* pstring++ !='\0'){
		i++;
		if(i>254) break;
	}
	//Llama a la HAL con la huart correspoendiente, el valor del puntero retornado al valor inicial
	//luego de la cuenta de caracteres (se le resta i y 1 para llegar al origen) y el largo leido en la
	//variable i luego del while

	HAL_UART_Transmit(&huart2, pstring - i - 1 , i , 200);


}

void uartSendStringSize(uint8_t * pstring, uint16_t size){

	HAL_UART_Transmit(&huart2, pstring, size, 200);

}

void uartReceiveStringSize(uint8_t * pstring, uint16_t size){

	HAL_UART_Receive(&huart2, pstring, size, 20000);
}


