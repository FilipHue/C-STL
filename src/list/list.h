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

typedef struct dll_node dll_node_t;
typedef struct dll_list dll_list_t;

struct dll_node {
    void *data;
    dll_node_t *next;
    dll_node_t *prev;
};

struct dll_list {
    dll_node_t *head;
    dll_node_t *tail;

    size_t data_size;
    size_t size;

    container_error_t error;

    free_function_t free_fn;
    print_function_t print_fn;
};

dll_list_t *dll_create(size_t data_size, free_function_t free_fn, print_function_t print_fn);
void dll_destroy(dll_list_t **list);

void* dll_front(dll_list_t *list);

void dll_append(dll_list_t *list, void *data);
void dll_prepend(dll_list_t *list, void *data);
void dll_insert(dll_list_t *list, size_t index, void *data);

void dll_remove(dll_list_t *list, size_t index);
void dll_remove_if(dll_list_t *list, predicate_function_t predicate);
void dll_clear(dll_list_t *list);

size_t dll_size(dll_list_t *list);
bool dll_empty(dll_list_t *list);

void dll_print(dll_list_t *list);

#endif // LIST_H
