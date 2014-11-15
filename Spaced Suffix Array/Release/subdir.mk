################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Alphabet.c \
../DisLex.c \
../MaskedSuffixArray.c \
../testDriver.c 

OBJS += \
./Alphabet.o \
./DisLex.o \
./MaskedSuffixArray.o \
./testDriver.o 

C_DEPS += \
./Alphabet.d \
./DisLex.d \
./MaskedSuffixArray.d \
./testDriver.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


