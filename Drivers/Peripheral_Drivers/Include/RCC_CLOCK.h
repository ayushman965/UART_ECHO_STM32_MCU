#ifndef RCC_CLOCK_H
#define RCC_CLOCK_H

/* Header Includes */
#include "main.h"

/* Function Prototypes */
void SysTick_Handler(void);
void SysTick_Init(void);
void Delay_ms(uint32_t delay);

#endif
