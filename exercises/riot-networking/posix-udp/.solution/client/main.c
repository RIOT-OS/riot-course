#include <stdio.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include "net/af.h"
#include "net/protnum.h"
#include "net/ipv6/addr.h"
#include "xtimer.h"

#define CLIENT_MESSAGE "Hello Server"

int main(void)
{
    /* Create the socket */
    int s = socket(AF_INET6, SOCK_DGRAM, IPPROTO_UDP);
    if (s < 0) {
        puts("error initializing socket");
        return 1;
    }

    /* configure the destination address */
    struct sockaddr_in6 dst;
    dst.sin6_family = AF_INET6;

    /* parse destination address */
    ipv6_addr_from_str((ipv6_addr_t *)&dst.sin6_addr, SERVER_ADDR);

    /* parse port */
    dst.sin6_port = htons(SERVER_PORT);

    while (1) {
        sendto(s, CLIENT_MESSAGE, strlen(CLIENT_MESSAGE), 0,
                   (struct sockaddr *)&dst, sizeof(dst));

        xtimer_sleep(1);
    }

    return 0;
}