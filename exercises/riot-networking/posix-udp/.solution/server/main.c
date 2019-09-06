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

    int server_socket = socket(AF_INET6, SOCK_DGRAM, IPPROTO_UDP);
    if (server_socket < 0) {
        puts("error initializing socket");
        server_socket = 0;
        return 1;
    }

    struct sockaddr_in6 server_addr;
    server_addr.sin6_family = AF_INET6;
    memset(&server_addr.sin6_addr, 0, sizeof(server_addr.sin6_addr));
    server_addr.sin6_port = htons(SERVER_PORT);

    if (bind(server_socket, (struct sockaddr *)&server_addr,
             sizeof(server_addr)) < 0) {
        server_socket = -1;
        puts("error binding socket");
        return 1;
    }

    while (1) {
        int res;
        struct sockaddr_in6 src;
        socklen_t src_len = sizeof(struct sockaddr_in6);
        if ((res = recvfrom(server_socket, server_buffer, sizeof(server_buffer), 0,
                            (struct sockaddr *)&src, &src_len)) < 0) {
            puts("Error on receive");
        }
        else if (res == 0) {
            puts("Peer did shut down");
        }
        else {
            printf("Message received: ");
            puts(server_buffer);
            sendto(server_socket, SERVER_MESSAGE, sizeof(SERVER_MESSAGE), 0,
                   (struct sockaddr *)&src, sizeof(src));
        }
    }

    return 0;
}
