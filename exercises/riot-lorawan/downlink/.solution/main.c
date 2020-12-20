/*
 * Copyright (C) 2018 Inria
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

#include <string.h>

#include "thread.h"

#include "timex.h"
#include "ztimer.h"

#include "net/loramac.h"
#include "semtech_loramac.h"

#include "board.h"

/* Declare globally the loramac descriptor */
static semtech_loramac_t loramac;

/* Device and application informations required for OTAA activation */
static const uint8_t deveui[LORAMAC_DEVEUI_LEN] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
static const uint8_t appeui[LORAMAC_APPEUI_LEN] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
static const uint8_t appkey[LORAMAC_APPKEY_LEN] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

/* The simple message to send */
const char *message = "This is RIOT!";

/* Implement the receiver thread */
#define RECEIVER_MSG_QUEUE                          (4U)
static msg_t _receiver_queue[RECEIVER_MSG_QUEUE];
static char _receiver_stack[THREAD_STACKSIZE_DEFAULT];

static void *receiver(void *arg)
{
    msg_init_queue(_receiver_queue, RECEIVER_MSG_QUEUE);

    (void)arg;
    while (1) {
        /* blocks until something is received */
        switch (semtech_loramac_recv(&loramac)) {
            case SEMTECH_LORAMAC_RX_DATA:
                loramac.rx_data.payload[loramac.rx_data.payload_len] = 0;
                printf("Data received: %s, port: %d\n",
                (char *)loramac.rx_data.payload, loramac.rx_data.port);
                break;

            case SEMTECH_LORAMAC_RX_CONFIRMED:
                puts("Received ACK from network");
                break;

            default:
                break;
        }
    }
    return NULL;
}

static void sender(void)
{
    while (1) {
        /* wait 20 secs */
        ztimer_sleep(ZTIMER_MSEC, 20 * MS_PER_SEC);

        /* send the LoRaWAN message */
        printf("Sending message: %s\n", message);
        uint8_t ret = semtech_loramac_send(&loramac, (uint8_t *)message,
                                           strlen(message));
        if (ret != SEMTECH_LORAMAC_TX_DONE) {
            printf("Cannot send message '%s', ret code: %d\n", message, ret);
        }
    }

    /* this should never be reached */
    return;
}

int main(void)
{
    /* initialize the loramac stack */
    semtech_loramac_init(&loramac);

    /* use a fast datarate so we don't use the physical layer too much */
    semtech_loramac_set_dr(&loramac, 5);

    /* set the LoRaWAN keys */
    semtech_loramac_set_deveui(&loramac, deveui);
    semtech_loramac_set_appeui(&loramac, appeui);
    semtech_loramac_set_appkey(&loramac, appkey);

    /* start the OTAA join procedure */
    puts("Starting join procedure");
    if (semtech_loramac_join(&loramac, LORAMAC_JOIN_OTAA) != SEMTECH_LORAMAC_JOIN_SUCCEEDED) {
        puts("Join procedure failed");
        return 1;
    }

    puts("Join procedure succeeded");

    /* start the receiver thread */
    thread_create(_receiver_stack, sizeof(_receiver_stack),
                  THREAD_PRIORITY_MAIN - 1, 0, receiver, NULL, "receiver thread");

    /* call the sender */
    sender();

    return 0; /* should never be reached */
}
