/* Header File Includes */
#include "main.h"
#include <stdio.h>
#include "RCC_CLOCK.h"
#include "UART.h"
#include "I2C.h"
#include "EEPROM.h"

/* Global Variables */
volatile uint8_t uart_data_rx;
volatile RingBuffer rb;


/* Main Function Start */
int main(void)
{
	SysTick_Init();		//Initialinzing Systick to enable ms delay

	uart_init();		//Initializing UART1 @2400 Baud Rate on pins PA9(Tx) & PA10(Rx). Also Enabling UART Rx Interrupt.

	I2C_Config();		//Initailizing I2C1 @100Khz on pins PB6(SCL) & PB7(SDA)

	initBuffer(&rb);		//Initializing Ring buffer to store data received over UART1 Rx Interrupt(from PC)

	uint16_t eeprom_address = 0x0000;		//EEPROM Register/Memory Location Address

	#ifdef DEBUG_PRINTS
	uint8_t BUFF[20] = { 0 };

	snprintf((char*)BUFF, sizeof(BUFF), "\nSystem Initiated!");
	UART_Transmit(BUFF, sizeof(BUFF));
	#endif

	uint8_t rx_buffer[256] =
	{ 0 };

	uint8_t tx_buffer[256] =
	{ 0 };

	uint16_t i = 0;

	while (i < 256)
	{
		tx_buffer[i] = 0xFF;		//Filling the buffer with 0xFF.
		i++;
	}

	for(uint8_t j=0;j<4;j++)
	{
		EEPROM_Write(SLAVE_ADDRESS, (j * 0x100), tx_buffer, 256);		//Filling EEPROM with 0xFF from address 0 to 1023 to clear the old contents
		Delay_ms(10);
	}

	while (1)
	{
		char read_element = readBuffer(&rb);		//Reading data from Ring Buffer, the data is filled in ring buffer in UART1 Rx Interrupt.

		if(read_element != '\0')
		{
			EEPROM_Write(SLAVE_ADDRESS, eeprom_address++, (uint8_t*)&read_element, 1);		//Storing the byte into EEPROM fetched from Ring Buffer
			Delay_ms(10);		//10ms of delay is required after byte/page read/write from EEPROM
		}

		if(eeprom_address >= 1010)		//Once the complete paragraph is received and simultaneously written into eeprom, processor starts PAGE reading the data from EEPROM.
		{
			NVIC_DisableIRQ(USART1_IRQn);		//Disabling UART1 Rx Interrupt since the complete data has been received.

			for(uint8_t k=0;k<3;k++)
			{
				EEPROM_Read(SLAVE_ADDRESS, (k * 0x100), rx_buffer, 256);		//Reading paragraph stored in the EEPROM by PAGE Read operation
				Delay_ms(10);
				UART_Transmit(rx_buffer, 256);
			}

			EEPROM_Read(SLAVE_ADDRESS, 0x0300, rx_buffer, 256-13);		//Reading the last page.
			Delay_ms(10);
			UART_Transmit(rx_buffer, 256-13);

			eeprom_address = 0;		//setting eeprom register/memory address to 0 to get ready to store the data again into eeprom from 0th address.

			NVIC_EnableIRQ(USART1_IRQn);		//Enabling UART1 Rx Interrupt to receive next paragraph of 1010 byte form PC.
		}
	}
	return 0;
}
/* Main Function End */

/* Function Definition Start */

//Error Handler is called to debug any Error Condition.
void Error_Handler(void)
{
	__disable_irq();
	while (1);
}

//Initializing Ring Buffer
void initBuffer(volatile RingBuffer *rb)
{
	rb->head = 0;
	rb->tail = 0;
	rb->count = 0;
}

//Checking if Ring Buffer is full
bool isFull(volatile RingBuffer *rb)
{
	return rb->count == BUFFER_SIZE;
}

//Checking if Ring Buffer is empty
bool isEmpty(volatile RingBuffer *rb)
{
	return rb->count == 0;
}

//Wrinting one byte into Ring Buffer
void writeBuffer(volatile RingBuffer *rb, char c)
{
	if(isFull(rb))
	{
		rb->tail = (rb->tail + 1) % BUFFER_SIZE;    // Overwrite the oldest data
	}
	else
	{
		rb->count++;
	}

	rb->buffer[rb->head] = c;
	rb->head = (rb->head + 1) % BUFFER_SIZE;
}

//Returns one byte form Ring Buffer also deletes the read byte
char readBuffer(volatile RingBuffer *rb)
{
	if(isEmpty(rb))
	{
		return '\0';
	}
	char c = rb->buffer[rb->tail];
	rb->tail = (rb->tail + 1) % BUFFER_SIZE;
	rb->count--;

	return c;
}
/* Function Definition End */

