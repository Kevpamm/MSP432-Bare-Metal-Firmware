/******************************************************************************
 * @file    data.c
 * @author  Khanh Pham (Kevin)
 * @date    March 2026
 *
 * @brief   This file contains the implementation of integer-to-ASCII and
 *          ASCII-to-integer conversion functions for signed 32-bit integers
 *          across multiple bases (2, 8, 10, 16).
 *
 *          my_itoa() converts an integer to an ASCII string and returns
 *                    the string length including the null terminator at the end.
 *          my_atoi() converts an ASCII string back to a signed 32-bit integer.
 *
 *          Both functions handle negative numbers and use pointer arithmetic
 *          exclusively — no array indexing.
 ******************************************************************************/

#include "data.h"
#include "memory.h"

uint8_t my_itoa (int32_t data, uint8_t * ptr, uint8_t base) {
  int32_t temp = data;
  uint8_t i = 0;
  int32_t digit = 0;
  switch (base) {
    case 2:
      do {
        digit = temp % 2;
        if (digit < 0)
          digit = -digit;
        *(ptr + i) = digit + '0';
        temp /= 2;
        i++;
      } while (temp != 0);
      if (data < 0) {
        *(ptr + i) = '-';
        i++;
      }

      my_reverse(ptr, i);
      *(ptr + i) = '\0';
      i++;
      return i;

    case 8:
      do {
        digit = temp % 8;
        if (digit < 0)
          digit = -digit;
        *(ptr + i) = digit + '0';
        temp /= 8;
        i++;
      } while (temp != 0);
      if (data < 0) {
        *(ptr + i) = '-';
        i++;
      }
      my_reverse(ptr, i);
      *(ptr + i) = '\0';
      i++;
      return i;

    case 10:
      do {
        digit = temp % 10;
        if (digit < 0)
          digit = -digit;
        *(ptr + i) = digit + '0';
        temp /= 10;
        i++;
      } while (temp != 0);
      if (data < 0) {
        *(ptr + i) = '-';
        i++;
      }
      my_reverse(ptr, i);
      *(ptr + i) = '\0';
      i++;
      return i;

    case 16:
      do {
        digit = temp % 16;
        if (digit < 0)
          digit = -digit;
        if (digit < 10)
          *(ptr + i) = digit + '0';
        else
          *(ptr + i) = (digit - 10) + 'A';
        temp /= 16;
        i++;
      } while (temp != 0);
      if (data < 0) {
        *(ptr + i) = '-';
        i++;
      }
      my_reverse(ptr, i);
      *(ptr + i) = '\0';
      i++;
      return i;

    default:
      return 0;
  }
}

int32_t my_atoi (uint8_t * ptr, uint8_t digits, uint32_t base) {
  uint8_t i = 0;
  int32_t data = 0;
  switch (base) {
    case 2:
      if (*ptr == 45)
        //set flag? the flag is i? if i =1 => nega, = 0 => posi
        i++;
        for (uint8_t j = 0; j < digits - 1 - i; j++) {
          if (j == 0)
            data = *(ptr + digits - 2) - '0';
          else {
            int32_t temp = *(ptr + digits - 2 - j) - '0';
            if (temp == 1) {
              for (uint8_t k = 1; k <= j; k++)
                temp *= 2;
              data += temp;
            }
          }
        }
        if (i == 1)
          data = -data;
        return data;

    case 8:
      if (*ptr == 45)
        i++;
      for (uint8_t j = 0; j < digits - 1 - i; j++) {
        if (j == 0)
          data = *(ptr + digits - 2) - '0';
        else {
          int32_t temp = *(ptr + digits - 2 - j) - '0';
          if (temp != 0) {
            for (uint8_t k = 1; k <= j; k++)
              temp *= 8;
            data += temp;
          }
        }
      }
      if (i == 1)
        data = -data;
      return data;

    case 10:
      if (*ptr == 45)
        i++;
      for (uint8_t j = 0; j < digits - 1 - i; j++) {
        if (j == 0)
          data = *(ptr + digits - 2) - '0';
        else {
          int32_t temp = *(ptr + digits - 2 - j) - '0';
          if (temp != 0) {
            for (uint8_t k = 1; k <= j; k++)
              temp *= 10;
            data += temp;
          }
        }
      }
      if (i == 1)
        data = -data;
      return data;

    case 16:
      if (*ptr == 45)
        i++;
      for (uint8_t j = 0; j < digits - 1 - i; j++) {
        if (j == 0) {
          if (*(ptr + digits - 2) >= 65 && *(ptr + digits - 2) <= 70) //if the ASCII code in this buffer is the ASCII code for letter A-F
            data = *(ptr + digits - 2) - 'A' + 10;
          else //if the ASCII code in this buffer is the ASCII code for number 0-9
            data = *(ptr + digits - 2) - '0'; 
        }
        else {
          int32_t temp = *(ptr + digits - 2 - j);
          if (temp >= 65 && temp <= 70)
            temp = temp - 'A' + 10;
          else
            temp = temp - '0';
          if (temp != 0) {
            for (uint8_t k = 1; k <= j; k++)
              temp *= 16;
            data += temp;
          }
        }
      }
      if (i == 1)
        data = -data;
      return data;

    default:
      return 0;
  }
}
