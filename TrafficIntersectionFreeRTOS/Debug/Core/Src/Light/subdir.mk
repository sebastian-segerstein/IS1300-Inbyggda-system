################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Light/carLights.c \
../Core/Src/Light/pedestrianLights.c 

OBJS += \
./Core/Src/Light/carLights.o \
./Core/Src/Light/pedestrianLights.o 

C_DEPS += \
./Core/Src/Light/carLights.d \
./Core/Src/Light/pedestrianLights.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/Light/%.o Core/Src/Light/%.su Core/Src/Light/%.cyclo: ../Core/Src/Light/%.c Core/Src/Light/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-Light

clean-Core-2f-Src-2f-Light:
	-$(RM) ./Core/Src/Light/carLights.cyclo ./Core/Src/Light/carLights.d ./Core/Src/Light/carLights.o ./Core/Src/Light/carLights.su ./Core/Src/Light/pedestrianLights.cyclo ./Core/Src/Light/pedestrianLights.d ./Core/Src/Light/pedestrianLights.o ./Core/Src/Light/pedestrianLights.su

.PHONY: clean-Core-2f-Src-2f-Light

