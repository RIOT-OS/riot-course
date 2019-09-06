#include <stdio.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include "shell.h"

/* import "ifconfig" shell command, used for printing addresses */
extern int _gnrc_netif_config(int argc, char **argv);

static char server_buffer[128];

#define SERVER_MESSAGE "Hello client"

int main(void)
{
    /* print network addresses */
    puts("Configured network interfaces:");
    _gnrc_netif_config(0, NULL);

    /* Create the socket */

    /* Configure the server address */

    /* Bind the socket to the local address */

    while (1) {
        /* Wait for incoming messages, if a message is received, reply SERVER_MESSAGE */
    }

    return 0;
}
