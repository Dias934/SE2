################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/cr_startup_lpc175x_6x.c \
../src/crp.c \
../src/data_storage.c \
../src/menu.c \
../src/menu_maintenance.c \
../src/menu_normal.c \
../src/project.c \
../src/view.c 

OBJS += \
./src/cr_startup_lpc175x_6x.o \
./src/crp.o \
./src/data_storage.o \
./src/menu.o \
./src/menu_maintenance.o \
./src/menu_normal.o \
./src/project.o \
./src/view.o 

C_DEPS += \
./src/cr_startup_lpc175x_6x.d \
./src/crp.d \
./src/data_storage.d \
./src/menu.d \
./src/menu_maintenance.d \
./src/menu_normal.d \
./src/project.d \
./src/view.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__USE_CMSIS=CMSIS_CORE_LPC17xx -D__LPC17XX__ -D__REDLIB__ -I"D:\Isel\19-20\Inverno\SE1\project\inc" -I"D:\Isel\19-20\Inverno\SE1\SE1920\inc" -I"D:\Isel\19-20\Inverno\SE1\CMSIS_CORE_LPC17xx\inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


