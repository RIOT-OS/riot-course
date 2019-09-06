#include <stdio.h>
#include "net/af.h"
#include "net/protnum.h"
#include "net/ipv6/addr.h"
#include "net/sock/udp.h"
#include "xtimer.h"

uint8_t buf[128];

#define CLIENT_MESSAGE "Hello Server"

int main(void)
{
    /* Create the local sock UDP endpoint */

    /* declare the remote sock UDP endpoint and assign the IPv6 address
       (link-local), based on SERVER_ADDR
       TIP: use ipv6_addr_from_str function to convert to an ipv6_addr_t
       */

    while (1) {
        /* Send CLIENT_MESSAGE to the remote */

        /* Wait for the reply of the server and print the reply */

        xtimer_sleep(1);
    }
    return 0;
}