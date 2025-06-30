################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Logic/carSignalLogic.c \
../Core/Src/Logic/pedestrianLogic.c 

OBJS += \
./Core/Src/Logic/carSignalLogic.o \
./Core/Src/Logic/pedestrianLogic.o 

C_DEPS += \
./Core/Src/Logic/carSignalLogic.d \
./Core/Src/Logic/pedestrianLogic.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/Logic/%.o Core/Src/Logic/%.su Core/Src/Logic/%.cyclo: ../Core/Src/Logic/%.c Core/Src/Logic/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-Logic

clean-Core-2f-Src-2f-Logic:
	-$(RM) ./Core/Src/Logic/carSignalLogic.cyclo ./Core/Src/Logic/carSignalLogic.d ./Core/Src/Logic/carSignalLogic.o ./Core/Src/Logic/carSignalLogic.su ./Core/Src/Logic/pedestrianLogic.cyclo ./Core/Src/Logic/pedestrianLogic.d ./Core/Src/Logic/pedestrianLogic.o ./Core/Src/Logic/pedestrianLogic.su

.PHONY: clean-Core-2f-Src-2f-Logic

