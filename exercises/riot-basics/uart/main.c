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

static void *printer(void *arg)
{
    (void) arg;

    return NULL;
}

int main(void)
{
    puts("UART echo application");

    pid = thread_create(stack, sizeof(stack),
                        THREAD_PRIORITY_MAIN - 1,
                        0,
                        printer,
                        NULL, "thread");
    
    /* initialize UART 0 with a callback */

    return 0;
}
