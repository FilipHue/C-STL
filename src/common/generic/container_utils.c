/**
 * @file container_utils.c
 * @author Secareanu Filip
 * @brief   This module provides utility methods to manipulate and query containers.
 * @version 0.1
 * @date 2023-10-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "container_utils.h"

#include "../../list/list.h"
#include "../../stack/stack.h"
#include "../../queue/queue.h"

container_error_t get_error(void *container, container_type_t type)
{
    container_error_t error;

    switch (type) {
        case CONTAINER_LIST:
            error = ((dll_list_t *)container)->error;
            break;
        // TODO: Add other container types
        case CONTAINER_STACK:
            error = ((stack_t *)container)->error;
            break;
        case CONTAINER_QUEUE:
            error = ((queue_t *)container)->error;
            break;
        // case CONTAINER_HASH_TABLE:
        //     error = ((hash_table_t *)container)->error;
        //     break;
        default:
            error = ERROR_NONE;
            break;
    }

    return error;
}
