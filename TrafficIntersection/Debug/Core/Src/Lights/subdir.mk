################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Lights/carSignalLights.c \
../Core/Src/Lights/pedestrianLights.c 

OBJS += \
./Core/Src/Lights/carSignalLights.o \
./Core/Src/Lights/pedestrianLights.o 

C_DEPS += \
./Core/Src/Lights/carSignalLights.d \
./Core/Src/Lights/pedestrianLights.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/Lights/%.o Core/Src/Lights/%.su Core/Src/Lights/%.cyclo: ../Core/Src/Lights/%.c Core/Src/Lights/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-Lights

clean-Core-2f-Src-2f-Lights:
	-$(RM) ./Core/Src/Lights/carSignalLights.cyclo ./Core/Src/Lights/carSignalLights.d ./Core/Src/Lights/carSignalLights.o ./Core/Src/Lights/carSignalLights.su ./Core/Src/Lights/pedestrianLights.cyclo ./Core/Src/Lights/pedestrianLights.d ./Core/Src/Lights/pedestrianLights.o ./Core/Src/Lights/pedestrianLights.su

.PHONY: clean-Core-2f-Src-2f-Lights

