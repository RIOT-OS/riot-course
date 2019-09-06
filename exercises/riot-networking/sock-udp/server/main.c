#include <stdio.h>
#include "shell.h"
#include "net/sock/udp.h"

/* import "ifconfig" shell command, used for printing addresses */
extern int _gnrc_netif_config(int argc, char **argv);

uint8_t buf[128];

int main(void)
{
    /* print network addresses */
    puts("Configured network interfaces:");
    _gnrc_netif_config(0, NULL);

    /* Create the local sock UDP endpoint */

    while (1) {
        /* Declare the remote sock UDP endpoint*/

        /* Start receiving messages, echo reply in case of success */
    }
    return 0;
}
