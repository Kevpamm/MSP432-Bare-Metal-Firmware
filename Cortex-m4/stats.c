/**
 * @file stats.c
 * @brief main program and function implementation
 *
 * This file contains the main program and the implementation
 * of functions declared in 'stats.h'
 *
 * @author Kevin Pham
 * @date 01/26/2026
 *
 */

#include <stdio.h>
#include "stats.h"
#define SIZE 40U
/* size of the Data Set */
void main() {

   unsigned char test[SIZE] = {34, 201, 190, 154,   8, 194,   2,   6,
                              114, 88,   45,  76, 123,  87,  25,  23,
                              200, 122, 150, 90,   92,  87, 177, 244,
                              201,   6,  12,  60,   8,   2,   5,  67,
                                7,  87, 250, 230,  99,   3, 100,  90};
/* Array for test case 2 */
  unsigned char data[92] = {255, 1, 128, 64, 32, 16, 8, 4, 2, 0,
                             10, 20, 30, 40, 50, 60, 70, 80, 90, 100,
                            200, 150, 75, 25, 5, 250, 240, 230, 220, 210,
                              1, 3, 5, 7, 9, 11, 13, 15, 17, 19,
                             21, 23, 25, 27, 29, 31, 33, 35, 37, 39,
                             41, 43, 45, 47, 49, 51, 53, 55, 57, 59,
                             61, 63, 65, 67, 69, 71, 73, 75, 77, 79,
                             81, 83, 85, 87, 89, 91, 93, 95, 97, 99,
                            101, 103, 105, 107, 109, 111, 113, 115, 117, 119,
                            121, 123};

  printf("----------TEST CASE 1: ANALYSIS OF AN UNSORTED 92-ELEMENT ARRAY-----------\n\n");

  print_array(data, 92);
  print_statistics(data, 92);
  printf("\n");

  printf("----------TEST CASE 2: ANALYSIS OF THE 92-ELEMENT ARRAY AFTER SORTING----------\n\n");
  sort_array(data, 92);
  print_array(data, 92);
  print_statistics(data, 92);
  printf("\n");

  printf("-----------TEST CASE 3: ANALYSIS OF AN UNSORTED 40-ELEMENT ARRAY-------------\n\n");
  print_array(test, SIZE);
  print_statistics(test, SIZE);
  printf("\n");

  printf("-----------TEST CASE 4: ANALYSIS OF THE 40-ELEMENT ARRAY AFTER SORTING-----------\n\n");
  sort_array(test, SIZE);
  print_array(test, SIZE);
  print_statistics(test, SIZE);

}


void print_statistics(const unsigned char *arr, unsigned int size) {
  printf("Max value: %hhu\n", find_maximum(arr, size));
  printf("Min value: %hhu\n", find_minimum(arr, size));
  printf("Mean value: %hhu\n", find_mean(arr, size));
  unsigned char median = find_median(arr, size);
  if (median == USC_ERROR)
    printf("Median was not found because the array is unsorted. Please call 'sort_array'\n");
  else
    printf("Median value: %hhu\n", median);
}


void print_array(const unsigned char *arr, unsigned int size) {
  printf("Array: {");
  int count = 0;
  unsigned int temp = size;
  unsigned int lead = size;
  unsigned int end = size;
  while (temp != 0) {
   temp /= 10;
   count++;
  }
  if (count > 1) {
    int exp = 1;
    int dec_plac = 1;
    for (int i = 0; i < count - 2; i++) {
      exp *= 10;
      dec_plac *= 10;
    }
    dec_plac *= 10;
    for (int i = 0; i < count - 1; i++) {
      lead /= 10;
      end %= 10;
    }
    for (int i = 0; i < (lead*exp); i++) {
       for (int j = 0; j < 9; j++) {
         printf("%4hhu, ", arr[i*10+j]);
       }
       printf("%4hhu\n        ", arr[i*10+9]);
    }
    if (end > 1) {
      for (int i = 0; i < end - 1; i++) {
        printf("%4hhu, ", arr[lead*dec_plac + i]);
      }
      printf("%4hhu}\n", arr[size - 1]);
    }
    else if (end == 1) {
      printf("%4hhu   }\n", arr[size - 1]);
    }
    else
      printf("}\n");

  }

  else {
    for (int i = 0; i < size - 1; i++)
      printf("%4hhu, ", arr[i]);
    printf("%4hhu   }\n", arr[size - 1]);
  }
}


unsigned char find_mean(const unsigned char *arr, unsigned int size) {

  unsigned int sum = 0;
  for (int i = 0; i < size; i++) {
    sum += arr[i];
  }
  return sum/size;
}

unsigned char find_median(const unsigned char *arr, unsigned int size) {
  //Algorithm to check whether the array is sorted or not
  //because median can only be found on a sorted array.
  unsigned int i = 0;
  while (i < (size - 1) && (arr[i] == arr[i+1])) {
    i++; //if the first datas are duplicates, ignore them.
  }

  if (arr[i] > arr[i+1]) { //If the data at i is greater than the next data...
    i++;
    for (int j = i; j < size - 1; j++) { //...every remaining data
      if (arr[j] < arr[j+1])         //cannot be less than the one after it.
        return USC_ERROR;            //return a flag indicates array is unsorted if it is
    }
  }

  if (arr[i] < arr[i+1]) { //If the datat at i is less than the one after it...
    i++;
    for (int j = i; j < size - 1; j++) { //...every remaining data
      if (arr[j] > arr[j+1])        //cannot be larger than the one after it
        return USC_ERROR;               //return a flag to indicates unsorted array if it is
    }
  }
  //END OF VERIFYING ALGORIGHTM

  //START TO FIND THE MEDIAN
  unsigned char median = 0;
  if (size % 2 == 0)
    median = ((unsigned int)arr[size/2] + (unsigned int)arr[size/2 - 1])/2;

  else
    median = arr[size/2];

  return median;
}

unsigned char find_maximum(const unsigned char *arr, unsigned int size) {
  unsigned char max = 0;
  for (unsigned char i = 0; i < size; i++) {
    if (arr[i] > max)
      max = arr[i];
  }
  return max;
}

unsigned char find_minimum(const unsigned char *arr, unsigned int size) {
  unsigned char min = 255;
  for (unsigned char i = 0; i < size; i++) {
    if (arr[i] < min)
      min = arr[i];
  }
  return min;
}

void sort_array(unsigned char *arr, unsigned int size) {
  for (int i = 1; i < size; i++) {
    unsigned char key = arr[i];
      int j = i-1;
      while (j >= 0 && key > arr[j]) {
        arr[j+1] = arr[j];
        j--;
      }
      arr[j+1] = key;
  }
  printf("    >>  Array has been sorted!  <<     \n\n");
}
