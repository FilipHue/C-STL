/**
 * @file stack.h
 * @author Secareanu Filip
 * @brief   This is the header file for the stack implementation.
 * @version 0.1
 * @date 2023-10-25
 * 
 * @copyright Copyright (c) 2023
 * 
 * This file defines the structure and function prototypes required to implement
 * a generic stack data structure. The stack is implemented using a dynamic
 * array, providing efficient resizing capabilities based on the number of
 * elements and specified growth and shrink thresholds.
 *
 * The stack is designed to be generic, supporting storage of any data type.
 * Client code is required to provide the size of the data type, and optionally,
 * custom memory management and printing functions, to ensure proper operation
 * for various data types.
 *
 * Standard stack operations are supported, including push (to add elements to
 * the top), pop (to remove elements from the top), and peek (to view the top
 * element without removing it). Additional utilities provided include checking
 * if the stack is empty, retrieving the current size of the stack, clearing the
 * stack, resizing the internal array, and converting between stacks and arrays.
 *
 * Error handling is integral to the implementation, with the stack keeping track
 * of the last occurred error using the `container_error_t` type. This allows
 * for robust error checking and handling by client code.
 *
 * This stack implementation is part of a larger container library, which
 * includes various utilities for generic programming and error management,
 * ensuring consistency and ease of use across different data structures.
 */

#ifndef STACK_H
#define STACK_H

#include "../common/error/error.h"
#include "../common/generic/memory_utils.h"
#include "../common/generic/container_utils.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/**
 * @brief The primary structure representing a generic stack.
 * 
 * Encapsulates the properties and behavior of a stack, allowing for generic 
 * data storage, dynamic resizing, and custom function application for 
 * memory management and data printing.
 */
typedef struct stack stack_t;

struct stack {
    void *data;                         ///< Pointer to the underlying dynamic array storing stack elements.
    size_t top;                         ///< Index of the top element in the stack.
    size_t data_size;                   ///< Size (in bytes) of the type of data this stack holds.
    size_t size;                        ///< Current number of elements in the stack.
    size_t capacity;                    ///< Maximum number of elements the stack can currently hold without resizing.
    float grow_treshold;                ///< Capacity threshold for triggering stack growth.
    float shrink_treshold;              ///< Capacity threshold for triggering stack reduction.
    container_error_t error;            ///< Holds any error status related to the latest stack operation.
    free_function_t free_function;      ///< Optional custom function for data deallocation.
    print_function_t print_function;    ///< Optional custom function for displaying stack data.
};

/**
 * @brief Creates a new generic stack instance.
 *
 * @param data_size        Size in bytes of the type of data the stack will hold.
 * @param capacity         Initial capacity for the stack.
 * @param grow_treshold    Percentage (0-1) to determine when the stack needs to expand.
 * @param shrink_treshold  Percentage (0-1) to determine when the stack needs to shrink.
 * @param free_function    Optional custom function for data deallocation.
 * @param print_function   Optional custom function for displaying stack data.
 * @return A pointer to the initialized stack.
 */
stack_t *stack_create(size_t data_size, size_t capacity, float grow_treshold, float shrink_treshold, free_function_t free_function, print_function_t print_function);

/**
 * @brief Frees memory occupied by the stack.
 *
 * Destroys the stack and, depending on the flag, can also deallocate memory of individual data items.
 *
 * @param stack  Pointer to the stack's pointer. Will set *stack to NULL after deallocation.
 * @param flag   Determines whether to free the stored data as well.
 */
void stack_destroy(stack_t **stack, container_flags_t flag);

/**
 * @brief Pushes an item onto the stack.
 *
 * @param stack  A pointer to the stack.
 * @param data   Pointer to the data item to push onto the stack.
 */
void stack_push(stack_t *stack, void *data);

/**
 * @brief Pops an item from the stack.
 *
 * Removes the top item from the stack and returns it. It's the caller's responsibility to free the returned data when done.
 *
 * @param stack  A pointer to the stack.
 * @return Pointer to the popped data.
 */
void *stack_pop(stack_t *stack);

/**
 * @brief Retrieves, but does not remove, the top item from the stack.
 *
 * @param stack  A pointer to the stack.
 * @return Pointer to the top data item.
 */
void *stack_peek(stack_t *stack);

/**
 * @brief Clears the stack of all items without destroying the stack itself.
 *
 * @param stack  A pointer to the stack.
 * @param flag   Determines whether to free the stored data as well.
 */
void stack_clear(stack_t *stack, container_flags_t flag);

/**
 * @brief Checks if the stack is empty.
 *
 * @param stack  A pointer to the stack.
 * @return true if the stack is empty, false otherwise.
 */
bool stack_is_empty(stack_t *stack);

/**
 * @brief Retrieves the number of items in the stack.
 *
 * @param stack  A pointer to the stack.
 * @return Number of items in the stack.
 */
size_t stack_size(stack_t *stack);

/**
 * @brief Copies the stack content into a provided array.
 *
 * The caller must ensure that the provided array has enough space to accommodate all stack items.
 *
 * @param stack  A pointer to the stack.
 * @param array  Pointer to the target array.
 */
void stack_to_array(stack_t *stack, void *array);

/**
 * @brief Populates the stack from the provided array.
 *
 * @param stack      A pointer to the stack.
 * @param array      Pointer to the source array.
 * @param array_size Number of items in the source array.
 */
void stack_from_array(stack_t *stack, void *array, size_t array_size);

/**
 * @brief Resizes the stack to the given capacity.
 *
 * If the new capacity is smaller than the current size, items will be lost.
 *
 * @param stack        A pointer to the stack.
 * @param new_capacity The desired capacity for the stack.
 */
void stack_resize(stack_t *stack, size_t new_capacity);

/**
 * @brief Prints the content of the stack.
 *
 * Utilizes the custom print function provided during stack creation, if available.
 *
 * @param stack  A pointer to the stack.
 */
void stack_print(stack_t *stack);

#endif // STACK_H
