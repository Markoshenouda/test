################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/User.cpp \
../src/UserManager.cpp \
../src/ai_logic.cpp \
../src/game_logic.cpp \
../src/game_ui.cpp \
../src/leaderboard.cpp 

OBJS += \
./src/User.o \
./src/UserManager.o \
./src/ai_logic.o \
./src/game_logic.o \
./src/game_ui.o \
./src/leaderboard.o 

CPP_DEPS += \
./src/User.d \
./src/UserManager.d \
./src/ai_logic.d \
./src/game_logic.d \
./src/game_ui.d \
./src/leaderboard.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


