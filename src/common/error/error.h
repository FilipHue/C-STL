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
    ERROR_NONE,
    ERROR_NULL,
    ERROR_MEMEORY_ALLOCATION,
    ERROR_INVALID_DATA,
    ERROR_INVALID_INDEX
};

#endif // ERROR_H