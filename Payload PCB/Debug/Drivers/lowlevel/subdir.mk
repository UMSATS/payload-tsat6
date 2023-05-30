################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/lowlevel/max6822.c \
../Drivers/lowlevel/max7300.c \
../Drivers/lowlevel/tlv2553.c 

OBJS += \
./Drivers/lowlevel/max6822.o \
./Drivers/lowlevel/max7300.o \
./Drivers/lowlevel/tlv2553.o 

C_DEPS += \
./Drivers/lowlevel/max6822.d \
./Drivers/lowlevel/max7300.d \
./Drivers/lowlevel/tlv2553.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/lowlevel/%.o Drivers/lowlevel/%.su Drivers/lowlevel/%.cyclo: ../Drivers/lowlevel/%.c Drivers/lowlevel/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L452xx -c -I../Core/Inc -I../Drivers -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-lowlevel

clean-Drivers-2f-lowlevel:
	-$(RM) ./Drivers/lowlevel/max6822.cyclo ./Drivers/lowlevel/max6822.d ./Drivers/lowlevel/max6822.o ./Drivers/lowlevel/max6822.su ./Drivers/lowlevel/max7300.cyclo ./Drivers/lowlevel/max7300.d ./Drivers/lowlevel/max7300.o ./Drivers/lowlevel/max7300.su ./Drivers/lowlevel/tlv2553.cyclo ./Drivers/lowlevel/tlv2553.d ./Drivers/lowlevel/tlv2553.o ./Drivers/lowlevel/tlv2553.su

.PHONY: clean-Drivers-2f-lowlevel

