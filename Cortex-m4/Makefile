#******************************************************************************
# Copyright (C) 2017 by Alex Fosdick - University of Colorado
#
# Redistribution, modification or use of this software in source or binary
# forms is permitted as long as the files maintain this copyright. Users are 
# permitted to modify this and use it to learn about the field of embedded
# software. Alex Fosdick and the University of Colorado are not liable for any
# misuse of this material. 
#
#*****************************************************************************

#------------------------------------------------------------------------------
# <Put a Description Here>
#
# Use: make [TARGET] [PLATFORM-OVERRIDES]
#
# Build Targets:
#      <Put a description of the supported targets here>
#
# Platform Overrides:
#      <Put a description of the supported Overrides here
#
#------------------------------------------------------------------------------
include sources.mk

# Platform Overrides
PLATFORM ?= HOST


# Compiler Flags and Defines 
LDFLAGS =
CFLAGS = -Wall -Werror
LANGUAGE_STANDARD = -std=c99
DEBUG_FLAGS = -g
OPT_FLAG = -O0

CFFLAGS += $(LANGUAGE_STANDARD) $(DEBUG_FLAGS) $(OPT_FLAG)
TARGET = c1m2

ifeq ($(PLATFORM), HOST)
# Compiler
CC = gcc

# DEfines/Preprocessor Flags
CPPFLAGS = -D$(PLATFORM) -I$(INCLUDES)

# COmpiler Flags
CFLAGS += $(CPPFLAGS)
endif

ifeq ($(PLATFORM), MSP432)
# Compiler
CC = arm-none-eabi-gcc

#Defines/Preprocessor Flags
CPPFLAGS = -D$(PLATFORM) $(patsubst %, -I%,$(INCLUDES))

# CPU
CPU = cortex-m4
CPU_FLAGS = -mcpu=$(CPU)

# Instruction Set
INSTRUCTION_SET = thumb
INSTRUCTION_FLAGS = -m$(INSTRUCTION_SET)

# Architecture
ARCH = armv7e-m
ARCH_FLAGS = -march=$(ARCH)

#Floating Point Unit Hardware
FPU = fpv4-sp-d16
FPU_FLAGS = -mfpu=$(FPU)

#Floating Point ABI
FLOAT_ABI = hard
FLOAT_FLAGS = -mfloat-abi=$(FLOAT_ABI)

# Runtime
SPECS = nosys.specs
SPECS_FLAGS = --specs=$(SPECS)

# Linker Flags
LINKER_FILE = ../msp432p401r.lds
#Directive unfound
# Fix this shit

LDFLAGS = -T $(LINKER_FILE) -Wl,-Map=$(TARGET).map

# Full Compiler Flags
CFLAGS += $(CPPFLAGS) $(CPU_FLAGS) $(INSTRUCTION_FLAGS) $(ARCH_FLAGS) \
$(FPU_FLAGS) $(FLOAT_FLAGS) $(SPECS_FLAGS)

endif

OBJS =  $(SOURCES:.c=.o)

%.i : %.c
	$(CC) -E $< $(CFLAGS) -MD -MP -MF $(@:.i=.d) -o $@

%.asm : %.c
	$(CC) -S $< $(CFLAGS) -MD -MP -MF $(@:.asm=.d) -o $@

%.o : %.c
	$(CC) -c $< $(CFLAGS) -MD -MP -MF $(@:.o=.d) -o $@

.PHONY: compile-all
compile-all: $(OBJS)

.PHONE: build
build: $(TARGET).out

$(TARGET).out : $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(LDFLAGS) -o $@

.PHONE: clean
clean:
	rm -f $(OBJS) *.o *.i *.s *.asm *.d $(TARGET).map $(TARGET).out
