/* Header Includes */
#include "I2C.h"
#include "stm32f103xb.h"

/* Function Definitions */
void I2C_Config(void)
{
	RCC->APB1ENR |= (1 << 21);    // enable I2C CLOCK
	RCC->APB2ENR |= (1 << 3);    // Enable GPIOB CLOCK

	AFIO->MAPR &= ~(1 << 1);				// Configure the I2C PINs for ALternate Functions
	GPIOB->CRL |= (1 << 24) | (1 << 26) | (1 << 27) | (1 << 28) | (1 << 30) | (1 << 31);    // output open drain

	I2C1->CR1 |= (1 << 15);		// Reset the I2C
	I2C1->CR1 &= ~(1 << 15);

	I2C1->CR2 |= (8 << 0);    // PCLK1 FREQUENCY in MHz

	I2C1->CCR = 40 << 0;		// Configure the clock control register

	I2C1->TRISE = 9;		// Configure the rise time register

	I2C1->CR1 |= (1 << 0);    // Enable I2C Peripheral
}

void I2C_Start(void)
{
	I2C1->CR1 |= (1 << 10);    // Enable the ACK
	I2C1->CR1 |= (1 << 8);    // Generate START
	while (!(I2C1->SR1 & (1 << 0)));    // Wait fror SB bit to set
}

void I2C_Write(uint8_t data)
{
	while (!(I2C1->SR1 & (1 << 7)));    // wait for TXE bit to set
	I2C1->DR = data;
	while (!(I2C1->SR1 & (1 << 2)));    // wait for BTF bit to set
}

void I2C_Address(uint8_t Address)
{
	I2C1->DR = Address;    //  send the address
	while (!(I2C1->SR1 & (1 << 1)));    // wait for ADDR bit to set
	uint8_t temp = I2C1->SR1 | I2C1->SR2;    // read SR1 and SR2 to clear the ADDR bit
}

void I2C_Stop(void)
{
	I2C1->CR1 |= (1 << 9);    // Stop I2C
}

void I2C_WriteMulti(uint8_t* Reg_Array, uint8_t *data, uint16_t size)
{
	while (!(I2C1->SR1 & (1 << 7)));    // wait for TXE bit to set

	while (!(I2C1->SR1 & (1 << 7)));    // wait for TXE bit to set
	I2C1->DR = (uint32_t)Reg_Array[0];    // send data

	while (!(I2C1->SR1 & (1 << 7)));    // wait for TXE bit to set
	I2C1->DR = (uint32_t)Reg_Array[1];    // send data

	while (size)
	{
		while (!(I2C1->SR1 & (1 << 7)));    // wait for TXE bit to set
		I2C1->DR = (uint32_t)*data++;    // send data
		size--;
	}

	while (!(I2C1->SR1 & (1 << 2)));    // wait for BTF to set
}

void I2C_Read(uint8_t Address, uint8_t *buffer, uint16_t size)
{
	int remaining = size;

	if(size == 1)
	{
		I2C1->DR = Address;    //  send the address
		while (!(I2C1->SR1 & (1 << 1)));    // wait for ADDR bit to set

		I2C1->CR1 &= ~(1 << 10);    // clear the ACK bit
		uint8_t temp = I2C1->SR1 | I2C1->SR2;    // read SR1 and SR2 to clear the ADDR bit
		I2C1->CR1 |= (1 << 9);    // Stop I2C

		while (!(I2C1->SR1 & (1 << 6)));    // wait for RxNE to set

		buffer[size - remaining] = I2C1->DR;    // Read the data from the DATA REGISTER
	}

	else
	{
		I2C1->DR = Address;    //  send the address
		while (!(I2C1->SR1 & (1 << 1)));    // wait for ADDR bit to set

		uint8_t temp = I2C1->SR1 | I2C1->SR2;    // read SR1 and SR2 to clear the ADDR bit

		while (remaining > 2)
		{
			while (!(I2C1->SR1 & (1 << 6)));    // wait for RxNE to set

			buffer[size - remaining] = I2C1->DR;    // copy the data into the buffer

			I2C1->CR1 |= 1 << 10;    // Set the ACK bit to Acknowledge the data received

			remaining--;
		}

		while (!(I2C1->SR1 & (1 << 6)));    // wait for RxNE to set
		buffer[size - remaining] = I2C1->DR;

		I2C1->CR1 &= ~(1 << 10);    // clear the ACK bit

		I2C1->CR1 |= (1 << 9);    // Stop I2C

		remaining--;

		while (!(I2C1->SR1 & (1 << 6)));    // wait for RxNE to set
		buffer[size - remaining] = I2C1->DR;    // copy the data into the buffer
	}

}
