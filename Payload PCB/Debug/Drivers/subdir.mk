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
Drivers/%.o Drivers/%.su Drivers/%.cyclo: ../Drivers/%.c Drivers/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L452xx -c -I../Core/Inc -I../Drivers -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers

clean-Drivers:
	-$(RM) ./Drivers/heaters.cyclo ./Drivers/heaters.d ./Drivers/heaters.o ./Drivers/heaters.su ./Drivers/leds.cyclo ./Drivers/leds.d ./Drivers/leds.o ./Drivers/leds.su ./Drivers/lightlevels.cyclo ./Drivers/lightlevels.d ./Drivers/lightlevels.o ./Drivers/lightlevels.su ./Drivers/temperatures.cyclo ./Drivers/temperatures.d ./Drivers/temperatures.o ./Drivers/temperatures.su ./Drivers/thermostats.cyclo ./Drivers/thermostats.d ./Drivers/thermostats.o ./Drivers/thermostats.su

.PHONY: clean-Drivers

