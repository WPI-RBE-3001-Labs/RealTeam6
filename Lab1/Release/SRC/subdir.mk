################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../SRC/ADC.c \
../SRC/USART.c \
../SRC/freerunADC.c \
../SRC/globals.c \
../SRC/main.c \
../SRC/ports.c \
../SRC/timer.c 

OBJS += \
./SRC/ADC.o \
./SRC/USART.o \
./SRC/freerunADC.o \
./SRC/globals.o \
./SRC/main.o \
./SRC/ports.o \
./SRC/timer.o 

C_DEPS += \
./SRC/ADC.d \
./SRC/USART.d \
./SRC/freerunADC.d \
./SRC/globals.d \
./SRC/main.d \
./SRC/ports.d \
./SRC/timer.d 


# Each subdirectory must supply rules for building sources it contributes
SRC/%.o: ../SRC/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"C:\Users\nbeeten\git\rbelib\RBELib\include" -I"C:\WinAVR-20100110\avr\include" -I"C:\WinAVR-20100110\lib\gcc\avr\4.3.3\include" -I"C:\WinAVR-20100110\lib\gcc\avr\4.3.3\include-fixed" -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega644p -DF_CPU=18432000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


