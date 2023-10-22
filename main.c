/**
 * @file main.c
 * @author Secareanu Filip
 * @brief   This is the main entry point for the testing program.
 * @version 0.1
 * @date 2023-10-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "src/list/list.h"

int main() {
    dll_list_t *list = dll_create(sizeof(int), NULL, NULL);

    dll_destroy(&list);

    return 0;
}
