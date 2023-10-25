/**
 * @file queue.h
 * @author Secareanu Filip
 * @brief 
 * @version 0.1
 * @date 2023-10-25
 * 
 * @copyright Copyright (c) 2023
 * This file provides the structure definition, function prototypes, and
 * documentation for a generic queue data structure. The queue is implemented
 * using a dynamic array, allowing it to resize based on the number of elements
 * and specified growth and shrink thresholds. 
 *
 * The queue is designed to be generic, meaning it can store elements of any 
 * data type. To accommodate for different data types, the client code must 
 * provide the size of the data type and optional custom functions for memory
 * management and printing. 
 *
 * The implementation provides standard queue operations such as enqueue (to
 * add elements to the rear), dequeue (to remove elements from the front),
 * checking if the queue is empty, and retrieving the size of the queue. 
 * Additionally, it provides functions to clear the queue, resize the internal
 * array, convert the queue to an array, and populate the queue from an array.
 *
 * Error handling is facilitated through the `container_error_t` type, and the
 * queue keeps track of the last error that occurred. This allows client code
 * to check the status of the queue and handle errors as necessary.
 *
 * This file is part of a larger container library, and it includes other
 * necessary headers from the library for error handling and generic
 * functionality.
 */

#ifndef QUEUE_H
#define QUEUE_H

#include "../common/error/error.h"
#include "../common/generic/memory_utils.h"
#include "../common/generic/container_utils.h"

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/**
 * @struct queue
 * @brief Represents a generic queue data structure.
 *
 * This structure holds all necessary information to manage a generic queue,
 * allowing storage of any data type, and provides functionality for enqueue,
 * dequeue, and other queue-related operations.
 */
typedef struct queue queue_t;

struct queue {
    void *data; ///< Pointer to the dynamic array storing the queue elements.
    size_t front; ///< Index of the front of the queue.
    size_t rear; ///< Index of the rear of the queue.
    size_t data_size; ///< Size in bytes of the data type stored in the queue.
    size_t size; ///< Current number of elements in the queue.
    size_t capacity; ///< Current capacity of the queue.
    float grow_treshold; ///< Load factor threshold to trigger capacity growth.
    float shrink_treshold; ///< Load factor threshold to trigger capacity shrinking.
    container_error_t error; ///< Error status of the last queue operation.
    free_function_t free_function; ///< Function to free data elements.
    print_function_t print_function; ///< Function to print data elements.
};

/**
 * @brief Creates and initializes a new queue.
 *
 * Allocates and initializes a new queue with the specified initial capacity,
 * growth and shrink thresholds, and optional custom memory management functions.
 *
 * @param data_size Size in bytes of the data type to be stored in the queue.
 * @param capacity Initial capacity of the queue.
 * @param grow_treshold Load factor threshold to trigger capacity growth.
 * @param shrink_treshold Load factor threshold to trigger capacity shrinking.
 * @param free_function Optional function to free data elements.
 * @param print_function Optional function to print data elements.
 * @return Pointer to the newly created queue, or NULL if memory allocation fails.
 */
queue_t *queue_create(size_t data_size, size_t capacity, float grow_treshold, float shrink_treshold, free_function_t free_function, print_function_t print_function);

/**
 * @brief Destroys a queue and frees its memory.
 *
 * Frees the memory used by the queue's dynamic array and the queue itself. If a
 * free function is provided, it is used to free the individual elements.
 *
 * @param queue Double pointer to the queue to be destroyed.
 * @param flag Flags controlling how the queue elements should be freed.
 */
void queue_destroy(queue_t **queue, container_flags_t flag);

/**
 * @brief Enqueues an element to the queue.
 *
 * Adds an element to the rear of the queue. If the queue is full, it is resized
 * to accommodate the new element.
 *
 * @param queue Pointer to the queue.
 * @param data Pointer to the data to be enqueued.
 */
void queue_enqueue(queue_t *queue, void *data);

/**
 * @brief Dequeues an element from the queue.
 *
 * Removes and returns the element at the front of the queue. If the queue is
 * sufficiently empty after the dequeue operation, it may be resized to save
 * memory.
 *
 * @param queue Pointer to the queue.
 * @return Pointer to the dequeued data, or NULL if the queue is empty.
 */
void *queue_dequeue(queue_t *queue);

/**
 * @brief Retrieves, but does not remove, the front element of the queue.
 *
 * @param queue Pointer to the queue.
 * @return Pointer to the front data, or NULL if the queue is empty.
 */
void *queue_front(queue_t *queue);

/**
 * @brief Clears all elements from the queue.
 *
 * Removes all elements from the queue, optionally freeing their memory if a
 * free function is provided.
 *
 * @param queue Pointer to the queue.
 * @param flag Flags controlling how the queue elements should be freed.
 */
void queue_clear(queue_t *queue, container_flags_t flag);

/**
 * @brief Checks if the queue is empty.
 *
 * @param queue Pointer to the queue.
 * @return true if the queue is empty, false otherwise.
 */
bool queue_is_empty(queue_t *queue);

/**
 * @brief Retrieves the number of elements in the queue.
 *
 * @param queue Pointer to the queue.
 * @return Number of elements in the queue.
 */
size_t queue_size(queue_t *queue);

/**
 * @brief Copies the queue elements to an array.
 *
 * @param queue Pointer to the queue.
 * @param array Pointer to the array where the queue elements will be copied.
 */
void queue_to_array(queue_t *queue, void *array);

/**
 * @brief Fills the queue with elements from an array.
 *
 * @param queue Pointer to the queue.
 * @param array Pointer to the array containing the data to be added to the queue.
 * @param array_size Number of elements in the array.
 */
void queue_from_array(queue_t *queue, void *array, size_t array_size);

/**
 * @brief Resizes the queue to a new capacity.
 *
 * @param queue Pointer to the queue.
 * @param new_capacity The new capacity for the queue.
 */
void queue_resize(queue_t *queue, size_t new_capacity);

/**
 * @brief Prints the queue elements.
 *
 * Prints the queue elements using the provided print function.
 *
 * @param queue Pointer to the queue.
 */
void queue_print(queue_t *queue);

#endif // QUEUE_H
