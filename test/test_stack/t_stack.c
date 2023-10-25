/**
 * @file t_stack.c
 * @author Secareanu Filip
 * @brief   This is the source file for the stack testing program.
 * @version 0.1
 * @date 2023-10-25
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "t_stack.h"

void print_int(const void *data)
{
    printf("%d ", *(int *)data);
}

void print_string(const void *data)
{
    printf("%s ", *(char **)data);
}

void print_list(const void *data) {
    dll_list_t *list = *(dll_list_t **) data;
    dll_print(list);
}

void free_list(void *data) {
    dll_list_t *list = *(dll_list_t **)data;
    dll_destroy(&list);
}

void stest_ints()
{   
    printf("Testing ints...\n\t");

    stack_t *stack;
    int data[5] = { 1, 2, 3, 4, 5 };
    int *popped_data;

    printf("Initializing stack...\n\t");

    stack = stack_create(sizeof(int), 5, 0.75, 0.25, NULL, print_int);
    assert(stack != NULL);
    assert(get_error(stack, CONTAINER_STACK) == ERROR_NONE);

    printf("Pushing data...\n\t");

    for (size_t i = 0; i < sizeof(data) / sizeof(int); i++) {
        stack_push(stack, &data[i]);
        assert(get_error(stack, CONTAINER_STACK) == ERROR_NONE);
    }
    assert(stack_size(stack) == 5);

    printf("Stack: ");
    stack_print(stack);
    printf("\n\t");

    printf("To array...\n\t\t");

    int array[5];
    stack_to_array(stack, array);

    for (size_t i = 0; i < sizeof(array) / sizeof(int); i++) {
        printf("%d ", array[i]);
    }

    printf("\n\t");

    printf(("Peeking data...\n\t"));

    popped_data = stack_peek(stack);
    assert(get_error(stack, CONTAINER_STACK) == ERROR_NONE);
    assert(*popped_data == 5);
    free(popped_data);

    printf("Popping data...\n\t");

    popped_data = stack_pop(stack);
    assert(get_error(stack, CONTAINER_STACK) == ERROR_NONE);
    assert(*popped_data == 5);

    popped_data = stack_pop(stack);
    assert(get_error(stack, CONTAINER_STACK) == ERROR_NONE);
    assert(*popped_data == 4);

    popped_data = stack_pop(stack);
    assert(get_error(stack, CONTAINER_STACK) == ERROR_NONE);
    assert(*popped_data == 3);

    assert(stack_size(stack) == 2);

    printf("Stack: ");
    stack_print(stack);
    printf("\n\t");

    printf("Clearing stack...\n\t");

    stack_clear(stack, CF_NONE);
    assert(get_error(stack, CONTAINER_STACK) == ERROR_NONE);
    assert(stack_size(stack) == 0);

    printf("Stack: ");
    stack_print(stack);
    printf("\n\t");

    printf("Poping data from empty stack...\n\t");

    popped_data = stack_pop(stack);
    assert(get_error(stack, CONTAINER_STACK) == ERROR_NONE);
    assert(popped_data == NULL);

    printf("Pushing data on cleared stack...\n\t");

    for (size_t i = 0; i < sizeof(data) / sizeof(int); i++) {
        stack_push(stack, &data[i]);
        assert(get_error(stack, CONTAINER_STACK) == ERROR_NONE);
    }

    printf("Stack: ");
    stack_print(stack);
    printf("\n\t");

    printf("Pushing more data...\n\t\t");

    printf("Stack capacity before: %zu\n\t\t", stack->capacity);
    printf("-- Resizing stack --\n\t\t");

    for (size_t i = 0; i < sizeof(data) / sizeof(int); i++) {
        stack_push(stack, &data[i]);
        assert(get_error(stack, CONTAINER_STACK) == ERROR_NONE);
    }

    printf("Stack capacity after: %zu\n\t\t", stack->capacity);

    printf("Stack: ");
    stack_print(stack);
    printf("\n\t");

    printf("Popping data until shrink treshold...\n\t\t");

    printf("Stack capacity before: %zu\n\t\t", stack->capacity);
    printf("-- Resizing stack --\n\t\t");

    size_t current_capacity = stack->capacity;
    while (stack->capacity >= current_capacity / 2) {
        printf("Stack size: %zu\n\t\t", stack->size);
        popped_data = stack_pop(stack);
        assert(get_error(stack, CONTAINER_STACK) == ERROR_NONE);
    }

    printf("Stack capacity after: %zu\n\t\t", stack->capacity);

    printf("Stack: ");
    stack_print(stack);
    printf("\n\t");

    printf("Destroying stack...\n\t");

    stack_destroy(&stack, CF_FREE_DATA);
    assert(stack == NULL);

    printf("Creating stack from array...\n\t");

    stack = stack_create(sizeof(int), 5, 0.75, 0.25, NULL, print_int);
    assert(get_error(stack, CONTAINER_STACK) == ERROR_NONE);
    assert(stack != NULL);

    int from_array[5] = {5, 4, 3, 2, 1};
    stack_from_array(stack, from_array, 5);
    assert(get_error(stack, CONTAINER_STACK) == ERROR_NONE);

    printf("Stack: ");
    stack_print(stack);
    printf("\n\t");

    printf("Destroying stack...\n\n");

    stack_destroy(&stack, CF_FREE_DATA);
    assert(stack == NULL);
}

void stest_strings()
{
    printf("Testing strings...\n\t");

    stack_t *stack;
    char *data[5] = { "one", "two", "three", "four", "five" };
    char *popped_data;

    printf("Initializing stack...\n\t");

    stack = stack_create(sizeof(char *), 5, 0.75, 0.25, NULL, print_string);
    assert(stack != NULL);
    assert(get_error(stack, CONTAINER_STACK) == ERROR_NONE);

    printf("Pushing data...\n\t");

    for (size_t i = 0; i < sizeof(data) / sizeof(char *); i++) {
        stack_push(stack, &data[i]);
        assert(get_error(stack, CONTAINER_STACK) == ERROR_NONE);
    }
    assert(stack_size(stack) == 5);

    printf("Stack: ");
    stack_print(stack);
    printf("\n\t");

    printf("To array...\n\t\t");

    char *array[5];
    stack_to_array(stack, array);

    for (size_t i = 0; i < sizeof(array) / sizeof(char *); i++) {
        printf("%s ", array[i]);
    }

    printf("\n\t");

    printf(("Peeking data...\n\t"));

    popped_data = stack_peek(stack);
    assert(get_error(stack, CONTAINER_STACK) == ERROR_NONE);
    assert(strcmp(*(char **)popped_data, "five") == 0);
    free(popped_data);

    printf("Popping data...\n\t");

    popped_data = stack_pop(stack);
    assert(get_error(stack, CONTAINER_STACK) == ERROR_NONE);
    assert(strcmp(*(char **)popped_data, "five") == 0);

    popped_data = stack_pop(stack);
    assert(get_error(stack, CONTAINER_STACK) == ERROR_NONE);
    assert(strcmp(*(char **)popped_data, "four") == 0);

    popped_data = stack_pop(stack);
    assert(get_error(stack, CONTAINER_STACK) == ERROR_NONE);
    assert(strcmp(*(char **)popped_data, "three") == 0);

    assert(stack_size(stack) == 2);

    printf("Stack: ");
    stack_print(stack);
    printf("\n\t");

    printf("Clearing stack...\n\t");

    stack_clear(stack, CF_NONE);
    assert(get_error(stack, CONTAINER_STACK) == ERROR_NONE);
    assert(stack_size(stack) == 0);

    printf("Stack: ");
    stack_print(stack);
    printf("\n\t");

    printf("Poping data from empty stack...\n\t");

    popped_data = stack_pop(stack);
    assert(get_error(stack, CONTAINER_STACK) == ERROR_NONE);
    assert(popped_data == NULL);

    printf("Pushing data on cleared stack...\n\t");

    for (size_t i = 0; i < sizeof(data) / sizeof(char *); i++) {
        stack_push(stack, &data[i]);
        assert(get_error(stack, CONTAINER_STACK) == ERROR_NONE);
    }

    printf("Stack: ");
    stack_print(stack);
    printf("\n\t");

    printf("Pushing more data...\n\t\t");

    printf("Stack capacity before: %zu\n\t\t", stack->capacity);
    printf("-- Resizing stack --\n\t\t");

    for (size_t i = 0; i < sizeof(data) / sizeof(char *); i++) {
        stack_push(stack, &data[i]);
        assert(get_error(stack, CONTAINER_STACK) == ERROR_NONE);
    }

    printf("Stack capacity after: %zu\n\t\t", stack->capacity);

    printf("Stack: ");
    stack_print(stack);
    printf("\n\t");

    printf("Popping data until shrink treshold...\n\t\t");

    printf("Stack capacity before: %zu\n\t\t", stack->capacity);
    printf("-- Resizing stack --\n\t\t");

    size_t current_capacity = stack->capacity;
    while (stack->capacity >= current_capacity / 2) {
        printf("Stack size: %zu\n\t\t", stack->size);
        popped_data = stack_pop(stack);
        assert(get_error(stack, CONTAINER_STACK) == ERROR_NONE);
    }

    printf("Stack capacity after: %zu\n\t\t", stack->capacity);

    printf("Stack: ");
    stack_print(stack);
    printf("\n\t");

    printf("Destroying stack...\n\t");

    stack_destroy(&stack, CF_FREE_DATA);
    assert(stack == NULL);

    printf("Creating stack from array...\n\t");

    stack = stack_create(sizeof(char *), 5, 0.75, 0.25, NULL, print_string);
    assert(get_error(stack, CONTAINER_STACK) == ERROR_NONE);
    assert(stack != NULL);

    char *from_array[5] = {"five", "four", "three", "two", "one"};
    stack_from_array(stack, from_array, 5);
    assert(get_error(stack, CONTAINER_STACK) == ERROR_NONE);

    printf("Stack: ");
    stack_print(stack);
    printf("\n\t");

    printf("Destroying stack...\n\n");

    stack_destroy(&stack, CF_FREE_DATA);
}

void stest_containers()
{
    printf("Testing lists in stack...\n\t");

    stack_t *stack;
    dll_list_t *lists[7];
    char *data[5] = { "one", "two", "three", "four", "five" };
    void *popped_data;
    
    printf("Initializing int lists...\n\t");

    for (int i = 0; i < 5; i++) {
        lists[i] = dll_create(sizeof(int), NULL, print_int);
        for (int j = 1; j <= (i + 1) * 2; j++) {
            dll_append(lists[i], &j);
        }
    }

    // [[1, 2], [1, 2, 3, 4], [1, 2, 3, 4, 5, 6], [1, 2, 3, 4, 5, 6, 7, 8], [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]

    printf("Initializing string lists...\n\t");

    for (int i = 5; i < 7; i++) {
        lists[i] = dll_create(sizeof(char *), NULL, print_string);
        for (int j = 0; j < 5; j++) {
            dll_append(lists[i], &data[j]);
        }
    }

    // [[one, two, three, four, five], [one, two, three, four, five]]

    printf("Initializing stack...\n\t");

    stack = stack_create(sizeof(dll_list_t *), 5, 0.6, 0.25, free_list, print_list);
    assert(stack != NULL);
    assert(get_error(stack, CONTAINER_STACK) == ERROR_NONE);

    printf("Pushing lists onto stack...\n\t");

    for (size_t i = 0; i < 5; i++) {
        stack_push(stack, &lists[i]);
        assert(get_error(stack, CONTAINER_STACK) == ERROR_NONE);
    }
    assert(stack_size(stack) == 5);

    printf("Stack: ");
    stack_print(stack);
    printf("\n\t");

    printf("To array...\n\t\t");

    dll_list_t *array[5];
    stack_to_array(stack, array);

    for (size_t i = 0; i < sizeof(array) / sizeof(dll_list_t *); i++) {
        dll_print(array[i]);
    }

    printf("\n\t");

    printf("Peeking top list from stack...\n\t\t");

    popped_data = stack_peek(stack);
    assert(get_error(stack, CONTAINER_STACK) == ERROR_NONE);

    printf("Peeked list: ");

    dll_print(*(dll_list_t **)popped_data);
    free(popped_data);
    printf("\n\t");

    printf("Popping lists from stack...\n\t");

    for (size_t i = 0; i < 3; i++) {
        popped_data = stack_pop(stack);
        assert(get_error(stack, CONTAINER_STACK) == ERROR_NONE);
    
        printf("Popped list: ");

        dll_print(*(dll_list_t **)popped_data);
        printf("\n\t");
    }
    assert(stack_size(stack) == 2);

    printf("Stack: ");
    stack_print(stack);
    printf("\n\t");

    printf("Clearing stack...\n\t");

    stack_clear(stack, CF_NONE);
    assert(get_error(stack, CONTAINER_STACK) == ERROR_NONE);
    assert(stack_size(stack) == 0);

    printf("Stack: ");
    stack_print(stack);
    printf("\n\t");

    printf("Pushing lists again after clearing...\n\t");

    for (size_t i = 0; i < 5; i++) {
        stack_push(stack, &lists[i]);
        assert(get_error(stack, CONTAINER_STACK) == ERROR_NONE);
    }

    printf("Stack: ");
    stack_print(stack);
    printf("\n\t");

    printf("Pushing more lists...\n\t\t");

    printf("Stack capacity before: %zu\n\t\t", stack->capacity);
    printf("-- Resizing stack --\n\t\t");

    for (size_t i = 5; i < 7; i++) {
        stack_push(stack, &lists[i]);
        assert(get_error(stack, CONTAINER_STACK) == ERROR_NONE);
    }

    printf("Stack capacity after: %zu\n\t\t", stack->capacity);

    printf("Stack: ");
    stack_print(stack);
    printf("\n\t");

    printf("Popping lists until shrink treshold...\n\t\t");

    printf("Stack capacity before: %zu\n\t\t", stack->capacity);
    printf("-- Resizing stack --\n\t\t");

    size_t current_capacity = stack->capacity;
    while (stack->capacity >= current_capacity / 2) {
        printf("Stack size: %zu\n\t\t", stack->size);
        popped_data = stack_pop(stack);
        assert(get_error(stack, CONTAINER_STACK) == ERROR_NONE);
        free_list(popped_data);
    }

    printf("Stack capacity after: %zu\n\t\t", stack->capacity);

    printf("Stack: ");
    stack_print(stack);
    printf("\n\t");

    printf("Destroying stack...\n\t");
    stack_destroy(&stack, CF_FREE_DATA);
    assert(stack == NULL);

    printf("Creating stack from array...\n\t");

    stack = stack_create(sizeof(dll_list_t *), 5, 0.75, 0.25, free_list, print_list);
    assert(get_error(stack, CONTAINER_STACK) == ERROR_NONE);
    assert(stack != NULL);

    dll_list_t *from_array[5];
    for (size_t i = 0; i < 5; i++) {
        from_array[i] = dll_create(sizeof(int), NULL, print_int);
        for (int j = 1; j <= (i + 1) * 2; j++) {
            dll_append(from_array[i], &j);
        }
    }

    // [[1, 2], [1, 2, 3, 4], [1, 2, 3, 4, 5, 6], [1, 2, 3, 4, 5, 6, 7, 8], [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]

    stack_from_array(stack, from_array, 5);

    printf("Stack: ");
    stack_print(stack);
    printf("\n\t");

    printf("Destroying stack...\n");

    stack_destroy(&stack, CF_FREE_DATA);
    assert(stack == NULL);
}
