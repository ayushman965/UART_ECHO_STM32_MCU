# UART_ECHO_STM32_MCU
 There are two part of this project-
 1- PC Console: PC Console is windows application which is written in c++ language. This application transmits predefined data of 1009 bytes and waits to accept the same data over UART.

 2- MCU Application: It is a STM32 project. It receives data over UART and stores it into an I2C based EEPROM simultaneously and then read it back from EEPROM and transmits the data over UART.

 Components Details-
 Microcontroller is STM32F103C8T6 (Bluepill Board)
 EEPROM is M24M02 (I2C Based EEPROM)
 Logic Analyzer has been used to visulaize and debug I2C and UART packets.
