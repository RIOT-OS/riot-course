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

#include "periph/uart.h"

kernel_pid_t pid;
static char stack[THREAD_STACKSIZE_MAIN];

#define MSG_QUEUE_SIZE 8
static msg_t msg_queue[MSG_QUEUE_SIZE];

static void uart_cb(void *arg, uint8_t data)
{
    (void) arg;
    msg_t msg;
    msg.content.value = data;

    msg_send(&msg, pid);
}

static void *printer(void *arg)
{
    (void) arg;

    msg_init_queue(msg_queue, MSG_QUEUE_SIZE);
    while (1) {
        msg_t msg;
        msg_receive(&msg);
        printf("received: %c\n", (char)msg.content.value);
    }

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
    uart_init(UART_DEV(0), 115200, uart_cb, NULL);

    return 0;
}
