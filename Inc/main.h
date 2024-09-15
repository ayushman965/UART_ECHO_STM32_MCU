#ifndef MAIN_H
#define MAIN_H

/* Header Includes */
#include "stm32f103xb.h"
#include <stdbool.h>

/* Macro Definitions */
#define BUFFER_SIZE 1010		//Size of ring buffer
//#define DEBUG_PRINTS		//Uncomment this line to enable debug prints

/* Structure Definition */
typedef struct
{
	char buffer[BUFFER_SIZE];
	int head;    // Points to the next location to write
	int tail;    // Points to the next location to read
	int count;    // Number of elements in the buffer
} RingBuffer;

/* Function Prototypes */
void Error_Handler(void);
void initBuffer(volatile RingBuffer *rb);
bool isFull(volatile RingBuffer *rb);
bool isEmpty(volatile RingBuffer *rb);
void writeBuffer(volatile RingBuffer *rb, char c);
char readBuffer(volatile RingBuffer *rb);

#endif
