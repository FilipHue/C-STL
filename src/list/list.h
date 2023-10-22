/**
 * @file list.h
 * @author Secareanu Filip
 * @brief 
 * @version 0.1
 * @date 2023-10-22
 * 
 * @copyright Copyright (c) 2023
 * 
 * This module provides methods to manipulate and query doubly linked lists.
 * It includes functions for creating, destroying, inserting, removing, 
 * querying, and modifying the DLL. Additionally, it supports custom free 
 * and print functions for flexibility in handling various data types.
 * 
 */

#ifndef LIST_H
#define LIST_H

#include "../common/error/error.h"
#include "../common/generic/container_utils.h"
#include "../common/generic/memory_utils.h"

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>
#include <assert.h>
#include <stdarg.h>
#include <stdint.h>

/** 
 * @brief Node structure for the doubly linked list.
 * 
 */
typedef struct dll_node dll_node_t;
/**
 * @brief Main structure representing the doubly linked list.
 * 
 */
typedef struct dll_list dll_list_t;

struct dll_node {
    void *data;                 /**< The data held by the node*/
    dll_node_t *next;           /**< The next node in the list*/
    dll_node_t *prev;           /**< The previous node in the list*/
};

struct dll_list {
    dll_node_t *head;           /**< The head of the list*/
    dll_node_t *tail;           /**< The tail of the list*/

    size_t data_size;           /**< The size of the data held by the list*/
    size_t size;                /**< The size of the list*/

    container_error_t error;    /**< The error code of the last operation*/

    free_function_t free_fn;    /**< The custom free function*/
    print_function_t print_fn;  /**< The custom print function*/
};

/**
 * @brief Creates a new doubly linked list.
 * 
 * @param data_size The size of the data held by the list.
 * @param free_fn The custom free function.
 * @param print_fn The custom print function.
 * @return dll_list_t* The newly created list.
 */
dll_list_t *dll_create(size_t data_size, free_function_t free_fn, print_function_t print_fn);

/**
 * @brief Destroys the list and frees all the memory.
 * 
 * @param list The list to be destroyed.
 */
void dll_destroy(dll_list_t **list);

/**
 * @brief Retrieves the data from the beginning of the list.
 * 
 * @param list The list to retrieve data from.
 * @return void* Data from the tail node.
 */
void* dll_front(dll_list_t *list);

/**
 * @brief Retrieves the data from the end of the list.
 * 
 * @param list The list to retrieve data from.
 * @return void* Data from the head node.
 */
void* dll_back(dll_list_t *list);


/**
 * @brief Appends data to the end of the list.
 * 
 * @param list The list to append data to.
 * @param data The data to be appended.
 */
void dll_append(dll_list_t *list, void *data);

/**
 * @brief Prepends data to the beginning of the list.
 * 
 * @param list The list to prepend data to.
 * @param data The data to be prepended.
 */
void dll_prepend(dll_list_t *list, void *data);

/**
 * @brief Inserts data at the specified index.
 * 
 * @param list The list to insert data to.
 * @param index The index at which to insert the data.
 * @param data The data to be inserted.
 */
void dll_insert(dll_list_t *list, size_t index, void *data);


/**
 * @brief Removes a node at a specific index from the list.
 * @param list The list to remove the node from.
 * @param index The index of the node to remove.
 */
void dll_remove(dll_list_t *list, size_t index);

/**
 * @brief Removes nodes from the list based on a predicate function.
 * @param list The list to remove nodes from.
 * @param predicate Function pointer determining nodes to remove.
 */
void dll_remove_if(dll_list_t *list, predicate_function_t predicate);

/**
 * @brief Removes duplicate nodes from the list.
 * @param list The list to remove duplicates from.
 */
void dll_unique(dll_list_t *list);

/**
 * @brief Removes duplicate nodes based on a custom comparison function.
 * @param list The list to remove duplicates from.
 * @param compare_fn Function pointer to compare nodes.
 */
void dll_unique_f(dll_list_t *list, unique_function_t compare_fn);

/**
 * @brief Retrieves data at a specific index from the list.
 * @param list The list to retrieve data from.
 * @param index The index to retrieve data from.
 * @return Data at the specified index.
 */
void dll_clear(dll_list_t *list);


/**
 * @brief Retrieves data at a specific index from the list.
 * @param list The list to retrieve data from.
 * @param index The index to retrieve data from.
 * @return Data at the specified index.
 */
void* dll_get(dll_list_t *list, size_t index);

/**
 * @brief Finds the index of a specific data item in the list.
 * @param list The list to search.
 * @param data The data to find.
 * @return Index of the data item or a value indicating not found.
 */
size_t dll_find(dll_list_t *list, void *data);

/**
 * @brief Finds the index of a specific data item using a custom function.
 * @param list The list to search.
 * @param data The data to find.
 * @param find_fn Custom function to use for searching.
 * @return Index of the data item or a value indicating not found.
 */
size_t dll_find_f(dll_list_t *list, void *data, find_function_t find_fn);

/**
 * @brief Sorts the list based on a custom comparison function.
 * @param list The list to sort.
 * @param compare_fn The comparison function to use for sorting.
 * @param order The desired sort order.
 */
void dll_sort(dll_list_t *list, compare_function_t compare_fn, sort_order_t order);

/**
 * @brief Reverses the order of nodes in the list.
 * @param list The list to reverse.
 */
void dll_reverse(dll_list_t *list);


/**
 * @brief Retrieves the size (number of nodes) of the list.
 * @param list The list to retrieve the size for.
 * @return The size of the list.
 */
size_t dll_size(dll_list_t *list);

/**
 * @brief Determines if the list is empty.
 * @param list The list to check.
 * @return true if the list is empty, false otherwise.
 */
bool dll_empty(dll_list_t *list);


/**
 * @brief Prints the list using the assigned print function.
 * @param list The list to print.
 */
void dll_print(dll_list_t *list);

#endif // LIST_H
