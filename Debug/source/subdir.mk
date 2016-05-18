################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/AStar.c \
../source/List.c \
../source/Map.c \
../source/Status.c \
../source/TestList.c \
../source/main.c 

OBJS += \
./source/AStar.o \
./source/List.o \
./source/Map.o \
./source/Status.o \
./source/TestList.o \
./source/main.o 

C_DEPS += \
./source/AStar.d \
./source/List.d \
./source/Map.d \
./source/Status.d \
./source/TestList.d \
./source/main.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"/home/gustavo/workspace/cEpita/pathProject/header" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


