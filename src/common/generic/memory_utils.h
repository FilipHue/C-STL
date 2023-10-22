/**
 * @file memory_utils.h
 * @author Secareanu Filip
 * @brief This module provides a safe wrapper for calloc.
 * @version 0.1
 * @date 2023-10-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef MEMORY_UTILS_H
#define MEMORY_UTILS_H

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Allocates memory and checks if the allocation was successful.
 * 
 * @param size The size of the memory to be allocated.
 * @param line The line where the function was called.
 * @return void* The pointer to the allocated memory.
 */
void* safe_calloc(size_t nmemb, size_t size, unsigned int line);

#define SAFE_CALLOC(nmemb, size) safe_calloc(nmemb, size, __LINE__);

#endif // MEMORY_UTILS_H
