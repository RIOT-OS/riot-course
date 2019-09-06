/*
 * Copyright (C) 2018 Inria
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

#include <stdio.h>

#include "thread.h"
#include "xtimer.h"

static char stack1[THREAD_STACKSIZE_MAIN];
static char stack2[THREAD_STACKSIZE_MAIN];
static char stack3[THREAD_STACKSIZE_MAIN];

static void *thread1_handler(void *arg)
{
    (void) arg;
    
    while (1) {
        LED1_TOGGLE;
        xtimer_usleep(500 * US_PER_MS);
    }

    return NULL;
}

static void *thread2_handler(void *arg)
{
    (void) arg;
    
    while (1) {
        LED2_TOGGLE;
        xtimer_sleep(1);
    }

    return NULL;
}

static void *thread3_handler(void *arg)
{
    (void) arg;

    while (1) {
        LED3_TOGGLE;
        xtimer_sleep(2);
    }

    return NULL;
}


int main(void)
{
    puts("Multi LED blinker application");

    thread_create(stack1, sizeof(stack1),
                  THREAD_PRIORITY_MAIN - 1,
                  0,
                  thread1_handler,
                  NULL, "thread1");
    thread_create(stack2, sizeof(stack2),
                  THREAD_PRIORITY_MAIN - 1,
                  0,
                  thread2_handler,
                  NULL, "thread2");
    thread_create(stack3, sizeof(stack3),
                  THREAD_PRIORITY_MAIN - 1,
                  0,
                  thread3_handler,
                  NULL, "thread3");

    return 0;
}
