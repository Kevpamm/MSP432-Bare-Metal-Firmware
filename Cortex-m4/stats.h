/**
 *
 * @file stats.h
 * @brief Statistical analysis functions for an unsigned char array.
 *
 * This file contains function declarations and comments on their use.
 * The functions in this file help perform statistical analysis on an array.
 * The functions includes: find minimum, maximum, mean, and median values,...
 *                         print array and print statistics.
 * @author <Kevin Pham>
 * @date <01/25/2026>
 *
 */

#ifndef __STATS_H__
#define __STATS_H__
#define USC_ERROR 255

/**
 * @brief Find the minimum value of an array
 *
 * This function finds the minimum value of an array
 * and returns it as an unsigned char.
 *
 * @param *arr Pointer to an array of data
 * @param SIZE Length of the array as an unsigned int
 *
 * @return Minimum value among all array data
 */
unsigned char find_minimum(const unsigned char *arr, unsigned int SIZE);

/**
 * @brief Find the maximum value of an array
 *
 * This function finds the maximum value of an array
 * and returns it as an unsigned char.
 *
 * @param *arr Pointer to an array of data
 * @param SIZE Length of the array as an unsigned char
 *
 * @return Maximum value of the array as an unsigned char
 */
unsigned char find_maximum(const unsigned char *arr, unsigned int SIZE);

/**
 * @brief Find mean value of an array
 *
 * This function finds the mean (average) value of an array of data
 * and returns it as an unsigned char.
 *
 * @param *arr Pointer to an array of data
 * @param SIZE Length of the array
 *
 * @return Mean value of the array as an unsigned char
 */
unsigned char find_mean(const unsigned char *arr, unsigned int SIZE);

/**
 * @brief Find median value of an array
 * This function takes an array, finds its median value 
 * and return the median value as an unsigned char.
 *
 * This function has an algorithm to verif if the array
 * is sorted or not.
 *
 * @param *arr Pointer to an array of data
 * @param SIZE Length of the array
 *
 * @return Median value is the array is sorted
 * @return USC_ERROR (255) if the array is unsorted
 */
unsigned char find_median(const unsigned char *arr, unsigned int SIZE);

/**
 * @brief Print out all the data of an array
 *
 * This function prints out the elements of an array.
 * The print format is 10 elements per line.
 *
 * @param *arr Pointer to an array of data
 * @param SIZE Length of the array
 *
 */
void print_array(const unsigned char *arr, unsigned int SIZE);

/**
 * @brief Print out all statistics of an array
 *
 * This function takes an array and its length.
 * Then, it performs all statistical analyis on the array.
 * Finally, it prints out all the statistics of the array.
 *
 * The statistical analysis in this function includes: find maximum,
 * minimum, median, mean values.
 *
 * This function does not return any value.
 *
 * @param *arr Pointer to an array of data
 * @param SIZE Length of the array
 */
void print_statistics(const unsigned char *arr, unsigned int SIZE);

/**
 * @brief Sort an array in descending order
 *
 * This function sorts an array in descending order using
 * insertion sort algorithm.
 *
 * This function MODIFIES the original array
 * and does not return any value.
 *
 * @param *arr Pointer to an array of data
 * @param SIZE Length of the array
 */
void sort_array(unsigned char *arr, unsigned int SIZE);
#endif /* __STATS_H__ */
