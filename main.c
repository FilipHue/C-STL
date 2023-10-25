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
#include "test/test_list/t_list.h"
#include "test/test_stack/t_stack.h"
#include "test/test_queue/t_queue.h"

int main() {
    // test_ints();
    // test_strings();
    // test_containers();

    stest_ints();
    // stest_strings();
    // stest_containers();

    // qtest_int();
    // qtest_string();
    // qtest_containers();

    return 0;
}
