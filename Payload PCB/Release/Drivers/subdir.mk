################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/heaters.c \
../Drivers/leds.c \
../Drivers/lightlevels.c \
../Drivers/temperatures.c \
../Drivers/thermostats.c 

OBJS += \
./Drivers/heaters.o \
./Drivers/leds.o \
./Drivers/lightlevels.o \
./Drivers/temperatures.o \
./Drivers/thermostats.o 

C_DEPS += \
./Drivers/heaters.d \
./Drivers/leds.d \
./Drivers/lightlevels.d \
./Drivers/temperatures.d \
./Drivers/thermostats.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/%.o Drivers/%.su: ../Drivers/%.c Drivers/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32L452xx -c -I../Core/Inc -I../Drivers -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers

clean-Drivers:
	-$(RM) ./Drivers/heaters.d ./Drivers/heaters.o ./Drivers/heaters.su ./Drivers/leds.d ./Drivers/leds.o ./Drivers/leds.su ./Drivers/lightlevels.d ./Drivers/lightlevels.o ./Drivers/lightlevels.su ./Drivers/temperatures.d ./Drivers/temperatures.o ./Drivers/temperatures.su ./Drivers/thermostats.d ./Drivers/thermostats.o ./Drivers/thermostats.su

.PHONY: clean-Drivers

