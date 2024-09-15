#ifndef I2C_H
#define I2C_H

/* Header Includes */
#include "main.h"

/* Function Prototypes */
void I2C_Config (void);
void I2C_Start (void);
void I2C_Write (uint8_t data);
void I2C_Address (uint8_t Address);
void I2C_Stop (void);
void I2C_WriteMulti (uint8_t* Reg_Array, uint8_t *data, uint16_t size);
void I2C_Read (uint8_t Address, uint8_t *buffer, uint16_t size);

#endif
