/*
 * Copyright (C) 2018 Inria
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

#include <stdio.h>

#include "thread.h"
#include "shell.h"

static char stack[THREAD_STACKSIZE_MAIN];

static void *thread_handler(void *arg)
{
    (void) arg;
    puts("Hello from thread");

    /* Loop forever */
    while (1) {}
 
    return NULL;
}
 
int main(void)
{
    puts("First RIOT application with a thread");

    thread_create(stack, sizeof(stack),
                  THREAD_PRIORITY_MAIN + 1,
                  0,
                  thread_handler,
                  NULL, "my thread");

    char line_buf[SHELL_DEFAULT_BUFSIZE];
    shell_run(NULL, line_buf, SHELL_DEFAULT_BUFSIZE);

    return 0;
}
