
#include <API_lcd.h>
#include "port.h"


void lcd_send_cmd (char cmd)
{
  char data_u, data_l;
	uint8_t data_t[4];
	data_u = (cmd&0xf0);
	data_l = ((cmd<<4)&0xf0);
	data_t[0] = data_u|0x0C;  //en=1, rs=0
	data_t[1] = data_u|0x08;  //en=0, rs=0
	data_t[2] = data_l|0x0C;  //en=1, rs=0
	data_t[3] = data_l|0x08;  //en=0, rs=0

	//llama a la función que envìa los datos al LCD
	i2c_lcd_transmit (data_t, 4);
}

void lcd_send_data (char data)
{
	char data_u, data_l;
	uint8_t data_t[4];
	data_u = (data&0xf0);
	data_l = ((data<<4)&0xf0);
	data_t[0] = data_u|0x0D;  //en=1, rs=1
	data_t[1] = data_u|0x09;  //en=0, rs=1
	data_t[2] = data_l|0x0D;  //en=1, rs=1
	data_t[3] = data_l|0x09;  //en=0, rs=1

	//llama a la función que envìa los datos al LCD
	i2c_lcd_transmit (data_t, 4);
}

void lcd_clear (void)
{
	lcd_send_cmd (0x00);
	for (int i=0; i<100; i++)
	{
		lcd_send_data (' ');
	}
}

void lcd_init (void)
{
	// 4 bit initialisation
	HAL_Delay(50);  // wait for >40ms
	lcd_send_cmd (0x30);
	HAL_Delay(5);  // wait for >4.1ms
	lcd_send_cmd (0x30);
	HAL_Delay(1);  // wait for >100us
	lcd_send_cmd (0x30);
	HAL_Delay(10);
	lcd_send_cmd (0x20);  // 4bit mode
	HAL_Delay(10);

  // display initialisation
	//Comment the line “lcd_send_cmd (0x28);” and it ‘ll work for 1604a LCD
	//Por default arranca en este modo y en este módulo, para que funcione, la recomendación es no enviar este comando
	//lcd_send_cmd (0x28); // Function set --> DL=0 (4 bit mode), N = 1 (2 line display) F = 0 (5x8 characters)
	HAL_Delay(1);
	lcd_send_cmd (0x08); //Display on/off control --> D=0,C=0, B=0  ---> display off
	HAL_Delay(1);
	lcd_send_cmd (0x01);  // clear display
	HAL_Delay(1);
	HAL_Delay(1);
	lcd_send_cmd (0x06); //Entry mode set --> I/D = 1 (increment cursor) & S = 0 (no shift)
	HAL_Delay(1);
	lcd_send_cmd (0x0C); //Display on/off control --> D = 1, C and B = 0. (Cursor and blink, last two bits)
}

void lcd_send_string (char *str)
{
	while (*str) lcd_send_data (*str++);
}

void welcome_message(void){

	//Mensaje de Bienvenida PASAR A LA API
	//el or se hace según la posición de memoria de inicio
	//depende de la tabla de memoria que es distinta en 16x4 y 20x4
	//ver https://controllerstech.com/lcd-20x4-using-i2c-with-stm32/

	lcd_clear();

	lcd_send_cmd (0x80|0x00);
	lcd_send_string("BIENVENIDA:");

	lcd_send_cmd (0x80|0x40);
	lcd_send_string("LECTOR PRESION");

	lcd_send_cmd (0x80|0x10);
	lcd_send_string("Y TEMPERATURA");

	lcd_send_cmd (0x80|0x50);
	lcd_send_string("PdM y PCSE 2023");

	HAL_Delay(3000);
	lcd_clear();

}