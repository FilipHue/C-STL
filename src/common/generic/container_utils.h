#ifndef CONTAINER_UTILS_H
#define CONTAINER_UTILS_H

#include "../error/error.h"

#include <stdbool.h>

typedef enum container_type container_type_t;
typedef enum sort_order sort_order_t;

enum container_type {
    CONTAINER_LIST,
    CONTAINER_STACK,
    CONTAINER_QUEUE,
    CONTAINER_HASH_TABLE,
    CONTAINER_INVALID_TYPE
};

enum sort_order {
    SORT_ASCENDING,
    SORT_DESCENDING
};

typedef void (*free_function_t)(void *data);
typedef void (*print_function_t)(const void *data);

typedef bool (*compare_function_t)(const void *data1, const void *data2);
typedef bool (*predicate_function_t)(const void *data);
typedef bool (*find_function_t)(const void *data1, const void *data2);
typedef bool (*unique_function_t)(const void *data1, const void *data2);

container_error_t get_error(void *container, container_type_t type);

#endif // CONTAINER_UTILS_H
