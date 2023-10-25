/**
 * @file memory_utils.c
 * @author Secareanu Filip
 * @brief   This module provides methods to manipulate and query memory. 
 * @version 0.1
 * @date 2023-10-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "memory_utils.h"

void* safe_calloc(size_t nmemb, size_t size, unsigned int line) {
    void* ptr = calloc(nmemb, size);
    if (ptr == NULL) {
        fprintf(stderr, "[%s:%u] Out of memory (%ld bytes)\n", __FILE__, line, nmemb * size);
        exit(EXIT_FAILURE);
    }
    return ptr;
}

void *safe_realloc(void *ptr, size_t size, unsigned int line)
{
    void *new_ptr = realloc(ptr, size);
    if (new_ptr == NULL) {
        fprintf(stderr, "[%s:%u] Out of memory (%ld bytes)\n", __FILE__, line, size);
        exit(EXIT_FAILURE);
    }
    return new_ptr;
}
