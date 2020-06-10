################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/calendar_maintenance.c \
../src/cr_startup_lpc175x_6x-FreeRTOS.c \
../src/crp.c \
../src/data_manager.c \
../src/init_menu.c \
../src/menu.c \
../src/menu_maintenance.c \
../src/menu_normal.c \
../src/project.c \
../src/select_maintenance.c \
../src/temperature_unit_maintenance.c \
../src/time_maintenance.c \
../src/viewLCDText.c 

OBJS += \
./src/calendar_maintenance.o \
./src/cr_startup_lpc175x_6x-FreeRTOS.o \
./src/crp.o \
./src/data_manager.o \
./src/init_menu.o \
./src/menu.o \
./src/menu_maintenance.o \
./src/menu_normal.o \
./src/project.o \
./src/select_maintenance.o \
./src/temperature_unit_maintenance.o \
./src/time_maintenance.o \
./src/viewLCDText.o 

C_DEPS += \
./src/calendar_maintenance.d \
./src/cr_startup_lpc175x_6x-FreeRTOS.d \
./src/crp.d \
./src/data_manager.d \
./src/init_menu.d \
./src/menu.d \
./src/menu_maintenance.d \
./src/menu_normal.d \
./src/project.d \
./src/select_maintenance.d \
./src/temperature_unit_maintenance.d \
./src/time_maintenance.d \
./src/viewLCDText.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__USE_CMSIS=CMSIS_CORE_LPC17xx -D__LPC17XX__ -D__REDLIB__ -I"C:\Users\Manue\OneDrive\Documentos\Isel\19-20\Verao\SE2\Ambiente\SE2\project\inc" -I"C:\Users\Manue\OneDrive\Documentos\Isel\19-20\Verao\SE2\Ambiente\SE2\FreeRTOS-Kernel\src\portable" -I"C:\Users\Manue\OneDrive\Documentos\Isel\19-20\Verao\SE2\Ambiente\SE2\FreeRTOS-Kernel\include" -I"C:\Users\Manue\OneDrive\Documentos\Isel\19-20\Verao\SE2\Ambiente\SE2\SE1920\inc" -I"C:\Users\Manue\OneDrive\Documentos\Isel\19-20\Verao\SE2\Ambiente\SE2\CMSIS_CORE_LPC17xx\inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m3 -mthumb -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


