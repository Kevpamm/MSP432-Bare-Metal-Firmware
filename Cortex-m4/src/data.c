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

int32_t my_atoi(uint8_t * ptr, uint8_t digits, uint8_t base) {

  switch (base) {
    case 2:
      return;

    case 8:
      return;

    case 10:
      return;

    case 16:
      return;

  }
}
