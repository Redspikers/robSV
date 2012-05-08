################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../AStarLight.cpp \
../Arm.cpp \
../Captor.cpp \
../Cell.cpp \
../Conveyor.cpp \
../Gate.cpp \
../Map.cpp \
../Motor.cpp \
../Node.cpp \
../NodeQueue.cpp \
../NodeQueueItem.cpp \
../Pin.cpp \
../Pomp.cpp \
../Robot.cpp \
../Sensors.cpp \
../distance_parcouru_roues.cpp \
../main.cpp 

OBJS += \
./AStarLight.o \
./Arm.o \
./Captor.o \
./Cell.o \
./Conveyor.o \
./Gate.o \
./Map.o \
./Motor.o \
./Node.o \
./NodeQueue.o \
./NodeQueueItem.o \
./Pin.o \
./Pomp.o \
./Robot.o \
./Sensors.o \
./distance_parcouru_roues.o \
./main.o 

CPP_DEPS += \
./AStarLight.d \
./Arm.d \
./Captor.d \
./Cell.d \
./Conveyor.d \
./Gate.d \
./Map.d \
./Motor.d \
./Node.d \
./NodeQueue.d \
./NodeQueueItem.d \
./Pin.d \
./Pomp.d \
./Robot.d \
./Sensors.d \
./distance_parcouru_roues.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -funsigned-char -funsigned-bitfields -fno-exceptions -mmcu=atmega1280 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


