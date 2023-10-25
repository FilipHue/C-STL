/**
 * @file container_utils.h
 * @author Secareanu Filip
 * @brief Provides utility definitions and functions for various container types.
 * @version 0.1
 * @date 2023-10-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef CONTAINER_UTILS_H
#define CONTAINER_UTILS_H

#include "../error/error.h"

#include <stdbool.h>

/** 
 * @brief Enumeration of supported container types.
 */
typedef enum container_type {
    CONTAINER_LIST,                 /**< Represents a list container. */
    CONTAINER_STACK,                /**< Represents a stack container. */
    CONTAINER_QUEUE,                /**< Represents a queue container. */
    CONTAINER_HASH_TABLE,           /**< Represents a hash table container. */
    CONTAINER_INVALID_TYPE          /**< Represents an invalid or unrecognized container type. */
} container_type_t;

/** 
 * @brief Enumeration of supported container flags.
 */
typedef enum container_flags {
    CF_NONE,                        /**< No flags set. */
    CF_FREE_DATA                    /**< Flag indicating that the container should free the data when destroyed or cleared. */
} container_flags_t;

/** 
 * @brief Enumeration of supported sort orders.
 */
typedef enum sort_order {
    SORT_ASCENDING,                 /**< Sort in ascending order. */
    SORT_DESCENDING                 /**< Sort in descending order. */
} sort_order_t;

/**
 * @brief Pointer to a function that frees allocated memory for container data.
 * @param data The data to be freed.
 */
typedef void (*free_function_t)(void *data);

/**
 * @brief Pointer to a function that prints container data.
 * @param data The data to be printed.
 */
typedef void (*print_function_t)(const void *data);

/**
 * @brief Pointer to a function that compares two data items for sorting or searching.
 * @param data1 The first data item to compare.
 * @param data2 The second data item to compare.
 * @return Integer value less than, equal to, or greater than zero if data1 is 
 *         found, respectively, to be less than, to match, or be greater than data2.
 */
typedef int (*compare_function_t)(const void *data1, const void *data2);

/**
 * @brief Pointer to a function that checks a condition on a data item.
 * @param data The data item to check.
 * @return true if the condition is met, false otherwise.
 */
typedef bool (*predicate_function_t)(const void *data);

/**
 * @brief Pointer to a function that checks equality of two data items.
 * @param data1 The first data item to check.
 * @param data2 The second data item to check.
 * @return true if the two data items are considered equal, false otherwise.
 */
typedef bool (*find_function_t)(const void *data1, const void *data2);

/**
 * @brief Pointer to a function that checks uniqueness of two data items.
 * @param data1 The first data item to check.
 * @param data2 The second data item to check.
 * @return true if the two data items are considered unique, false if they are duplicates.
 */
typedef bool (*unique_function_t)(const void *data1, const void *data2);

/**
 * @brief Retrieves the error status for a given container type.
 * @param container Pointer to the container to check the error status for.
 * @param type Enumeration value representing the type of the container.
 * @return The current error status of the container.
 */
container_error_t get_error(void *container, container_type_t type);

#endif // CONTAINER_UTILS_H
