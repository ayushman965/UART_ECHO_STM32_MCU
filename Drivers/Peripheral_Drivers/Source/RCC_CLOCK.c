/* Header Includes */
#include "RCC_CLOCK.h"

/* Global Variables */
volatile uint32_t msTicks = 0;

/* Function Definitions */

//This is Systick Interrupt Handler, this is called every millisecond, need to implement overflow spill condition of msTicks.
void SysTick_Handler(void)
{
	msTicks++;    // Increment the millisecond counter
}

//Initializing Systick Timer which is a part of ARM Cortex M-3 processor core.
void SysTick_Init(void)
{
	// Reload value to trigger every 1 ms (8 MHz / 1000 = 8000)
	SysTick->LOAD = 8000 - 1;    // Set reload register

	// Set the priority of the SysTick interrupt (optional)
	NVIC_SetPriority(SysTick_IRQn, (1 << __NVIC_PRIO_BITS) - 1);    // Set lowest priority

	// Set the SysTick counter value to 0
	SysTick->VAL = 0;

	// Enable SysTick: Enable timer, enable interrupt, select processor clock
	SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk
			| SysTick_CTRL_ENABLE_Msk;
}

//This functions provides blocking-mode delay. It inputs delay in milliseconds.
void Delay_ms(uint32_t delay)
{
	uint32_t currentTicks = msTicks;    // Capture the current value of msTicks
	while ((msTicks - currentTicks) < delay);    // Wait until the delay time has passed
}
