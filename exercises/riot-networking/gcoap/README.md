## A simple CoAP server

### Introduction

In this exercise, we propose to expose different kind of CoAP resources,
accessible via GET, PUT and POST requests:
- `/riot/board` returns the name of the board running RIOT
- `/riot/cpu` returns the name of the cpu running RIOT
- `/value` returns an arbitrary value, equal to 0 by default. This value can be
  updated using `PUT` and `POST` requests.

You will send CoAP requests to one RIOT native instance from the VM (or your
computer) using the [aiocaop](https://aiocoap.readthedocs.io/en/latest/) Python
package clients.

### Exercise

1. Go into the `~/riot-course/exercises/riot-networking/gcoap` application
  directory

2. Add the `gcoap` and `fmt` modules dependency to the application `Makefile`:
  ```mk
  USEMODULE += gcoap
  USEMODULE += fmt
  ```
3. Add the list of ressources, in the form {`<path>`, `<method>`, `<handler function>`, `<context>`}:
  ```c
    { "/riot/board", COAP_GET, _riot_board_handler, NULL },
    { "/riot/cpu", COAP_GET, _riot_cpu_handler, NULL },
    { "/value", COAP_GET | COAP_PUT | COAP_POST, _value_handler, NULL },
  ```
4. Declare the gcoap listener:
  ```c
  static gcoap_listener_t _listener = {
      &_resources[0],
      sizeof(_resources) / sizeof(_resources[0]),
      NULL
  };
  ```
5. Register the coap listener:
  ```c
  gcoap_register_listener(&_listener);
  ```
6. Implement the riot board GET handler:
  - Initialize the request response:
  ```c
  gcoap_resp_init(pdu, buf, len, COAP_CODE_CONTENT);
  coap_opt_add_format(pdu, COAP_FORMAT_TEXT);
  size_t resp_len = coap_opt_finish(pdu, COAP_OPT_FINISH_PAYLOAD);
  ```
  - Sends the response with the content of the board type (contained in the
    `RIOT_BOARD` macro):
  ```c
  /* write the RIOT board name in the response buffer */
  if (pdu->payload_len >= strlen(RIOT_BOARD)) {
      memcpy(pdu->payload, RIOT_BOARD, strlen(RIOT_BOARD));
      return resp_len + strlen(RIOT_BOARD);
  }
  else {
      puts("gcoap: msg buffer too small");
      return gcoap_response(pdu, buf, len, COAP_CODE_INTERNAL_SERVER_ERROR);
  }
  ```
7. Implement the riot cpu GET handler on the same principle as the riot board:
  use `RIOT_CPU` macro instead of `RIOT_BOARD`.
8. Implement the `/value` GET, PUT/POST handler:
  - Read coap method flag in the packet:
  ```c
   unsigned method_flag = coap_method2flag(coap_get_code_detail(pdu));
  ```
  - Implement GET request reply:
  ```c
  gcoap_resp_init(pdu, buf, len, COAP_CODE_CONTENT);
  coap_opt_add_format(pdu, COAP_FORMAT_TEXT);
  size_t resp_len = coap_opt_finish(pdu, COAP_OPT_FINISH_PAYLOAD);

  /* write the response buffer with the request count value */
  resp_len += fmt_u16_dec((char *)pdu->payload, _value);
  return resp_len;
  ```
  - Implement the PUT/POST request reply:
  ```c
  if (pdu->payload_len <= 5) {
      char payload[6] = { 0 };
      memcpy(payload, (char *)pdu->payload, pdu->payload_len);
      _value = (uint16_t)strtoul(payload, NULL, 10);
      return gcoap_response(pdu, buf, len, COAP_CODE_CHANGED);
  }
  else {
      return gcoap_response(pdu, buf, len, COAP_CODE_BAD_REQUEST);
  }
  ```
9. Build and start the coap server application on `tap0`. Note the link-local
  address of the server application:
  ```sh
  $ make -C ~/riot-course/exercises/riot-networking/gcoap
  $ make PORT=tap0 -C ~/riot-course/exercises/riot-networking/gcoap term
  Configured network interfaces:
  Iface  5  HWaddr: F2:9D:F4:58:14:D4
          L2-PDU:1500 MTU:1500  HL:64  Source address length: 6
          Link type: wired
          inet6 addr: fe80::f09d:f4ff:fe58:14d4  scope: local  TNT[1]
          inet6 group: ff02::1
          inet6 group: ff02::1:ff58:14d4
  ```
  Here the link-local address of the CoAP server is **fe80::f09d:f4ff:fe58:14d4**.
  Keep the terminal open and the server application running.
10. From the VM (or your computer), use `aiocoap-client` to send requests to the
  CoAP server (note the `%tapbr0` added at the end of the server link-local
  address):
  - Get the `/riot/board` and `/riot/cpu` resources:
  ```
  $ aiocoap-client -m get coap://[fe80::f09d:f4ff:fe58:14d4%tapbr0]/riot/board
  native
  $ aiocoap-client -m get coap://[fe80::f09d:f4ff:fe58:14d4%tapbr0]/riot/cpu
  native
  ```
  - Verify the `value` can correctly be retrieved and changed using CoAP:
  ```
  $ aiocoap-client -m get coap://[fe80::f09d:f4ff:fe58:14d4%tapbr0]/value
  0
  $ aiocoap-client -m put coap://[fe80::f09d:f4ff:fe58:14d4%tapbr0]/value --payload 42
  $ aiocoap-client -m get coap://[fe80::f09d:f4ff:fe58:14d4%tapbr0]/value
  42
  $ aiocoap-client -m post coap://[fe80::f09d:f4ff:fe58:14d4%tapbr0]/value --payload 10
  $ aiocoap-client -m get coap://[fe80::f09d:f4ff:fe58:14d4%tapbr0]/value
  10
  ```

Now let's continue with the
[networking slides](https://riot-os.github.io/riot-course/slides/04-networking-in-riot/#25).
