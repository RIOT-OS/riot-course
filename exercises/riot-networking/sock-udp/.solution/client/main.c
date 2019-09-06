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
    sock_udp_ep_t local = SOCK_IPV6_EP_ANY;
    sock_udp_t sock;
    local.port = 0xabcd;
    if (sock_udp_create(&sock, &local, NULL, 0) < 0) {
        puts("Error creating UDP sock");
        return 1;
    }

    sock_udp_ep_t remote = { .family = AF_INET6  };
    remote.port = SERVER_PORT;

    /* Convert server address from string to ipv6_addr_t */
    if (ipv6_addr_from_str((ipv6_addr_t *)&remote.addr.ipv6, SERVER_ADDR) == NULL) {
        puts("Cannot convert server address");
        sock_udp_close(&sock);
        return 1;
    }

    while (1) {
        if (sock_udp_send(&sock, CLIENT_MESSAGE, sizeof(CLIENT_MESSAGE),
                          &remote) < 0) {
            puts("Error sending message");
            sock_udp_close(&sock);
            return 1;
        }

        ssize_t res;
        if ((res = sock_udp_recv(&sock, buf, sizeof(buf), 1 * US_PER_SEC,
                                NULL)) < 0) {
            if (res == -ETIMEDOUT) {
                puts("Timed out");
            }
            else {
                puts("Error receiving message");
            }
        }
        else {
            printf("Received message: \"");
            for (int i = 0; i < res; i++) {
                printf("%c", buf[i]);
            }
            printf("\"\n");
        }
        xtimer_sleep(1);
    }
    return 0;
}