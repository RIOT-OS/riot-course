
#include <stdio.h>

#include "fmt.h"
#include "net/gcoap.h"

#include "lpsxxx.h"
#include "lpsxxx_params.h"

static lpsxxx_t sensor;

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
    gcoap_resp_init(pdu, buf, len, COAP_CODE_CONTENT);
    coap_opt_add_format(pdu, COAP_FORMAT_TEXT);
    size_t resp_len = coap_opt_finish(pdu, COAP_OPT_FINISH_PAYLOAD);

    char response[32];
    uint16_t pres;
    lpsxxx_read_pres(&sensor, &pres);
    sprintf(response, "%ihPa", pres);

    /* write the RIOT board name in the response buffer */
    if (pdu->payload_len >= strlen(response)) {
        memcpy(pdu->payload, response, strlen(response));
        return resp_len + strlen(response);
    }
    else {
        puts("gcoap: msg buffer too small");
        return gcoap_response(pdu, buf, len, COAP_CODE_INTERNAL_SERVER_ERROR);
    }
}

static ssize_t _riot_temperature_handler(coap_pkt_t *pdu, uint8_t *buf, 
                                         size_t len, void *ctx)
{
    (void)ctx;
    gcoap_resp_init(pdu, buf, len, COAP_CODE_CONTENT);
    coap_opt_add_format(pdu, COAP_FORMAT_TEXT);
    size_t resp_len = coap_opt_finish(pdu, COAP_OPT_FINISH_PAYLOAD);

    char response[32];
    int16_t temp;
    lpsxxx_read_temp(&sensor, &temp);
    int temp_abs = temp / 100;
    temp -= temp_abs * 100;
    sprintf(response, "%2i.%02i°C",temp_abs, temp);

    /* write the temperature value in the response buffer */
    if (pdu->payload_len >= strlen(response)) {
        memcpy(pdu->payload, response, strlen(response));
        return resp_len + strlen(response);
    }
    else {
        puts("gcoap: msg buffer too small");
        return gcoap_response(pdu, buf, len, COAP_CODE_INTERNAL_SERVER_ERROR);
    }
}

int main(void)
{
    if (lpsxxx_init(&sensor, &lpsxxx_params[0]) != LPSXXX_OK) {
        puts("LPS331AP initialization failed");
        return 1;
    }
    lpsxxx_enable(&sensor);

    xtimer_sleep(2);

    /* print network addresses */
    puts("Configured network interfaces:");
    _gnrc_netif_config(0, NULL);

    gcoap_register_listener(&_listener);

    return 0;
}
