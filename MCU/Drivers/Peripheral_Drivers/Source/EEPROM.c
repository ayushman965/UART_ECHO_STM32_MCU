/* Header Includes */
#include "EEPROM.h"

/* Function Definitions */

//This function can write multiple bytes(Size) into the eeprom
void EEPROM_Write (uint8_t Address, uint16_t Reg, uint8_t *buffer, uint16_t size)
{
	uint8_t Reg_Array[2];

	Reg_Array[0] = (uint8_t)((Reg & 0xFF00) >> 8);
	Reg_Array[1] = (uint8_t)(Reg & 0x00FF);

	I2C_Start ();
	I2C_Address (Address);
	I2C_WriteMulti(Reg_Array, buffer, size);
	I2C_Stop ();
}

//This function can read multiple bytes(Size) from the eeprom
void EEPROM_Read (uint8_t Address, uint16_t Reg, uint8_t *buffer, uint16_t size)
{
	uint8_t RegH = (uint8_t)((Reg & 0xFF00) >> 8);
	uint8_t RegL = (uint8_t)(Reg & 0x00FF);

	I2C_Start ();
	I2C_Address (Address);
	I2C_Write (RegH);
	I2C_Write (RegL);
	I2C_Start ();  // repeated start
	I2C_Read (Address+0x01, buffer, size);
	I2C_Stop ();
}
