
#include <stdio.h>

#include "fmt.h"
#include "net/gcoap.h"

/* import "ifconfig" shell command, used for printing addresses */
extern int _gnrc_netif_config(int argc, char **argv);

static uint16_t _value = 0;

static ssize_t _riot_board_handler(coap_pkt_t* pdu, uint8_t *buf, size_t len, void *ctx);
static ssize_t _riot_cpu_handler(coap_pkt_t* pdu, uint8_t *buf, size_t len, void *ctx);
static ssize_t _value_handler(coap_pkt_t* pdu, uint8_t *buf, size_t len, void *ctx);

/* CoAP resources. Must be sorted by path (ASCII order). */
static const coap_resource_t _resources[] = {

    /* Define the list of CoAP resources here, sorted by path (ASCII alphabetical order) */

};

/* Declare the gcoap listener */

static ssize_t _riot_board_handler(coap_pkt_t *pdu, uint8_t *buf, size_t len, void *ctx)
{
    (void)ctx;

    /* Implement the riot board GET handler */

}

static ssize_t _riot_cpu_handler(coap_pkt_t *pdu, uint8_t *buf, size_t len, void *ctx)
{
    (void)ctx;

    /* Implement the riot mcu GET handler */
    
}

static ssize_t _value_handler(coap_pkt_t* pdu, uint8_t *buf, size_t len, void *ctx)
{
    (void)ctx;

    /* read coap method flag in the packet */

    switch(method_flag) {
        case COAP_GET:
            /* implement the GET method */

        case COAP_PUT:
        case COAP_POST:
            /* implement PUT/POST methods */
    }

    return 0;
}


int main(void)
{
    /* print network addresses */
    puts("Configured network interfaces:");
    _gnrc_netif_config(0, NULL);

    /* register the gcoap listener */

    return 0;
}
