################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../app/app.c \
../app/cbf.c \
../app/hw.c \
../app/shell.c 

OBJS += \
./app/app.o \
./app/cbf.o \
./app/hw.o \
./app/shell.o 

C_DEPS += \
./app/app.d \
./app/cbf.d \
./app/hw.d \
./app/shell.d 


# Each subdirectory must supply rules for building sources it contributes
app/%.o: ../app/%.c app/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F401xC -DDEBUG -c -I../Core/Inc -I../app -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-app

clean-app:
	-$(RM) ./app/app.d ./app/app.o ./app/cbf.d ./app/cbf.o ./app/hw.d ./app/hw.o ./app/shell.d ./app/shell.o

.PHONY: clean-app

