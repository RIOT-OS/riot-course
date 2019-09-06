/*
 * Copyright (C) 2018 Inria
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

#include <stdio.h>
#include <string.h>

#include "thread.h"
#include "msg.h"

#include "board.h"

kernel_pid_t pid;
static char stack[THREAD_STACKSIZE_MAIN];

static void *thread_handler(void *arg)
{
    (void) arg;
    
    return NULL;
}

int main(void)
{
    puts("Push button RIOT application");

    pid = thread_create(stack, sizeof(stack),
                        THREAD_PRIORITY_MAIN - 1,
                        0,
                        thread_handler,
                        NULL, "thread");
    
    /* initialize on-board LED1 */

    /* initialize on-board user button */
    
    return 0;
}
