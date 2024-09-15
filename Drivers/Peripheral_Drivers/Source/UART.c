/* Header Includes */
#include"UART.h"

/* Function Definitions Starts */
void uart_init(void)
{
	RCC->APB2ENR |= (1 << 2) | (1 << 14) | (1 << 0);    // Enable AFIO, GPIOA, and USART1 clocks
	AFIO->MAPR &= ~AFIO_MAPR_USART1_REMAP;    // Clear remap for USART1

	GPIOA->CRH &= ~(0xF << 4);    // Clear bits for PA9
	GPIOA->CRH |= (0xA << 4);    // Set as alternate function push-pull
	USART1->BRR = 0xD05;    // Set baud rate (assuming 8 MHz clock, 2400 baud). 8 MHz / 2400 = 0xD05

	USART1->CR1 |= (1 << 3) | (1 << 13) | (1 << 2) | (1 << 5);    // Enable transmitter (TE) Enable USART (UE) etc.

	NVIC_EnableIRQ(USART1_IRQn);		//Enable USART1 Interrupt
}

// Function to send a character over USART1
void uart_send_char(char c)
{
	while (!(USART1->SR & (1 << 7)));	//Wait until transmit data register is empty
	USART1->DR = c;

	while (!(USART1->SR & (1 << 6)));    // Wait for TC flag (Transmission Complete)
}

//USART1 Interrupt Handler. Whenever interrupt is generated, this ISR is called.
void USART1_IRQHandler(void)
{
	if( USART1->SR & (1 << 5))
	{
		uart_data_rx = (uint8_t) USART1->DR;

		if(uart_data_rx == 0x0A || uart_data_rx == 0x0D || (uart_data_rx >= 0x20 && uart_data_rx <= 0x7E))
		{
			writeBuffer(&rb, uart_data_rx);
		}
		//uart_send_char(uart_data_rx);
	}
}

//This function can transmit multiple (Size) bytes over USART1
void UART_Transmit(uint8_t *data, uint32_t size)
{
	for(uint32_t i = 0; i < size; i++)
	{
		uart_send_char(data[i]);
	}
}
/* Functions Defintions End */
