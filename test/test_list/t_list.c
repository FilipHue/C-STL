#include "t_list.h"

typedef struct Point {
    int x;
    int y;
} Point;

void int_print(void *data)
{
    printf("%d ", *(int*)data);
}

void string_print(void *data)
{
    printf("%s ", (char*)data);
}

void double_print(void *data) {
    printf("%.2f ", *(double*)data);
}

void char_print(void *data) {
    printf("%c ", *(char*)data);
}

void point_print(void *data) {
    Point *point = (Point*)data;
    printf("(%d, %d) ", point->x, point->y);
}

void list_free(void *data) {
    dll_destroy((dll_list_t**)data);
}

void list_print(void *data) {
    dll_list_t *nested_list = *(dll_list_t**)data;
    if (nested_list) {
        dll_print(nested_list);
    }
}

void test_ints()
{
    printf("Testing ints...\n");

    dll_list_t *list;
    int values[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    // Initialize list
    printf("Initializing list...\n");

    list = dll_create(sizeof(int), NULL, int_print);
    assert(list != NULL);
    assert(get_error(list, CONTAINER_LIST) == ERROR_NONE);

    // Append
    printf("Appending...\n");

    for (int i = 0; i < 10; i++) {
        dll_append(list, &values[i]);
        assert(get_error(list, CONTAINER_LIST) == ERROR_NONE);
    }
    dll_print(list);
    printf("\n");

    // Prepend
    printf("Prepending...\n");

    for (int i = 0; i < 10; i++) {
        dll_prepend(list, &values[i]);
        assert(get_error(list, CONTAINER_LIST) == ERROR_NONE);
    }
    dll_print(list);
    printf("\n");

    // Insert
    printf("Inserting...\n");
    dll_insert(list, 0, &values[0]);
    assert(get_error(list, CONTAINER_LIST) == ERROR_NONE);
    dll_insert(list, 5, &values[0]);
    assert(get_error(list, CONTAINER_LIST) == ERROR_NONE);
    dll_insert(list, dll_size(list) - 1, &values[0]);
    assert(get_error(list, CONTAINER_LIST) == ERROR_NONE);

    dll_print(list);
    printf("\n");

    // Remove
    printf("Removing...\n");
    dll_remove(list, 0);
    assert(get_error(list, CONTAINER_LIST) == ERROR_NONE);
    dll_remove(list, 5);
    assert(get_error(list, CONTAINER_LIST) == ERROR_NONE);
    dll_remove(list, dll_size(list) - 1);
    assert(get_error(list, CONTAINER_LIST) == ERROR_NONE);

    dll_print(list);
    printf("\n");

    // Clear
    printf("Clearing...\n");
    dll_clear(list);
    assert(get_error(list, CONTAINER_LIST) == ERROR_NONE);
    assert(dll_empty(list) == true);
    assert(list != NULL);

    dll_print(list);
    printf("\n");

    // Destroy
    printf("Destroying...\n");
    dll_destroy(&list);

    printf("All tests passed!\n\n");
}

void test_strings()
{
    printf("Testing strings...\n");

    dll_list_t *list;
    char *values[10] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

    // Initialize list
    printf("Initializing list...\n");

    list = dll_create(sizeof(char*), NULL, string_print);
    assert(list != NULL);
    assert(get_error(list, CONTAINER_LIST) == ERROR_NONE);

    // Append
    printf("Appending...\n");

    for (int i = 0; i < 10; i++) {
        dll_append(list, values[i]);
        assert(get_error(list, CONTAINER_LIST) == ERROR_NONE);
    }
    dll_print(list);
    printf("\n");

    // Prepend
    printf("Prepending...\n");

    for (int i = 0; i < 10; i++) {
        dll_prepend(list, values[i]);
        assert(get_error(list, CONTAINER_LIST) == ERROR_NONE);
    }
    dll_print(list);
    printf("\n");

    // Insert
    printf("Inserting...\n");
    dll_insert(list, 0, values[0]);
    assert(get_error(list, CONTAINER_LIST) == ERROR_NONE);
    dll_insert(list, 5, values[0]);
    assert(get_error(list, CONTAINER_LIST) == ERROR_NONE);
    dll_insert(list, dll_size(list) - 1, values[0]);
    assert(get_error(list, CONTAINER_LIST) == ERROR_NONE);

    dll_print(list);
    printf("\n");

    // Remove
    printf("Removing...\n");
    dll_remove(list, 0);
    assert(get_error(list, CONTAINER_LIST) == ERROR_NONE);
    dll_remove(list, 5);
    assert(get_error(list, CONTAINER_LIST) == ERROR_NONE);
    dll_remove(list, dll_size(list) - 1);
    assert(get_error(list, CONTAINER_LIST) == ERROR_NONE);

    dll_print(list);
    printf("\n");

    // Clear
    printf("Clearing...\n");
    dll_clear(list);
    assert(get_error(list, CONTAINER_LIST) == ERROR_NONE);
    assert(dll_empty(list) == true);
    assert(list != NULL);

    dll_print(list);
    printf("\n");

    // Destroy
    printf("Destroying...\n\n");
    dll_destroy(&list);
}

void test_containers()
{
    dll_list_t *main_list = dll_create(sizeof(dll_list_t*), list_free, list_print); // List of lists

    // Int list
    dll_list_t *int_list = dll_create(sizeof(int), NULL, int_print);
    int int_values[6] = {0, 1, 2, 3, 4, 5};
    for (int i = 0; i < 6; i++) {
        dll_append(int_list, &int_values[i]);
    }
    dll_append(main_list, &int_list);

    // Double list
    dll_list_t *double_list = dll_create(sizeof(double), NULL, double_print);
    double double_values[] = {0.1, 1.1, 2.2, 3.3, 4.4};
    for (int i = 0; i < 5; i++) {
        dll_append(double_list, &double_values[i]);
    }
    dll_append(main_list, &double_list);

    // Char list
    dll_list_t *char_list = dll_create(sizeof(char), NULL, char_print);
    char char_values[] = {'a', 'b', 'c', 'd'};
    for (int i = 0; i < 4; i++) {
        dll_append(char_list, &char_values[i]);
    }
    dll_append(main_list, &char_list);

    // Point list
    dll_list_t *point_list = dll_create(sizeof(Point), NULL, point_print);
    Point point_values[] = {{0, 0}, {1, 1}, {2, 2}};
    for (int i = 0; i < 3; i++) {
        dll_append(point_list, &point_values[i]);
    }
    dll_append(main_list, &point_list);

    // Now, print the main list
    dll_print(main_list);

    // Just destroy the main list, which will in turn destroy nested lists
    dll_destroy(&main_list);
    assert(main_list == NULL);
    // assert(int_list == NULL);
}
