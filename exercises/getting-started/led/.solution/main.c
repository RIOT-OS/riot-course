/*
 * Copyright (C) 2018 Inria
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

#include <stdio.h>
#include <stdlib.h>

#include "shell.h"

#include "board.h"

static int toggle_handler(int argc, char **argv)
{
    if (argc != 2) {
        printf("usage: %s <led id>\n", argv[0]);
        return 1;
    }

    uint8_t led_id = atoi(argv[1]);
    switch (led_id) {
#ifdef LED0_TOGGLE
        case 0:
            LED0_TOGGLE;
            break;
#endif
#ifdef LED1_TOGGLE
        case 1:
            LED1_TOGGLE;
            break;
#endif
#ifdef LED2_TOGGLE
        case 2:
            LED2_TOGGLE;
            break;
#endif
#ifdef LED3_TOGGLE
        case 3:
            LED3_TOGGLE;
            break;
#endif
        default:
            printf("Invalid led number '%d'\n", led_id);
            return -1;
    }
    printf("led '%d' toggled\n", led_id);
    return 0;
}

static const shell_command_t shell_commands[] = {
    { "toggle", "toggle a led", toggle_handler },
    { NULL, NULL, NULL }
};

int main(void)
{
    puts("shell application that toggles on-board LEDs");
    char line_buf[SHELL_DEFAULT_BUFSIZE];
    shell_run(shell_commands, line_buf, SHELL_DEFAULT_BUFSIZE);
}
