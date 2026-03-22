#------------------------------------------------------------------------------
# Cross-platform build system for the MSP432P401R embedded firmware project.
# The build below supports native host compilation for testing and ARM cross-compilation
# for deployment to the MSP432P401R (Cortex-M4) target.
#
# Author: Khanh Pham (Kevin)
# Date: February 2026
#
# Use: make [TARGET] [PLATFORM-OVERRIDES]
#
# Build Targets:
#      build        - Compiles and links all source files into $(TARGET).out
#                     and prints memory usage via the size tool
#      compile-all  - Compiles all source files into object files without linking
#      %.i          - Generates preprocessed output for a given source file
#      %.asm        - Generates assembly output for a given source file
#      %.o          - Compiles a single source file into an object file
#      clean        - Removes all generated build artifacts (.o, .i, .asm,
#                     .d, .map, .out)
#
# Platform Overrides:
#      PLATFORM=HOST    (default) Compiles with gcc for the native host machine.
#                       Enables host-side testing and debugging without hardware.
#
#      PLATFORM=MSP432  Cross-compiles with arm-none-eabi-gcc targeting the
#                       MSP432P401R (ARM Cortex-M4, ARMv7E-M, hard FPU).
#                       Uses the provided linker script msp432p401r.lds and
#                       generates a .map file for memory analysis.
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
LINKER_FILE = msp432p401r.lds
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
