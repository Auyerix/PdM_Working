
#include <stdint.h>
#include <stdbool.h>
#include "stm32f4xx_hal.h"

typedef bool bool_t;


bool_t uartInit(void);
void uartSendString(uint8_t * pstring);
void uartSendStringSize(uint8_t * pstring, uint16_t size);
void uartReceiveStringSize(uint8_t * pstring, uint16_t size);
