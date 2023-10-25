/**
 * @file queue.c
 * @author Secareanu Filip
 * @brief   This is the implementation for the queue data structure.
 * @version 0.1
 * @date 2023-10-25
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "queue.h"

queue_t *queue_create(size_t data_size, size_t capacity, float grow_treshold, float shrink_treshold, free_function_t free_function, print_function_t print_function)
{
    queue_t *queue = SAFE_CALLOC(1, sizeof(queue_t));

    queue->data = SAFE_CALLOC(capacity, data_size);

    queue->front = SIZE_MAX;
    queue->rear = 0;
    queue->data_size = data_size;
    queue->size = 0;
    queue->capacity = capacity;

    queue->grow_treshold = grow_treshold;
    queue->shrink_treshold = shrink_treshold;

    queue->error = ERROR_NONE;

    queue->free_function = free_function;
    queue->print_function = print_function;

    return queue;
}

void queue_destroy(queue_t **queue, container_flags_t flag)
{
    if (*queue == NULL)
        return;

    if (flag == CF_FREE_DATA && (*queue)->free_function != NULL)
    {
        for (size_t i = 0; i < (*queue)->size; i++) {
            void *source = (*queue)->data + (((*queue)->front + i) * (*queue)->data_size);
            (*queue)->free_function(source);
        }
    }

    free((*queue)->data);
    free(*queue);
    *queue = NULL;
}

void queue_enqueue(queue_t *queue, void *data)
{
    if (queue == NULL) {
        return;
    }

    if (data == NULL) {
        queue->error = ERROR_INVALID_DATA;
        return;
    }

    if ((float)queue->size / (float)queue->capacity >= queue->grow_treshold) {
        queue_resize(queue, queue->capacity * 2);
    }

    if (queue->front == SIZE_MAX) {
        queue->front = 0;
    }

    void *source = queue->data + (queue->rear * queue->data_size);
    memcpy(source, data, queue->data_size);

    queue->rear++;
    queue->size++;

    queue->error = ERROR_NONE;
}

void *queue_dequeue(queue_t *queue)
{
    if (queue == NULL) {
        return NULL;
    }

    if (queue->size == 0) {
        queue->error = ERROR_EMPTY;
        return NULL;
    }

    if ((float)queue->size / queue->capacity <= queue->shrink_treshold) {
        queue_resize(queue, queue->capacity / 2);
    }

    void *data = queue->data + (queue->front * queue->data_size);

    queue->front++;
    queue->size--;

    if (queue->size == 0) {
        queue->front = SIZE_MAX;
        queue->rear = 0;
    }

    queue->error = ERROR_NONE;

    return data;
}

void *queue_front(queue_t *queue)
{
    if (queue == NULL) {
        return NULL;
    }

    if (queue->size == 0) {
        queue->error = ERROR_EMPTY;
        return NULL;
    }

    void *data = SAFE_CALLOC(1, queue->data_size);

    void *source = queue->data + (queue->front * queue->data_size);
    memcpy(data, source, queue->data_size);

    queue->error = ERROR_NONE;

    return data;
}

void queue_clear(queue_t *queue, container_flags_t flag)
{
    if (queue == NULL) {
        return;
    }

    if (flag == CF_FREE_DATA && queue->free_function) {
        while (queue->size > 0) {
            void *source = queue->data + (queue->front * queue->data_size);
            queue->free_function(source);
            queue->front++;
            queue->size--;
        }
    } else {
        queue->front = SIZE_MAX;
        queue->rear = 0;
        queue->size = 0;
    }

    queue->error = ERROR_NONE;
}

bool queue_is_empty(queue_t *queue)
{
    if (queue == NULL) {
        return true;
    }

    return queue->size == 0;
}

size_t queue_size(queue_t *queue)
{
    if (queue == NULL) {
        return 0;
    }

    return queue->size;
}

void queue_to_array(queue_t *queue, void *array)
{
    if (queue == NULL) {
        return;
    }

    if (array == NULL) {
        queue->error = ERROR_INVALID_DATA;
        return;
    }

    void *source = queue->data + (queue->front * queue->data_size);
    memcpy(array, source, queue->data_size * queue->size);

    queue->error = ERROR_NONE;
}

void queue_from_array(queue_t *queue, void *array, size_t array_size)
{
    if (queue == NULL) {
        return;
    }

    if (array == NULL) {
        queue->error = ERROR_INVALID_DATA;
        return;
    }

    queue_clear(queue, CF_NONE);

    if (array_size > queue->capacity) {
        queue->data = SAFE_REALLOC(queue->data, array_size * queue->data_size);
        queue->capacity = array_size;
    }

    memcpy(queue->data, array, array_size * queue->data_size);

    queue->front = 0;
    queue->rear = array_size;
    queue->size = array_size;

    queue->error = ERROR_NONE;
}

void queue_resize(queue_t *queue, size_t new_capacity)
{
    if (queue == NULL) {
        return;
    }

    void *new_data = SAFE_CALLOC(new_capacity, queue->data_size);

    void *source = queue->data + (queue->front * queue->data_size);
    memcpy(new_data, source, queue->data_size * queue->size);

    free(queue->data);

    queue->data = new_data;
    queue->capacity = new_capacity;

    queue->front = 0;
    queue->rear = queue->size;

    queue->error = ERROR_NONE;
}

void queue_print(queue_t *queue)
{
    if (queue == NULL) {
        return;
    }

    if (queue->print_function == NULL) {
        queue->error = ERROR_INVALID_FUNCTION;
        return;
    }

    size_t front = queue->front;

    while (front < queue->rear) {
        void *source = queue->data + front * queue->data_size;
        queue->print_function(source);

        front++;
    }
}
