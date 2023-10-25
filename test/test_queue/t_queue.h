#ifndef T_QUEUE_H
/**
 * @file t_queue.h
 * @author Secareanu Filip
 * @brief   This is the header file for the queue testing program.
 * @version 0.1
 * @date 2023-10-25
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#define T_QUEUE_H

#include "../../src/queue/queue.h"
#include "../../src/list/list.h"
#include "../../src/stack/stack.h"

#include <stdio.h>
#include <assert.h>

void qtest_int();
void qtest_string();
void qtest_containers();

#endif // T_QUEUE_H
