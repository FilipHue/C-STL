#include "t_list.h"

typedef struct Point {
    int x;
    int y;
} Point;

void int_print(const void *data)
{
    printf("%d ", *(int*)data);
}

void string_print(const void *data)
{
    printf("%s ", (char*)data);
}

void double_print(const void *data) {
    printf("%.2f ", *(double*)data);
}

void char_print(const void *data) {
    printf("%c ", *(char*)data);
}

void point_print(const void *data) {
    Point *point = (Point*)data;
    printf("(%d, %d) ", point->x, point->y);
}

void list_free(void *data) {
    dll_destroy((dll_list_t**)data);
}

void list_print(const void *data) {
    dll_list_t *nested_list = *(dll_list_t**)data;
    if (nested_list) {
        dll_print(nested_list);
    }
}

bool is_even(const void *data) {
    return (*(int*)data % 2 == 0);
}

bool is_string(const void *data) {
    return strcmp((char*)data, "one") == 0;
}

bool is_list(const void *data) {
    return *(dll_list_t**)data != NULL;
}

bool is_int(const void *data) {
    return (*(dll_list_t**)data)->print_fn == int_print;
}

bool find_int(const void *data, const void *value) {
    return *(int*)data == *(int*)value;
}

bool find_string(const void *data, const void *value) {
    return strcmp((char*)data, (char*)value) == 0;
}

bool find_list_int(const void *data, const void *value) {
    return (*(dll_list_t**)data)->print_fn == int_print;
}

bool find_list_double(const void *data, const void *value) {
    return (*(dll_list_t**)data)->print_fn == double_print;
}

bool find_list_point(const void *data, const void *value) {
    return (*(dll_list_t**)data)->print_fn == point_print;
}

bool unique_list_int(const void *data1, const void *data2) {
    dll_list_t *list1 = *(dll_list_t**) data1;
    dll_list_t *list2 = *(dll_list_t**) data2;

    if (list1->size != list2->size) {
        return false;
    }

    dll_node_t *node1 = list1->head;
    dll_node_t *node2 = list2->head;

    while (node1 != NULL && node2 != NULL) {
        int *int1 = (int*) node1->data;
        int *int2 = (int*) node2->data;

        if (*int1 != *int2) {
            return false;
        }

        node1 = node1->next;
        node2 = node2->next;
    }

    return true;
}

void test_ints()
{
    printf("Testing ints...\n\t");

    dll_list_t *list;
    int values[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    // Initialize list
    printf("Initializing list...\n\t");

    list = dll_create(sizeof(int), NULL, int_print);
    assert(list != NULL);
    assert(get_error(list, CONTAINER_LIST) == ERROR_NONE);

    // Append
    printf("Appending...\n\t\t");

    for (int i = 0; i < 10; i++) {
        dll_append(list, &values[i]);
        assert(get_error(list, CONTAINER_LIST) == ERROR_NONE);
    }
    dll_print(list);
    printf("\n\t");

    // Prepend
    printf("Prepending...\n\t\t");

    for (int i = 0; i < 10; i++) {
        dll_prepend(list, &values[i]);
        assert(get_error(list, CONTAINER_LIST) == ERROR_NONE);
    }
    dll_print(list);
    printf("\n\t");

    // Insert
    printf("Inserting...\n\t\t");
    dll_insert(list, 0, &values[0]);
    assert(get_error(list, CONTAINER_LIST) == ERROR_NONE);
    dll_insert(list, 5, &values[0]);
    assert(get_error(list, CONTAINER_LIST) == ERROR_NONE);
    dll_insert(list, dll_size(list) - 1, &values[0]);
    assert(get_error(list, CONTAINER_LIST) == ERROR_NONE);

    dll_print(list);
    printf("\n\t");

    // Remove
    printf("Removing...\n\t\t");
    dll_remove(list, 0);
    assert(get_error(list, CONTAINER_LIST) == ERROR_NONE);
    dll_remove(list, 5);
    assert(get_error(list, CONTAINER_LIST) == ERROR_NONE);
    dll_remove(list, dll_size(list) - 1);
    assert(get_error(list, CONTAINER_LIST) == ERROR_NONE);

    dll_print(list);
    printf("\n\t");

    // Remove if
    printf("Removing if...\n\t\t");
    dll_remove_if(list, is_even);
    assert(get_error(list, CONTAINER_LIST) == ERROR_NONE);

    dll_print(list);
    printf("\n\t");

    // Unique
    printf("Unique...\n\t\t");
    dll_unique(list);
    assert(get_error(list, CONTAINER_LIST) == ERROR_NONE);

    dll_print(list);
    printf("\n\t");

    // Get
    printf("Getting...\n\t");
    int *value = dll_get(list, 0);
    assert(get_error(list, CONTAINER_LIST) == ERROR_NONE);
    assert(*value == *((int*)dll_front(list)));

    value = dll_get(list, dll_size(list) - 1);
    assert(get_error(list, CONTAINER_LIST) == ERROR_NONE);
    assert(*value == *((int*)dll_back(list)));

    value = dll_get(list, 3);
    assert(get_error(list, CONTAINER_LIST) == ERROR_NONE);
    assert(*value == 3);

    // Find
    printf("Finding...\n\t");
    size_t index;
    
    index = dll_find(list, dll_front(list));
    assert(get_error(list, CONTAINER_LIST) == ERROR_NONE);
    assert(index == 0);

    index = dll_find(list, &values[5]);
    assert(get_error(list, CONTAINER_LIST) == ERROR_NONE);
    assert(index == 2);

    // Clear
    printf("Clearing...\n\t\t");
    dll_clear(list);
    assert(get_error(list, CONTAINER_LIST) == ERROR_NONE);
    assert(dll_empty(list) == true);
    assert(list != NULL);

    dll_print(list);
    printf("\n\t");

    // Destroy
    printf("Destroying...\n");
    dll_destroy(&list);
    assert(list == NULL);

    printf("All tests passed!\n\n");
}

void test_strings()
{
    printf("Testing strings...\n\t");

    dll_list_t *list;
    char *values[10] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

    // Initialize list
    printf("Initializing list...\n\t");

    list = dll_create(sizeof(char*), NULL, string_print);
    assert(list != NULL);
    assert(get_error(list, CONTAINER_LIST) == ERROR_NONE);

    // Append
    printf("Appending...\n\t\t");

    for (int i = 0; i < 10; i++) {
        dll_append(list, values[i]);
        assert(get_error(list, CONTAINER_LIST) == ERROR_NONE);
    }
    dll_print(list);
    printf("\n\t");

    // Prepend
    printf("Prepending...\n\t\t");

    for (int i = 0; i < 10; i++) {
        dll_prepend(list, values[i]);
        assert(get_error(list, CONTAINER_LIST) == ERROR_NONE);
    }
    dll_print(list);
    printf("\n\t");

    // Insert
    printf("Inserting...\n\t\t");
    dll_insert(list, 0, values[0]);
    assert(get_error(list, CONTAINER_LIST) == ERROR_NONE);
    dll_insert(list, 5, values[0]);
    assert(get_error(list, CONTAINER_LIST) == ERROR_NONE);
    dll_insert(list, dll_size(list) - 1, values[0]);
    assert(get_error(list, CONTAINER_LIST) == ERROR_NONE);

    dll_print(list);
    printf("\n\t");

    // Remove
    printf("Removing...\n\t\t");
    dll_remove(list, 0);
    assert(get_error(list, CONTAINER_LIST) == ERROR_NONE);
    dll_remove(list, 5);
    assert(get_error(list, CONTAINER_LIST) == ERROR_NONE);
    dll_remove(list, dll_size(list) - 1);
    assert(get_error(list, CONTAINER_LIST) == ERROR_NONE);

    dll_print(list);
    printf("\n\t");

    // Remove if
    printf("Removing if...\n\t\t");
    dll_remove_if(list, is_string);
    assert(get_error(list, CONTAINER_LIST) == ERROR_NONE);

    dll_print(list);
    printf("\n\t");

    // Get
    printf("Getting...\n\t");
    char *value = dll_get(list, 0);
    assert(get_error(list, CONTAINER_LIST) == ERROR_NONE);
    assert(strcmp(value, ((char*)dll_front(list))) == 0);

    value = dll_get(list, dll_size(list) - 1);
    assert(get_error(list, CONTAINER_LIST) == ERROR_NONE);
    assert(strcmp(value, ((char*)dll_back(list))) == 0);

    value = dll_get(list, 5);
    assert(get_error(list, CONTAINER_LIST) == ERROR_NONE);
    assert(strcmp(value, "five") == 0);

    // Unique
    printf("Unique...\n\t\t");
    dll_unique(list);

    dll_print(list);
    printf("\n\t");

    // Find
    printf("Finding...\n\t");
    size_t index;

    index = dll_find_f(list, dll_front(list), find_string);
    assert(get_error(list, CONTAINER_LIST) == ERROR_NONE);
    assert(index == 0);

    index = dll_find_f(list, values[5], find_string);
    assert(get_error(list, CONTAINER_LIST) == ERROR_NONE);
    assert(index == 5);

    // Clear
    printf("Clearing...\n\t\t");
    dll_clear(list);
    assert(get_error(list, CONTAINER_LIST) == ERROR_NONE);
    assert(dll_empty(list) == true);
    assert(list != NULL);

    dll_print(list);
    printf("\n\t");

    // Destroy
    printf("Destroying...\n");
    dll_destroy(&list);

    printf("All tests passed!\n\n");
}

void test_containers()
{
    printf("Testing containers...\n\t");

    printf("Testing lists...\n\t");
    dll_list_t *main_list = dll_create(sizeof(dll_list_t*), list_free, list_print); // List of lists

    printf("Creating nested lists...\n\t\t");

    printf("Creating int list...\n\t\t\t");
    dll_list_t *int_list = dll_create(sizeof(int), NULL, int_print);
    dll_list_t *int_list2 = dll_create(sizeof(int), NULL, int_print);
    dll_list_t *int_list3 = dll_create(sizeof(int), NULL, int_print);
    int int_values[6] = {0, 1, 2, 3, 4, 5};
    for (int i = 0; i < 6; i++) {
        dll_append(int_list, &int_values[i]);
        dll_append(int_list2, &int_values[i]);
        dll_append(int_list3, &int_values[i]);
        assert(get_error(int_list, CONTAINER_LIST) == ERROR_NONE);
    }
    dll_print(int_list);
    printf("\n\t\t");

    printf("Creating double list...\n\t\t\t");
    dll_list_t *double_list = dll_create(sizeof(double), NULL, double_print);
    double double_values[] = {0.1, 1.1, 2.2, 3.3, 4.4};
    for (int i = 0; i < 5; i++) {
        dll_append(double_list, &double_values[i]);
        assert(get_error(double_list, CONTAINER_LIST) == ERROR_NONE);
    }
    dll_print(double_list);
    printf("\n\t\t");

    printf("Creating char list...\n\t\t\t");
    dll_list_t *char_list = dll_create(sizeof(char), NULL, char_print);
    char char_values[] = {'a', 'b', 'c', 'd'};
    for (int i = 0; i < 4; i++) {
        dll_append(char_list, &char_values[i]);
        assert(get_error(char_list, CONTAINER_LIST) == ERROR_NONE);
    }
    dll_print(char_list);
    printf("\n\t\t");

    printf("Creating point list...\n\t\t\t");
    dll_list_t *point_list = dll_create(sizeof(Point), NULL, point_print);
    Point point_values[] = {{0, 0}, {1, 1}, {2, 2}};
    for (int i = 0; i < 3; i++) {
        dll_append(point_list, &point_values[i]);
        assert(get_error(point_list, CONTAINER_LIST) == ERROR_NONE);
    }
    dll_print(point_list);
    printf("\n\t\t");

    printf("Creating main list...\n\t\t\t");
    dll_append(main_list, &int_list);
    dll_append(main_list, &double_list);
    dll_append(main_list, &char_list);
    dll_append(main_list, &point_list);

    dll_print(main_list);
    printf("\n\t\t");

    printf("Removing int list...\n\t\t\t");
    dll_remove_if(main_list, is_int);
    assert(get_error(main_list, CONTAINER_LIST) == ERROR_NONE);

    dll_print(main_list);
    printf("\n\t\t");

    printf("Unique...\n\t\t\t");
    dll_append(main_list, &int_list2);
    dll_append(main_list, &int_list3);

    printf("Before: ");
    dll_print(main_list);
    printf("\n\t\t\t");

    dll_unique_f(main_list, unique_list_int);

    printf("After:  ");
    dll_print(main_list);
    printf("\n\t\t");

    printf("Finding int list...\n\t\t");
    size_t index = dll_find(main_list, &int_list);
    assert(get_error(main_list, CONTAINER_LIST) == ERROR_NONE);
    assert(index == SIZE_MAX);

    printf("Finding int list2...\n\t\t");
    index = dll_find(main_list, &int_list2);
    assert(get_error(main_list, CONTAINER_LIST) == ERROR_NONE);
    assert(index == dll_size(main_list) - 1);

    printf("Finding double list...\n\t\t");
    index = dll_find_f(main_list, &double_list, find_list_double);
    assert(get_error(main_list, CONTAINER_LIST) == ERROR_NONE);
    assert(index == 0);

    printf("Finding point list...\n\t\t");

    index = dll_find_f(main_list, &point_list, find_list_point);
    assert(get_error(main_list, CONTAINER_LIST) == ERROR_NONE);
    assert(index == 2);

    printf("Destroying main list...\n");
    dll_destroy(&main_list);
    assert(main_list == NULL);

    printf("All tests passed!\n\n");
}
