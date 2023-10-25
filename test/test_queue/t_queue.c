/**
 * @file t_queue.c
 * @author Secareanu Filip
 * @brief   This is the implementation for the queue testing program.
 * @version 0.1
 * @date 2023-10-25
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "t_queue.h"

void qprint_int(const void *data)
{
    printf("%d ", *(int *)data);
}

void qprint_string(const void *data)
{
    printf("%s ", *(char **)data);
}

void qstack_print(const void *data)
{
    stack_print(*(stack_t **)data);
}

void qdll_list_print(const void *data)
{
    dll_print(*(dll_list_t **)data);
}

void qstack_free(void *data)
{
    stack_destroy((stack_t **)data, CF_FREE_DATA);
}

void qdll_list_free(void *data)
{
    dll_destroy((dll_list_t **)data);
}

void qtest_int()
{
    printf("Testing queue with integers...\n\t");

    queue_t *queue;
    int data[5] = {1, 2, 3, 4, 5};
    int *popped_data;

    printf("Initializing queue...\n\t");

    queue = queue_create(sizeof(int), 5, 0.75, 0.25, NULL, qprint_int);
    assert(queue != NULL);
    assert(get_error(queue, CONTAINER_QUEUE) == ERROR_NONE);

    printf("Enqueuing data...\n\t");

    for (size_t i = 0; i < 5; i++)
    {
        queue_enqueue(queue, &data[i]);
        assert(get_error(queue, CONTAINER_QUEUE) == ERROR_NONE);
    }
    assert(queue_size(queue) == 5);

    printf("Queue: ");
    queue_print(queue);
    printf("\n\t");

    printf("Peeking data...\n\t");

    popped_data = queue_front(queue);
    assert(get_error(queue, CONTAINER_QUEUE) == ERROR_NONE);
    assert(*popped_data == data[0]);
    free(popped_data);

    printf("Dequeuing data...\n\t");

    for (size_t i = 0; i < 5; i++)
    {
        popped_data = queue_dequeue(queue);
        assert(get_error(queue, CONTAINER_QUEUE) == ERROR_NONE);
        assert(*popped_data == data[i]);
    }

    printf("Queue: ");
    queue_print(queue);
    printf("\n\t");

    printf("From array...\n\t");

    int from_array[5] = {1, 2, 3, 4, 5};
    queue_from_array(queue, from_array, 5);
    assert(get_error(queue, CONTAINER_QUEUE) == ERROR_NONE);
    assert(queue_size(queue) == 5);

    printf("Queue: ");
    queue_print(queue);
    printf("\n\t");

    printf("To array...\n\t");

    int to_array[5];
    queue_to_array(queue, to_array);
    assert(get_error(queue, CONTAINER_QUEUE) == ERROR_NONE);
    assert(queue_size(queue) == 5);

    printf("Array: ");
    for (size_t i = 0; i < 5; i++)
    {
        printf("%d ", to_array[i]);
    }
    printf("\n\t");

    printf("Clearing queue...\n\t");

    queue_clear(queue, CF_NONE);
    assert(get_error(queue, CONTAINER_QUEUE) == ERROR_NONE);
    assert(queue_size(queue) == 0);

    printf("Queue: ");
    queue_print(queue);
    printf("\n\t");

    printf("Poping data from empty queue...\n\t");

    popped_data = queue_dequeue(queue);
    assert(get_error(queue, CONTAINER_QUEUE) == ERROR_EMPTY);
    assert(popped_data == NULL);

    printf("Enqueuing data on cleared queue...\n\t");

    for (size_t i = 0; i < 5; i++)
    {
        queue_enqueue(queue, &data[i]);
        assert(get_error(queue, CONTAINER_QUEUE) == ERROR_NONE);
    }

    printf("Queue: ");
    queue_print(queue);
    printf("\n\t");

    printf("Enqueuing data on full queue...\n\t\t");

    printf("Queue capacity before: %zu\n\t\t", queue->capacity);
    printf("--Resize queue--\n\t\t");

    for (size_t i = 0; i < 5; i++)
    {
        queue_enqueue(queue, &data[i]);
        assert(get_error(queue, CONTAINER_QUEUE) == ERROR_NONE);
    }

    printf("Queue capacity after: %zu\n\t\t", queue->capacity);

    printf("Queue: ");
    queue_print(queue);
    printf("\n\t");

    printf("Dequeuing data until shrink trehold...\n\t\t");

    printf("Queue capacity before: %zu\n\t\t", queue->capacity);
    printf("--Resize queue--\n\t\t");

    size_t current_capacity = queue->capacity;
    while (queue->capacity >= current_capacity) {
        printf("Queue size: %zu\n\t\t", queue->size);
        popped_data = queue_dequeue(queue);
        assert(get_error(queue, CONTAINER_QUEUE) == ERROR_NONE);
    }

    printf("Queue capacity after: %zu\n\t\t", queue->capacity);

    printf("Queue: ");
    queue_print(queue);
    printf("\n\t");

    printf("Destroying queue...\n\n");

    queue_destroy(&queue, CF_NONE);
    assert(queue == NULL);
}

void qtest_string()
{
    printf("Testing queue with strings...\n\t");

    queue_t *queue;
    char *data[5] = {"one", "two", "three", "four", "five"};
    char *popped_data;

    printf("Initializing queue...\n\t");

    queue = queue_create(sizeof(char *), 5, 0.5, 0.25, NULL, qprint_string);
    assert(queue != NULL);
    assert(get_error(queue, CONTAINER_QUEUE) == ERROR_NONE);

    printf("Enqueuing data...\n\t");

    for (size_t i = 0; i < 5; i++)
    {
        queue_enqueue(queue, &data[i]);
        assert(get_error(queue, CONTAINER_QUEUE) == ERROR_NONE);
    }
    assert(queue_size(queue) == 5);

    printf("Queue: ");
    queue_print(queue);
    printf("\n\t");

    printf("Peeking data...\n\t");

    popped_data = queue_front(queue);
    assert(get_error(queue, CONTAINER_QUEUE) == ERROR_NONE);
    assert(strcmp(*(char **)popped_data, "one") == 0);
    free(popped_data);

    printf("Dequeuing data...\n\t");

    for (size_t i = 0; i < 5; i++)
    {
        popped_data = queue_dequeue(queue);
        assert(get_error(queue, CONTAINER_QUEUE) == ERROR_NONE);
        assert(strcmp(*(char **)popped_data, data[i]) == 0);
    }

    printf("Queue: ");
    queue_print(queue);
    printf("\n\t");

    printf("From array...\n\t");

    char *from_array[5] = {"one", "two", "three", "four", "five"};
    queue_from_array(queue, from_array, 5);
    assert(get_error(queue, CONTAINER_QUEUE) == ERROR_NONE);
    assert(queue_size(queue) == 5);

    printf("Queue: ");
    queue_print(queue);
    printf("\n\t");

    printf("To array...\n\t");

    char *to_array[5];
    queue_to_array(queue, to_array);
    assert(get_error(queue, CONTAINER_QUEUE) == ERROR_NONE);
    assert(queue_size(queue) == 5);

    printf("Array: ");
    for (size_t i = 0; i < 5; i++)
    {
        printf("%s ", to_array[i]);
    }
    printf("\n\t");

    printf("Clearing queue...\n\t");

    queue_clear(queue, CF_FREE_DATA);
    assert(get_error(queue, CONTAINER_QUEUE) == ERROR_NONE);
    assert(queue_size(queue) == 0);

    printf("Queue: ");
    queue_print(queue);
    printf("\n\t");

    printf("Poping data from empty queue...\n\t");

    popped_data = queue_dequeue(queue);
    assert(get_error(queue, CONTAINER_QUEUE) == ERROR_EMPTY);
    assert(popped_data == NULL);

    printf("Enqueuing data on cleared queue...\n\t");

    for (size_t i = 0; i < 5; i++)
    {
        queue_enqueue(queue, &data[i]);
        assert(get_error(queue, CONTAINER_QUEUE) == ERROR_NONE);
    }

    printf("Queue: ");
    queue_print(queue);
    printf("\n\t");

    printf("Enqueuing data on full queue...\n\t\t");

    printf("Queue capacity before: %zu\n\t\t", queue->capacity);
    printf("--Resize queue--\n\t\t");

    for (size_t i = 0; i < 5; i++)
    {
        queue_enqueue(queue, &data[i]);
        assert(get_error(queue, CONTAINER_QUEUE) == ERROR_NONE);
    }

    printf("Queue capacity after: %zu\n\t\t", queue->capacity);

    printf("Queue: ");
    queue_print(queue);
    printf("\n\t");

    printf("Dequeuing data until shrink treshold...\n\t\t");

    printf("Queue capacity before: %zu\n\t\t", queue->capacity);
    printf("--Resize queue--\n\t\t");

    size_t current_capacity = queue->capacity;
    while (queue->capacity >= current_capacity) {
        printf("Queue size: %zu\n\t\t", queue->size);
        popped_data = queue_dequeue(queue);
        assert(get_error(queue, CONTAINER_QUEUE) == ERROR_NONE);
    }

    printf("Queue capacity after: %zu\n\t\t", queue->capacity);

    printf("Queue: ");
    queue_print(queue);
    printf("\n\t");

    printf("Destroying queue...\n\n");

    queue_destroy(&queue, CF_FREE_DATA);
    assert(queue == NULL);
}

void qtest_containers()
{
    printf("Testing queue with other containers\n\t");

    stack_t *s1;
    stack_t *s2;
    stack_t *s3;

    dll_list_t *l1;
    dll_list_t *l2;
    dll_list_t *l3;

    queue_t *queue;

    int data[5] = {1, 2, 3, 4, 5};
    char *data2[5] = {"one", "two", "three", "four", "five"};

    printf("Initializing stacks...\n\t");

    s1 = stack_create(sizeof(int), 3, 0.5, 0.25, NULL, qprint_int);
    assert(s1 != NULL);
    assert(get_error(s1, CONTAINER_STACK) == ERROR_NONE);

    s2 = stack_create(sizeof(char *), 5, 0.5, 0.25, NULL, qprint_string);
    assert(s2 != NULL);
    assert(get_error(s2, CONTAINER_STACK) == ERROR_NONE);

    s3 = stack_create(sizeof(int), 2, 0.5, 0.25, NULL, qprint_int);
    assert(s3 != NULL);
    assert(get_error(s3, CONTAINER_STACK) == ERROR_NONE);

    printf("Initializing doubly linked lists...\n\t");

    l1 = dll_create(sizeof(int), NULL, qprint_int);
    assert(l1 != NULL);
    assert(get_error(l1, CONTAINER_LIST) == ERROR_NONE);

    l2 = dll_create(sizeof(char *), NULL, qprint_string);
    assert(l2 != NULL);
    assert(get_error(l2, CONTAINER_LIST) == ERROR_NONE);

    l3 = dll_create(sizeof(int), NULL, qprint_int);
    assert(l3 != NULL);
    assert(get_error(l3, CONTAINER_LIST) == ERROR_NONE);

    printf("Pushing data to stacks...\n\t\t");

    for (size_t i = 0; i < 3; i++)
    {
        stack_push(s1, &data[i]);
        assert(get_error(s1, CONTAINER_STACK) == ERROR_NONE);
    }

    printf("Stack 1: ");
    stack_print(s1);
    printf("\n\t\t");

    for (size_t i = 0; i < 5; i++)
    {
        stack_push(s2, &data2[i]);
        assert(get_error(s2, CONTAINER_STACK) == ERROR_NONE);
    }

    printf("Stack 2: ");
    stack_print(s2);
    printf("\n\t\t");

    for (size_t i = 3; i < 5; i++)
    {
        stack_push(s3, &data[i]);
        assert(get_error(s3, CONTAINER_STACK) == ERROR_NONE);
    }

    printf("Stack 3: ");
    stack_print(s3);
    printf("\n\t");

    printf("Pushing data to lists...\n\t\t");

    for (size_t i = 0; i < 3; i++)
    {
        dll_append(l1, &data[i]);
        assert(get_error(l1, CONTAINER_LIST) == ERROR_NONE);
    }

    printf("List 1: ");
    dll_print(l1);
    printf("\n\t\t");

    for (size_t i = 0; i < 5; i++)
    {
        dll_insert(l2, 0, &data2[i]);
        assert(get_error(l2, CONTAINER_LIST) == ERROR_NONE);
    }

    printf("List 2: ");
    dll_print(l2);
    printf("\n\t\t");

    for (size_t i = 3; i < 5; i++)
    {
        dll_prepend(l3, &data[i]);
        assert(get_error(l3, CONTAINER_LIST) == ERROR_NONE);
    }

    printf("List 3: ");
    dll_print(l3);
    printf("\n\t");

    printf("Pushing stacks to queue...\n\t\t");

    queue = queue_create(sizeof(stack_t *), 5, 0.5, 0.25, qstack_free, qstack_print);
    assert(queue != NULL);
    assert(get_error(queue, CONTAINER_QUEUE) == ERROR_NONE);

    queue_enqueue(queue, &s1);
    assert(get_error(queue, CONTAINER_QUEUE) == ERROR_NONE);

    queue_enqueue(queue, &s2);
    assert(get_error(queue, CONTAINER_QUEUE) == ERROR_NONE);

    queue_enqueue(queue, &s3);
    assert(get_error(queue, CONTAINER_QUEUE) == ERROR_NONE);

    printf("Queue: ");
    queue_print(queue);
    printf("\n\t");

    printf("Popping stacks from queue...\n\t\t");

    void *popped_stack;

    popped_stack = queue_dequeue(queue);
    assert(get_error(queue, CONTAINER_QUEUE) == ERROR_NONE);

    printf("Popped stack 1: ");
    stack_print(*(stack_t **)popped_stack);
    qstack_free(popped_stack);
    printf("\n\t\t");

    printf("Queue: ");
    queue_print(queue);
    printf("\n\t");

    printf("To array...\n\t\t");

    stack_t *to_array[2];
    queue_to_array(queue, to_array);
    assert(get_error(queue, CONTAINER_QUEUE) == ERROR_NONE);

    printf("Array: ");
    for (size_t i = 0; i < 2; i++)
    {
        stack_print(to_array[i]);
    }

    printf("\n\t");

    printf("Clearing queue...\n\t\t");

    queue_clear(queue, CF_FREE_DATA);
    assert(get_error(queue, CONTAINER_QUEUE) == ERROR_NONE);

    printf("Queue: ");
    queue_print(queue);
    printf("\n\t");

    printf("Destroying queue...\n\t");

    queue_destroy(&queue, CF_FREE_DATA);
    assert(queue == NULL);

    printf("Pushing lists to queue...\n\t\t");

    queue = queue_create(sizeof(dll_list_t *), 5, 0.5, 0.25, qdll_list_free, qdll_list_print);
    assert(queue != NULL);

    queue_enqueue(queue, &l1);
    assert(get_error(queue, CONTAINER_QUEUE) == ERROR_NONE);

    queue_enqueue(queue, &l2);
    assert(get_error(queue, CONTAINER_QUEUE) == ERROR_NONE);

    queue_enqueue(queue, &l3);
    assert(get_error(queue, CONTAINER_QUEUE) == ERROR_NONE);

    printf("Queue: ");
    queue_print(queue);
    printf("\n\t");

    printf("Popping lists from queue...\n\t\t");

    void *popped_list;

    popped_list = queue_dequeue(queue);
    assert(get_error(queue, CONTAINER_QUEUE) == ERROR_NONE);

    printf("Popped list 1: ");
    dll_print(*(dll_list_t **)popped_list);
    qdll_list_free(popped_list);
    printf("\n\t\t");

    printf("Queue: ");
    queue_print(queue);
    printf("\n\t");

    printf("To array...\n\t\t");

    dll_list_t *to_array2[2];
    queue_to_array(queue, to_array2);
    assert(get_error(queue, CONTAINER_QUEUE) == ERROR_NONE);

    printf("Array: ");
    for (size_t i = 0; i < 2; i++)
    {
        dll_print(to_array2[i]);
    }

    printf("\n\t");

    printf("Clearing queue...\n\t\t");

    queue_clear(queue, CF_NONE);
    assert(get_error(queue, CONTAINER_QUEUE) == ERROR_NONE);
    
    printf("Queue: ");
    queue_print(queue);
    printf("\n\t");

    printf("From array...\n\t\t");

    dll_list_t *from_array[2] = {l3, l2};
    queue_from_array(queue, from_array, 2);
    assert(get_error(queue, CONTAINER_QUEUE) == ERROR_NONE);

    printf("Queue: ");
    queue_print(queue);
    printf("\n\t");

    printf("Destroying queue...\n");

    queue_destroy(&queue, CF_FREE_DATA);
    assert(queue == NULL);
}
