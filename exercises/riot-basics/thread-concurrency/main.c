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
#include "mutex.h"
#include "xtimer.h"

static kernel_pid_t writer_pid, printer_pid;
static char printer_stack[THREAD_STACKSIZE_MAIN];
static char writer_stack[THREAD_STACKSIZE_MAIN];

typedef struct {
    char buffer[128];
    mutex_t lock;
} data_t;

static data_t data;

static void *thread_writer_handler(void *arg)
{
    (void) arg;

    /* Update content of buffer every 100ms, the content update takes 200ms */

    return NULL;
}

static void *thread_printer_handler(void *arg)
{
    (void) arg;

    /* print content of buffer every 200ms */

    return NULL;
}

int main(void)
{
    puts("RIOT application with thread safe concurrency");

    writer_pid = thread_create(writer_stack, sizeof(writer_stack), THREAD_PRIORITY_MAIN - 1,
                               0, thread_writer_handler, NULL, "writer thread");
    printer_pid = thread_create(printer_stack, sizeof(printer_stack), THREAD_PRIORITY_MAIN - 1,
                                0, thread_printer_handler, NULL, "printer thread");

    return 0;
}