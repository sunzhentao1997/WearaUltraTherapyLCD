################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Devices/dev_ad9833.c \
../Devices/dev_adc.c \
../Devices/dev_flash.c \
../Devices/dev_mpc5043.c 

OBJS += \
./Devices/dev_ad9833.o \
./Devices/dev_adc.o \
./Devices/dev_flash.o \
./Devices/dev_mpc5043.o 

C_DEPS += \
./Devices/dev_ad9833.d \
./Devices/dev_adc.d \
./Devices/dev_flash.d \
./Devices/dev_mpc5043.d 


# Each subdirectory must supply rules for building sources it contributes
Devices/%.o Devices/%.su Devices/%.cyclo: ../Devices/%.c Devices/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Devices

clean-Devices:
	-$(RM) ./Devices/dev_ad9833.cyclo ./Devices/dev_ad9833.d ./Devices/dev_ad9833.o ./Devices/dev_ad9833.su ./Devices/dev_adc.cyclo ./Devices/dev_adc.d ./Devices/dev_adc.o ./Devices/dev_adc.su ./Devices/dev_flash.cyclo ./Devices/dev_flash.d ./Devices/dev_flash.o ./Devices/dev_flash.su ./Devices/dev_mpc5043.cyclo ./Devices/dev_mpc5043.d ./Devices/dev_mpc5043.o ./Devices/dev_mpc5043.su

.PHONY: clean-Devices

