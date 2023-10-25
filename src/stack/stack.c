/**
 * @file stack.c
 * @author Secareanu Filip
 * @brief   This is the source file for the stack implementation.
 * @version 0.1
 * @date 2023-10-25
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "stack.h"

stack_t *stack_create(size_t data_size, size_t capacity, float grow_treshold, float shrink_treshold, free_function_t free_function, print_function_t print_function)
{
    stack_t *stack;
    
    stack = SAFE_CALLOC(1, sizeof(stack_t));

    stack->data = SAFE_CALLOC(capacity, data_size);

    stack->top = SIZE_MAX;

    stack->data_size = data_size;
    stack->size = 0;
    stack->capacity = capacity;

    stack->grow_treshold = grow_treshold;
    stack->shrink_treshold = shrink_treshold;

    stack->error = ERROR_NONE;

    stack->free_function = free_function;
    stack->print_function = print_function;

    return stack;
}

void stack_destroy(stack_t **stack, container_flags_t flag)
{
    if (*stack == NULL) {
        return;
    }

    if (flag == CF_FREE_DATA && (*stack)->free_function) {
        while ((*stack)->size > 0) {
            void *source = (*stack)->data + ((*stack)->top * (*stack)->data_size);
            (*stack)->free_function(source);
            (*stack)->size--;
            (*stack)->top--;
        }
    }

    free((*stack)->data);
    free(*stack);

    *stack = NULL;
}

void stack_push(stack_t *stack, void *data)
{
    if (stack == NULL) {
        return;
    }

    if (data == NULL) {
        stack->error = ERROR_INVALID_DATA;
        return;
    }

    if (((float)stack->size) / (float)(stack->capacity) >= stack->grow_treshold) {
        stack_resize(stack, stack->capacity * 2);
    }

    if (stack->size == SIZE_MAX) {
        stack->top = 0;
    } else {
        stack->top++;
    }

    void *source = stack->data + ((stack->top) * stack->data_size);
    memcpy(source, data, stack->data_size);

    stack->size++;

    stack->error = ERROR_NONE;
}

void *stack_pop(stack_t *stack)
{
    if (stack == NULL) {
        return NULL;
    }

    if (stack->size == 0) {
        stack->error = ERROR_NONE;
        return NULL;
    }

    if (((float)stack->size) / (float)(stack->capacity) <= stack->shrink_treshold) {
        stack_resize(stack, stack->capacity / 2);
    }

    void *data;

    void *source = stack->data + ((stack->top) * stack->data_size);
    data = source;

    stack->size--;
    stack->top--;

    stack->error = ERROR_NONE;

    return data;
}

void *stack_peek(stack_t *stack)
{
    if (stack == NULL) {
        return NULL;
    }

    if (stack->size == 0) {
        return NULL;
    }

    void *data = SAFE_CALLOC(1, stack->data_size);

    void *source = stack->data + ((stack->top) * stack->data_size);
    memcpy(data, source, stack->data_size);

    stack->error = ERROR_NONE;

    return data;
}

void stack_clear(stack_t *stack, container_flags_t flag)
{
    if (stack == NULL) {
        return;
    }

    if (flag == CF_FREE_DATA && stack->free_function) {
        while (stack->size > 0) {
            void *source = stack->data + ((stack->top) * stack->data_size);
            stack->free_function(source);
            stack->size--;
            stack->top--;
        }
    } else {
        stack->top = SIZE_MAX;
        stack->size = 0;
    }

    stack->error = ERROR_NONE;
}

bool stack_is_empty(stack_t *stack)
{
    if (stack == NULL) {
        return true;
    }

    return stack->size == 0;
}

size_t stack_size(stack_t *stack)
{
    if (stack == NULL) {
        return SIZE_MAX;
    }

    return stack->size;
}

void stack_to_array(stack_t *stack, void *array)
{
    if (stack == NULL) {
        return;
    }

    if (array == NULL) {
        stack->error = ERROR_INVALID_DATA;
        return;
    }

    memcpy(array, stack->data, stack->size * stack->data_size);

    stack->error = ERROR_NONE;
}

void stack_from_array(stack_t *stack, void *array, size_t array_size)
{
    if (stack == NULL) {
        return;
    }

    if (array == NULL) {
        stack->error = ERROR_INVALID_DATA;
        return;
    }

    if (array_size == 0) {
        stack->error = ERROR_INVALID_DATA;
        return;
    }

    stack_clear(stack, CF_FREE_DATA);

    stack_resize(stack, array_size);

    memcpy(stack->data, array, array_size * stack->data_size);

    stack->size = array_size;
    stack->top = array_size - 1;

    stack->error = ERROR_NONE;
}

void stack_resize(stack_t *stack, size_t new_capacity)
{
    if (stack == NULL) {
        return;
    }

    stack->data = SAFE_REALLOC(stack->data, new_capacity * stack->data_size);

    stack->capacity = new_capacity;
}

// TODO Fix print function
void stack_print(stack_t *stack)
{
    if (stack == NULL) {
        return;
    }

    if (stack->print_function == NULL) {
        return;
    }

    for (size_t i = 0; i < stack->size; i++) {
        void *source = stack->data + (i * stack->data_size);
        stack->print_function(source);
    }
}
