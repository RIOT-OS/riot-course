## Expose sensor data via CoAP

### Introduction

In this exercise, we propose to expose the temperature and atmospheric pressure
values of a sensor via CoAP.
You will start an experiment on 2 iotlab-m3 boards on the FIT IoT-LAB testbed.
The iotlab-m3 boards provide a LPS331ap sensor, already supported by RIOT, so
we'll use it to read the temperature and atmospheric pressure.

### Prerequisites

1. Follow the riot-course [FIT IoT-LAB prerequites](https://riot-os.github.io/riot-course/slides/prerequisites/#4) (if not done already)
2. [Setup an experiment](https://github.com/riot-os/riot-course-exercises/tree/master/riot-networking/networking-iotlab#setup-an-experiment-on-fit-iot-lab)

In the rest of the exercice, we assume that you have booked 2 `iotlab-m3` boards
on the `paris` site:
- m3-10.paris.iot-lab.info
- m3-11.paris.iot-lab.info

### Flash the RIOT gcoap example application

This application is available on GitHub [here](https://github.com/riot-os/riot-course-exercises/tree/master/RIOT/examples/gcoap).
On the VM, you can access it at `~/riot-course/RIOT/examples/gcoap`

1. On the first board (here on **m3-10**), build, flash and open a terminal of
   the `gcoap` example application:

      $ make BOARD=iotlab-m3 IOTAB_NODE=m3-10.paris.iot-lab.info -C ~/riot-course/RIOT/examples/gcoap flash term

2. Ensure the shell is working:

      > help
      Command              Description
      ---------------------------------------
      coap                 CoAP example
      reboot               Reboot the node
      ps                   Prints information about running threads.
      ping6                Ping via ICMPv6
      random_init          initializes the PRNG
      random_get           returns 32 bit of pseudo randomness
      nib                  Configure neighbor information base
      ifconfig             Configure network interfaces
      > coap
      usage: coap <get|post|put|info>

### Write the CoAP server application

1. Go to `~/riot-course/riot-networking/gcoap-iotlab`

2. Edit the application `Makefile`: add the missing module for the sensor
   driver, e.g `lps331ap`

3. Edit the application `main.c` file:
  - Add the includes for the sensor driver:
  ```c
  #include "lpsxxx.h"
  #include "lpsxxx_params.h"
  ```
  - Declare the sensor variable
  ```c
  static lpsxxx_t sensor;
  ```
  - Implement the `_riot_pressure_handler` function:
    - Initialize the coap response:
    ```c
    gcoap_resp_init(pdu, buf, len, COAP_CODE_CONTENT);
    coap_opt_add_format(pdu, COAP_FORMAT_TEXT);
    size_t resp_len = coap_opt_finish(pdu, COAP_OPT_FINISH_PAYLOAD);
    ```
    - Format the response message:
    ```c
    char response[32];
    uint16_t pres;
    lpsxxx_read_pres(&sensor, &pres);
    sprintf(response, "%ihPa", pres);
    ```
    - Return the response to the caller:
    ```c
    if (pdu->payload_len >= strlen(response)) {
        memcpy(pdu->payload, response, strlen(response));
        return resp_len + strlen(response);
    }
    else {
        puts("gcoap: msg buffer too small");
        return gcoap_response(pdu, buf, len, COAP_CODE_INTERNAL_SERVER_ERROR);
    }
    ```
  - Follow the same strategy to implement the `_riot_temperature_handler`
    function

4. Verify that it builds and flash it on the second board (here **m3-11**):

      $ make BOARD=iotlab-m3 IOTAB_NODE=m3-11.paris.iot-lab.info flash term

5. Check the link-local IP address of the `m3-11` that is printed at startup:

      Configured network interfaces:
      Iface  7  HWaddr: 3E:26  Channel: 26  Page: 0  NID: 0x23
          Long HWaddr: 15:11:6B:10:65:FB:BE:26 
           TX-Power: 0dBm  State: IDLE  max. Retrans.: 3  CSMA Retries: 4 
          AUTOACK  ACK_REQ  CSMA  L2-PDU:102 MTU:1280  HL:64  6LO  
          IPHC  
          Source address length: 8
          Link type: wireless
          inet6 addr: fe80::1711:6b10:65fb:be26  scope: local  VAL
          inet6 group: ff02::1

  Here the address is **fe80::1711:6b10:65fb:be26**

6. Read the temperature and pressure value from the first board (e.g **m3-10**):

      > coap get fe80::1711:6b10:65fb:be26 5683 /temperature
      gcoap: response Success, code 2.05, 8 bytes
      39.36°C
      > coap get fe80::1711:6b10:65fb:be26 5683 /pressure
      gcoap: response Success, code 2.05, 7 bytes
      1013hPa

Now let's continue with the
[networking slides](https://riot-os.github.io/riot-course/slides/04-networking-in-riot/#25).
