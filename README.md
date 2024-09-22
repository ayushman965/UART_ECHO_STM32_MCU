# UART_ECHO_STM32_MCU
 __There are two part of this project-__
 
 __1- PC Console:__ PC Console is windows application which is written in c++ language. This application transmits predefined data of 1009 bytes and waits to accept the same data over UART.

 __2- MCU Application:__ It is a STM32 project. It receives data over UART and stores it into an I2C based EEPROM simultaneously and then read it back from EEPROM and transmits the data over UART.

 __Components Details-__
 __Microcontroller is STM32F103C8T6 (Bluepill Board)
 EEPROM is M24M02 (I2C Based EEPROM)
 Logic Analyzer has been used to visulaize and debug I2C and UART packets.
 FT232 USB TO UART Converter__

<p align="center">
  <img src="[image_url](https://github.com/ayushman965/UART_ECHO_STM32_MCU/blob/main/Pictures/Block_diagram_uart.drawio.png)" alt="Alt Text" />
</p>
![MCU](https://github.com/ayushman965/UART_ECHO_STM32_MCU/blob/main/Pictures/STM32F103C8T6_Blue_Pill.jpg)
![EEPROM Module](https://github.com/ayushman965/UART_ECHO_STM32_MCU/blob/main/Pictures/eeprom_module.jpg)
![FT232 Module](https://github.com/ayushman965/UART_ECHO_STM32_MCU/blob/main/Pictures/FT232.jpg)
