#ifndef EEPROM_H
#define EEPROM_H

/* Header Includes */
#include "I2C.h"

/* Macro Defintions */
#define SLAVE_ADDRESS	((0x50) << 1)		//left shifting 7-bit I2C slave address to make it of one byte. Slave address of ST's EEPROM (Part No. M24M02) is 0x50

/* Function Prototypes */
void EEPROM_Write(uint8_t Address, uint16_t Reg, uint8_t *buffer, uint16_t size);
void EEPROM_Read(uint8_t Address, uint16_t Reg, uint8_t *buffer, uint16_t size);

#endif
