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

#include "hts221.h"
#include "hts221_params.h"

static hts221_t dev;

static int temperature_handler(int argc, char **argv)
{
    if (argc != 1) {
        printf("usage: %s\n", argv[0]);
        return 1;
    }

    int16_t temp = 0;
    if (hts221_read_temperature(&dev, &temp) != HTS221_OK) {
        puts("failed to read hts221 temperature");
        return -1;
    }

    bool negative = (temp < 0);
    if (negative) {
        temp = -temp;
    }

    printf("temperature T:%c%u.%u°C\n",
           (negative ? '-' : ' '), (temp / 10), (temp % 10));
    return 0;
}

static int humidity_handler(int argc, char **argv)
{
    if (argc != 1) {
        printf("usage: %s\n", argv[0]);
        return 1;
    }

    uint16_t hum = 0;
    if (hts221_read_humidity(&dev, &hum) != HTS221_OK) {
        puts("failed to read hts221 humidity");
        return -1;
    }

    printf("humidity: %u.%u%%\n", (hum / 10), (hum % 10));
    return 0;
}

static const shell_command_t shell_commands[] = {
    { "temperature", "print hts221 temperature", temperature_handler },
    { "humidity", "print hts221 relative humidity", humidity_handler },
    { NULL, NULL, NULL }
};

int main(void)
{
    puts("shell application that toggles on-board LEDs");

    if (hts221_init(&dev, &hts221_params[0]) != HTS221_OK) {
        puts("Cannot initialize hts221 sensor");
        return -1;
    }
    if (hts221_power_on(&dev) != HTS221_OK) {
        puts("Failed to set hts221 power on");
        return -2;
    }
    if (hts221_set_rate(&dev, dev.p.rate) != HTS221_OK) {
        puts("Failed to set hts221 continuous mode");
        return -3;
    }

    char line_buf[SHELL_DEFAULT_BUFSIZE];
    shell_run(shell_commands, line_buf, SHELL_DEFAULT_BUFSIZE);
}
