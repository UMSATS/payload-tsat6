################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/heaters.c \
../Drivers/max7300.c \
../Drivers/thermostats.c \
../Drivers/tlv2553.c 

OBJS += \
./Drivers/heaters.o \
./Drivers/max7300.o \
./Drivers/thermostats.o \
./Drivers/tlv2553.o 

C_DEPS += \
./Drivers/heaters.d \
./Drivers/max7300.d \
./Drivers/thermostats.d \
./Drivers/tlv2553.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/%.o Drivers/%.su: ../Drivers/%.c Drivers/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L452xx -c -I../Core/Inc -I../Drivers -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers

clean-Drivers:
	-$(RM) ./Drivers/heaters.d ./Drivers/heaters.o ./Drivers/heaters.su ./Drivers/max7300.d ./Drivers/max7300.o ./Drivers/max7300.su ./Drivers/thermostats.d ./Drivers/thermostats.o ./Drivers/thermostats.su ./Drivers/tlv2553.d ./Drivers/tlv2553.o ./Drivers/tlv2553.su

.PHONY: clean-Drivers

