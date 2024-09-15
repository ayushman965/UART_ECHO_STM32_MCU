#ifndef UART_H
#define UART_H

/* Header Includes */
#include "main.h"

/* Extern Variables */
extern volatile uint8_t uart_data_rx;
extern volatile RingBuffer rb;

/* Function Prototypes */
void uart_init(void);
void uart_send_char(char c);
void UART_Transmit(uint8_t *data, uint32_t size);

#endif
