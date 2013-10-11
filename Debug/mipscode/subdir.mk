################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../mipscode/ackermann.c \
../mipscode/qsort.c \
../mipscode/rt30.c 

OBJS += \
./mipscode/ackermann.o \
./mipscode/qsort.o \
./mipscode/rt30.o 

C_DEPS += \
./mipscode/ackermann.d \
./mipscode/qsort.d \
./mipscode/rt30.d 


# Each subdirectory must supply rules for building sources it contributes
mipscode/%.o: ../mipscode/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


