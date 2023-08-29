################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/rtems-tasks.c 

C_DEPS += \
./src/rtems-tasks.d 

OBJS += \
./src/rtems-tasks.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	sparc-rtems-gcc -I"D:\WORKSPACE\VERITAS\test_example\src\includes" -O0 -g3 -Wall -c -fmessage-length=0 -mcpu=v8 -qleon3 -std=gnu99 -Wcast-qual -Wformat=2 -Wshadow -Wundef -Wuninitialized -fdiagnostics-show-option -fpermissive -msoft-float -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/rtems-tasks.d ./src/rtems-tasks.o

.PHONY: clean-src

