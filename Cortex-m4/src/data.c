#include "data.h"
#include "memory.h"

uint8_t my_itoa(int32_t data, uint8_t * ptr, uint32_t base) {
  int32_t temp = data;
  if (base == 10) {
    uint8_t length = 0;
    while ((temp /= 10) != 0)
      length++;
    length++; //length gives the number of digits of int32_t data parameter

    *(ptr + length) = '\0';

    while (--length) {
      *(ptr + length) = ((data % 10) + '0');
      data /= 10;
    }
    *ptr = data;
  }

  else if (base == 2) {
    uint8_t i = 0;
    do {
      *(ptr + i) = (temp % 2) + '0';
      temp /= 2;
      i++;
    } while (temp != 0);

    //Reverse the order of elements at the memory location
    i += 1;
    my_reverse(ptr, i); //This function is declared in "memory.h"

    //Add the null terminal at the end of the ASCII string
    i += 1;
    *(ptr + i) = '\0';

    //i is also the length of the ASCII string, including the null terminal.
    return i;
  }

  else if (base == 8) {
    uint8_t i = 0;
    do {
      *(ptr + i) =  (temp % 8) + '0';
      temp /= 8;
      i++;
    } while (temp != 0);

    //Reverse the order of the element at the memory location
    i += 1;
    my_reverse(ptr, i);

    //Add null terminal at the end of the ASCII string
    i += 1;
    *(ptr + i) = '\0';

    //i is also the length of the ASCII string, including the null character.
    return i;
  }

  else if (base == 16) {
    uint8_t i = 0;
    do {
      *(ptr + i) = (temp % 16) + '0';
      temp /= 16;
      i++;
    } while (temp != 0);

   i += 1;
   my_reverse(ptr, i);

   i += 1;
   *(ptr + i) = '\0'

   return i;
  }

  else {
    printf("This base you chose is not supported\n");
    printf("Please choose a different base");
    return 0;
  }
}
