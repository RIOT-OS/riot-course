
#include <stdio.h>

#include "fmt.h"
#include "net/gcoap.h"

/* include the lpsxxx headers */

/* declate the lpsxxx_t sensor variable (globally) */

/* import "ifconfig" shell command, used for printing addresses */
extern int _gnrc_netif_config(int argc, char **argv);

static ssize_t _riot_pressure_handler(coap_pkt_t* pdu, uint8_t *buf, size_t len, void *ctx);
static ssize_t _riot_temperature_handler(coap_pkt_t* pdu, uint8_t *buf, size_t len, void *ctx);

/* CoAP resources. Must be sorted by path (ASCII order). */
static const coap_resource_t _resources[] = {
    { "/pressure", COAP_GET, _riot_pressure_handler, NULL },
    { "/temperature", COAP_GET, _riot_temperature_handler, NULL },
};

static gcoap_listener_t _listener = {
    &_resources[0],
    sizeof(_resources) / sizeof(_resources[0]),
    NULL
};

static ssize_t _riot_pressure_handler(coap_pkt_t *pdu, uint8_t *buf, size_t len, void *ctx)
{
    (void)ctx;

    /* Implement pressure GET handler */

}

static ssize_t _riot_temperature_handler(coap_pkt_t *pdu, uint8_t *buf, 
                                         size_t len, void *ctx)
{
    (void)ctx;

    /* Implement temperature GET handler */

}

int main(void)
{
    xtimer_sleep(2);
    /* print network addresses */
    puts("Configured network interfaces:");
    _gnrc_netif_config(0, NULL);

    /* Initialize and enable the lps331ap device */

    /* Register the gcoap listener */

    return 0;
}
