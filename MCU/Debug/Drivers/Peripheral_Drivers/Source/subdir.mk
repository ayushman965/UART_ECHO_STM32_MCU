################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/Peripheral_Drivers/Source/EEPROM.c \
../Drivers/Peripheral_Drivers/Source/I2C.c \
../Drivers/Peripheral_Drivers/Source/RCC_CLOCK.c \
../Drivers/Peripheral_Drivers/Source/UART.c 

OBJS += \
./Drivers/Peripheral_Drivers/Source/EEPROM.o \
./Drivers/Peripheral_Drivers/Source/I2C.o \
./Drivers/Peripheral_Drivers/Source/RCC_CLOCK.o \
./Drivers/Peripheral_Drivers/Source/UART.o 

C_DEPS += \
./Drivers/Peripheral_Drivers/Source/EEPROM.d \
./Drivers/Peripheral_Drivers/Source/I2C.d \
./Drivers/Peripheral_Drivers/Source/RCC_CLOCK.d \
./Drivers/Peripheral_Drivers/Source/UART.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/Peripheral_Drivers/Source/%.o Drivers/Peripheral_Drivers/Source/%.su Drivers/Peripheral_Drivers/Source/%.cyclo: ../Drivers/Peripheral_Drivers/Source/%.c Drivers/Peripheral_Drivers/Source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -I"D:/THRSL/CubeIDE_Workspace/UART_ECHO_FIRMWARE_TASK_1/Drivers/CMSIS/Include" -I"D:/THRSL/CubeIDE_Workspace/UART_ECHO_FIRMWARE_TASK_1/Drivers/CMSIS/Device/ST/STM32F1xx/Include" -I"D:/THRSL/CubeIDE_Workspace/UART_ECHO_FIRMWARE_TASK_1/Drivers/Peripheral_Drivers/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-Peripheral_Drivers-2f-Source

clean-Drivers-2f-Peripheral_Drivers-2f-Source:
	-$(RM) ./Drivers/Peripheral_Drivers/Source/EEPROM.cyclo ./Drivers/Peripheral_Drivers/Source/EEPROM.d ./Drivers/Peripheral_Drivers/Source/EEPROM.o ./Drivers/Peripheral_Drivers/Source/EEPROM.su ./Drivers/Peripheral_Drivers/Source/I2C.cyclo ./Drivers/Peripheral_Drivers/Source/I2C.d ./Drivers/Peripheral_Drivers/Source/I2C.o ./Drivers/Peripheral_Drivers/Source/I2C.su ./Drivers/Peripheral_Drivers/Source/RCC_CLOCK.cyclo ./Drivers/Peripheral_Drivers/Source/RCC_CLOCK.d ./Drivers/Peripheral_Drivers/Source/RCC_CLOCK.o ./Drivers/Peripheral_Drivers/Source/RCC_CLOCK.su ./Drivers/Peripheral_Drivers/Source/UART.cyclo ./Drivers/Peripheral_Drivers/Source/UART.d ./Drivers/Peripheral_Drivers/Source/UART.o ./Drivers/Peripheral_Drivers/Source/UART.su

.PHONY: clean-Drivers-2f-Peripheral_Drivers-2f-Source

