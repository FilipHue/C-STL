#include "list.h"

dll_list_t *dll_create(size_t data_size, free_function_t free_fn, print_function_t print_fn)
{
	dll_list_t *new_list;
	
	new_list = SAFE_CALLOC(sizeof(dll_list_t), 1);
	
	new_list->head = NULL;
	new_list->tail = NULL;

	new_list->data_size = data_size;
	new_list->size = 0;

	new_list->free_fn = free_fn;
	new_list->print_fn = print_fn;

	new_list->error = ERROR_NONE;

	return new_list;
}

void dll_destroy(dll_list_t **list)
{
	if ((*list) == NULL) {
		return;
	}

	dll_clear(*list);
	free(*list);

	*list = NULL;
}

void *dll_front(dll_list_t *list)
{
	if (list == NULL) {
		return NULL;
	}

	if (list->head == NULL) {
		list->error = ERROR_NULL;
		return NULL;
	}

	list->error = ERROR_NONE;

	return list->head->data;
}

void *dll_back(dll_list_t *list)
{
	if (list == NULL) {
		return NULL;
	}

	if (list->tail == NULL) {
		list->error = ERROR_NULL;
		return NULL;
	}

	list->error = ERROR_NONE;

	return list->tail->data;
}

void dll_append(dll_list_t *list, void *data)
{
	if (list == NULL) {
		return;
	}

	if (data == NULL) {
		list->error = ERROR_INVALID_DATA;
		return;
	}

	dll_node_t *new_node;

	new_node = SAFE_CALLOC(sizeof(dll_node_t), 1);

	new_node->next = NULL;
	new_node->prev = NULL;
	new_node->data = SAFE_CALLOC(list->data_size, 1);
	memcpy(new_node->data, data, list->data_size);

	if (list->head == NULL) {
		list->head = new_node;
		list->tail = new_node;
	} else {
		new_node->prev = list->tail;
		list->tail->next = new_node;
		list->tail = new_node;
	}

	list->size++;

	list->error = ERROR_NONE;
}

void dll_prepend(dll_list_t *list, void *data)
{
	if (list == NULL) {
		return;
	}

	if (data == NULL) {
		list->error = ERROR_INVALID_DATA;
		return;
	}

	dll_node_t *new_node;

	new_node = SAFE_CALLOC(sizeof(dll_node_t), 1);

	new_node->next = NULL;
	new_node->prev = NULL;
	new_node->data = SAFE_CALLOC(list->data_size, 1);
	memcpy(new_node->data, data, list->data_size);

	if (list->head == NULL) {
		list->head = new_node;
		list->tail = new_node;
	} else {
		new_node->next = list->head;
		list->head->prev = new_node;
		list->head = new_node;
	}

	list->size++;

	list->error = ERROR_NONE;
}

void dll_insert(dll_list_t *list, size_t index, void *data)
{
	if (list == NULL) {
		return;
	}

	if (data == NULL) {
		list->error = ERROR_INVALID_DATA;
		return;
	}

	if (index >= list->size) {
		list->error = ERROR_INVALID_INDEX;
		return;
	}

	if (index == 0) {
		dll_prepend(list, data);
		return;
	}

	if (index == list->size - 1) {
		dll_append(list, data);
		return;
	}

	dll_node_t *new_node;
	dll_node_t *current_node;

	new_node = SAFE_CALLOC(sizeof(dll_node_t), 1);

	new_node->next = NULL;
	new_node->prev = NULL;
	new_node->data = SAFE_CALLOC(list->data_size, 1);
	memcpy(new_node->data, data, list->data_size);

	current_node = list->head;

	for (size_t i = 0; i < index; i++) {
		current_node = current_node->next;
	}

	new_node->next = current_node;
	new_node->prev = current_node->prev;

	current_node->prev->next = new_node;
	current_node->prev = new_node;

	list->size++;

	list->error = ERROR_NONE;
}

void dll_remove(dll_list_t *list, size_t index)
{
	if (list == NULL) {
		return;
	}

	if (index >= list->size) {
		list->error = ERROR_INVALID_INDEX;
		return;
	}

	dll_node_t *to_delete;

	if (index == 0) {
		to_delete = list->head;

		list->head = list->head->next;
		list->head->prev = NULL;
	} else if (index == list->size - 1) {
		to_delete = list->tail;

		list->tail = list->tail->prev;
		list->tail->next = NULL;
	} else {
		dll_node_t *current_node;

		current_node = list->head;

		for (size_t i = 0; i <= index; i++) {
			current_node = current_node->next;
		}

		to_delete = current_node;

		current_node->prev->next = current_node->next;
		current_node->next->prev = current_node->prev;
	}

	if (list->free_fn != NULL) {
		list->free_fn(to_delete->data);
	}
	if (to_delete->data != NULL) {
		free(to_delete->data);
	}
	free(to_delete);

	list->size--;

	list->error = ERROR_NONE;
}

void dll_remove_if(dll_list_t *list, predicate_function_t predicate)
{
	if (list == NULL) {
		return;
	}

	dll_node_t *current_node;
	dll_node_t *next_node;

	current_node = list->head;

	while (current_node != NULL) {
		next_node = current_node->next;

		if (predicate(current_node->data)) {
			if (current_node == list->head) {
				list->head = list->head->next;
				if (list->head != NULL) {
					list->head->prev = NULL;
				}
			} else if (current_node == list->tail) {
				list->tail = list->tail->prev;
				list->tail->next = NULL;
			} else {
				current_node->prev->next = current_node->next;
				current_node->next->prev = current_node->prev;
			}

			if (list->free_fn != NULL) {
				list->free_fn(current_node->data);
			}
			if (current_node->data != NULL) {
				free(current_node->data);
			}
			free(current_node);

			list->size--;
		}

		current_node = next_node;
	}

	list->error = ERROR_NONE;
}

void dll_clear(dll_list_t *list)
{
	if (list == NULL) {
		return;
	}

	dll_node_t *current_node;
	dll_node_t *next_node;

	current_node = list->head;

	while (current_node != NULL) {
		next_node = current_node->next;

		if (list->free_fn != NULL) {
			list->free_fn(current_node->data);
		}
		if (current_node->data != NULL) {
			free(current_node->data);
		}
		free(current_node);

		current_node = next_node;
	}

	list->head = NULL;
	list->tail = NULL;

	list->size = 0;

	list->error = ERROR_NONE;
}

void *dll_get(dll_list_t *list, size_t index)
{
	if (list == NULL) {
		return NULL;
	}

	if (index >= list->size) {
		list->error = ERROR_INVALID_INDEX;
		return NULL;
	}

	dll_node_t *current_node;

	current_node = list->head;

	for (size_t i = 0; i < index; i++) {
		current_node = current_node->next;
	}

	list->error = ERROR_NONE;

	return current_node->data;
}

size_t dll_find(dll_list_t *list, void *data)
{
    if (list == NULL) {
        return SIZE_MAX;
    }

    if (data == NULL) {
        list->error = ERROR_INVALID_DATA;
        return SIZE_MAX;
    }

    dll_node_t *current_node = list->head;
    for (size_t i = 0; i < list->size; i++) {
       	if (memcmp(current_node->data, data, list->data_size) == 0) {
            list->error = ERROR_NONE;
            return i;
        }
        current_node = current_node->next;
    }

    return SIZE_MAX;
}

size_t dll_find_f(dll_list_t *list, void *data, find_function_t find_fn)
{
	if (list == NULL) {
		return SIZE_MAX;
	}

	if (data == NULL) {
		list->error = ERROR_INVALID_DATA;
		return SIZE_MAX;
	}

	dll_node_t *current_node = list->head;
	for (size_t i = 0; i < list->size; i++) {
		if (find_fn(current_node->data, data)) {
			list->error = ERROR_NONE;
			return i;
		}
		current_node = current_node->next;
	}

	return SIZE_MAX;
}

size_t dll_size(dll_list_t *list)
{
	if (list == NULL) {
		return 0;
	}

	list->error = ERROR_NONE;

	return list->size;
}

bool dll_empty(dll_list_t *list)
{
	if (list == NULL) {
		return false;
	}

	list->error = ERROR_NONE;

	return list->size == 0;
}

void dll_print(dll_list_t *list)
{
	if (list == NULL) {
		return;
	}

	dll_node_t *current_node;

	current_node = list->head;

	while (current_node != NULL) {
		if (list->print_fn != NULL) {
			list->print_fn(current_node->data);
		}

		current_node = current_node->next;
	}

	list->error = ERROR_NONE;
}
