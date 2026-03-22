#------------------------------------------------------------------------------
# This file defines the source files and header files Makefile uses depending
# on the target platform (HOST or MSP432)
#
# This file is included in the Makefile
#
# Author: Khanh Pham (Kevin)
# Date:   February 2026
#
# Sources:
#      HOST     - Compiles main.c and memory.c only
#      MSP432   - Additionally compiles the MSP432 startup, interrupt, and
#                 system initialization files required for bare-metal boot
#
# Includes:
#      HOST     - Common headers shared across both platforms
#      MSP432   - Additionally includes MSP432 and CMSIS device headers
#
#------------------------------------------------------------------------------

SOURCES = src/main.c \
	  src/memory.c

ifeq ($(PLATFORM), MSP432)
SOURCES += src/interrupts_msp432p401r_gcc.c
SOURCES += src/startup_msp432p401r_gcc.c
SOURCES += src/system_msp432p401r.c
endif

# Add your include paths to this variable
INCLUDES = include/common

ifeq ($(PLATFORM), MSP432)
INCLUDES += include/msp432
INCLUDES += include/CMSIS
endif

