/**
 * @file error.h
 * @author Secareanu Filip
 * @brief   This module provides an enum for error codes.
 * @version 0.1
 * @date 2023-10-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef ERROR_H
#define ERROR_H

typedef enum container_error container_error_t;
enum container_error {
    ERROR_NONE,                 // 0
    ERROR_NULL,                 // 1
    ERROR_MEMORY_ALLOCATION,    // 2
    ERROR_INVALID_DATA,         // 3
    ERROR_INVALID_INDEX,        // 4
    ERROR_INVALID_FUNCTION,     // 5
    ERROR_EMPTY                 // 6
};

#endif // ERROR_H