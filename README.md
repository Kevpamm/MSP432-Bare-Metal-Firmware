# MSP432 Bare-Metal Firmware

Bare-metal firmware for the ARM Cortex-M4 (MSP432P401R) — implements custom memory management, data conversion utilities, and a cross-platform build system that supports both native host and embedded targets.

---

## Overview

This project is written entirely in C and targets the Texas Instruments MSP432P401R microcontroller, which is based on the ARM Cortex-M4 core with a hardware floating-point unit. The firmware is built without an operating system or standard library dependencies, and is compiled using a cross-platform Makefile that supports both native host builds (for testing) and embedded ARM builds (for deployment). The MCU, unfortunately, is discontinued. However, that does not stop a firmware enthusiast from starting and exploring 😎.

---

## Project Structure

```
Cortex-M4/
├── Makefile                          # Cross-platform build system
├── sources.mk                        # Platform-conditional source and include paths
├── msp432p401r.lds                   # Linker script for MSP432P401R memory layout
├── src/
│   ├── main.c                        # Entry point
│   ├── memory.c                      # Custom memory manipulation functions
│   ├── data.c                        # Integer-to-string and string-to-integer conversion
│   ├── stats.c                       # Array statistics (min, max, mean, median)
│   ├── testing.c                     # Top-level test harness
│   ├── interrupts_msp432p401r_gcc.c  # Interrupt vector table (MSP432 only)
│   ├── startup_msp432p401r_gcc.c     # Bare-metal startup and .data/.bss init (MSP432 only)
│   └── system_msp432p401r.c         # System clock initialization (MSP432 only)
└── include/
    ├── common/                       # Headers shared across both platforms
    │   ├── memory.h
    │   ├── data.h
    │   ├── stats.h
    │   ├── testing.h
    │   └── platform.h
    └── msp432/                       # MSP432-specific device headers
        └── msp.h
```

---

## Hardware Target

| Property        | Details                          |
|-----------------|----------------------------------|
| Microcontroller | Texas Instruments MSP432P401R    |
| CPU Core        | ARM Cortex-M4                    |
| Architecture    | ARMv7E-M                         |
| Flash           | 256 KB                           |
| SRAM            | 64 KB                            |
| FPU             | FPv4-SP-D16 (hard ABI)           |
| Instruction Set | Thumb-2                          |

---

## Build System

The Makefile supports two platforms controlled by the `PLATFORM` variable.

| Platform         | Compiler            | Use case                            |
|------------------|---------------------|-------------------------------------|
| `HOST` (default) | `gcc`               | Native build for testing on a PC    |
| `MSP432`         | `arm-none-eabi-gcc` | Cross-compile for the MSP432P401R   |

### Prerequisites

For `HOST` builds:
- GCC (`gcc`)

For `MSP432` builds:
- ARM GNU Toolchain (`arm-none-eabi-gcc`)

### Build Targets

| Target        | Description                                                   |
|---------------|---------------------------------------------------------------|
| `build`       | Compiles and links all sources into `c1m2.out`, prints memory usage |
| `compile-all` | Compiles all source files to object files without linking     |
| `%.i`         | Generates preprocessed output for a given source file         |
| `%.asm`       | Generates assembly output for a given source file             |
| `%.o`         | Compiles a single source file into an object file             |
| `clean`       | Removes all generated build artifacts                         |

### Build Commands

```bash
# Build for host (default)
make build

# Build for MSP432
make build PLATFORM=MSP432

# Compile only, no linking
make compile-all PLATFORM=MSP432

# Generate preprocessed output for a specific file
make src/memory.i PLATFORM=MSP432

# Generate assembly output for a specific file
make src/memory.asm PLATFORM=MSP432

# Clean all build artifacts
make clean
```

### Compile-Time Switches (Future updates)

| Flag        | Effect                                               |
|-------------|------------------------------------------------------|
| `-DCOURSE1` | Enables the `course1()` test harness in `main.c`     |
| `-DVERBOSE` | Enables `print_array()` debug output in `stats.c`    |
| `-DHOST`    | Targets native host platform                         |
| `-DMSP432`  | Targets MSP432P401R embedded platform                |

---

## Function Reference

### memory.c

| Function                                               | Description                                                                 |
|--------------------------------------------------------|-----------------------------------------------------------------------------|
| `my_memmove(src, dst, length)`                         | Moves `length` bytes from `src` to `dst`. Handles overlapping regions safely. |
| `my_memcopy(src, dst, length)`                         | Copies `length` bytes from `src` to `dst`. Behavior is undefined if regions overlap. |
| `my_memset(src, length, value)`                        | Sets `length` bytes starting at `src` to `value`.                          |
| `my_memzero(src, length)`                              | Zeroes out `length` bytes starting at `src`.                               |
| `my_reverse(src, length)`                              | Reverses the byte order of `length` bytes in place at `src`.               |
| `reserve_words(length)`                                | Dynamically allocates `length` words on the heap. Returns `NULL` on failure. |
| `free_words(src)`                                      | Frees a dynamically allocated block pointed to by `src`.                   |

All operations are implemented using pointer arithmetic exclusively — no array indexing.

### data.c

| Function              | Description                                                    |
|-----------------------|----------------------------------------------------------------|
| `my_itoa(data, ptr, base)` | Converts a 32-bit signed integer to a null-terminated string in the given base (2–16). |
| `my_atoi(ptr, digits, base)` | Converts a string representation of a number back to a 32-bit signed integer. |

### stats.c

| Function                    | Description                                      |
|-----------------------------|--------------------------------------------------|
| `find_minimum(arr, length)` | Returns the minimum value in the array.          |
| `find_maximum(arr, length)` | Returns the maximum value in the array.          |
| `find_mean(arr, length)`    | Returns the mean value of the array.             |
| `find_median(arr, length)`  | Returns the median value of the array.           |
| `print_statistics(arr, length)` | Prints min, max, mean, and median to output. |
| `print_array(arr, length)`  | Prints array contents. Enabled only with `-DVERBOSE`. |

---

## Author

**Khanh Pham (Kevin)**  
March 2026
