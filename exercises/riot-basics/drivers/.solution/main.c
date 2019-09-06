/*
 * Copyright (C) 2018 Inria
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

#include <stdio.h>
#include <string.h>

#include "xtimer.h"
#include "thread.h"

#include "board.h"

#include "hts221.h"
#include "hts221_params.h"

#include "lsm6dsl.h"
#include "lsm6dsl_params.h"

static char stack1[THREAD_STACKSIZE_MAIN];
static char stack2[THREAD_STACKSIZE_MAIN];

static hts221_t hts221_dev;
static lsm6dsl_t lsm6dsl_dev;

static void *thread1_handler(void *arg)
{
    (void) arg;

    while (1) {
        uint16_t hum = 0;
        int16_t temp = 0;
        hts221_read_humidity(&hts221_dev, &hum);
        hts221_read_temperature(&hts221_dev, &temp);
        printf("Humidity: %u.%u%%, Temperature:%u.%u°C\n",
               (hum / 10), (hum % 10),
               (temp / 10), (temp % 10));
        xtimer_sleep(2);
    }

    return NULL;
}

static void *thread2_handler(void *arg)
{
    (void) arg;

    while (1) {
        lsm6dsl_3d_data_t mag_value;
        lsm6dsl_3d_data_t acc_value;
        lsm6dsl_read_acc(&lsm6dsl_dev, &acc_value);
        printf("Accelerometer x: %i y: %i z: %i\n",
               acc_value.x, acc_value.y, acc_value.z);
        lsm6dsl_read_gyro(&lsm6dsl_dev, &mag_value);
        printf("Gyroscope x: %i y: %i z: %i\n",
               mag_value.x, mag_value.y, mag_value.z);
        xtimer_usleep(100 * US_PER_MS);
    }

    return NULL;
}


int main(void)
{
    puts("RTC alarm RIOT application");

    hts221_init(&hts221_dev, &hts221_params[0]);
    hts221_power_on(&hts221_dev);
    hts221_set_rate(&hts221_dev, hts221_dev.p.rate);

    lsm6dsl_init(&lsm6dsl_dev, lsm6dsl_params);
    lsm6dsl_acc_power_up(&lsm6dsl_dev);
    lsm6dsl_gyro_power_up(&lsm6dsl_dev); 

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

    return 0;
}
