/*
 * Copyright (C) 2018 Inria
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

#include <string.h>

#include "timex.h"
#include "ztimer.h"

#include "net/loramac.h"
#include "semtech_loramac.h"

#include "board.h"

/* TODO: Declare globally the loramac descriptor */

/* TODO: Device and application informations required for OTAA activation */

/* The simple message to send */
const char *message = "This is RIOT!";

int main(void)
{
    /* TODO: initialize the loramac stack */

    /* TODO: use a fast datarate so we don't use the physical layer too much */

    /* TODO: set the LoRaWAN keys */

    /* TODO: start the OTAA join procedure */

    while (1) {
        /* TODO: wait 20 secs */

        /* TODO: send the LoRaWAN message (check return code!) */
        printf("Sending message: %s\n", message);

        /* TODO: check send return status */
    }

    return 0; /* should never be reached */
}
