class: center, middle

# Networking in RIOT

---

## IoT in the digital world


.center[
    <img src="images/iot-global-overview.png" alt="" style="width:800px;"/>
]

.right[<span style="font-style: italic;font-size:12px">Source: https://www.keysight.com/upload/cmc_upload/All/Slide_IOT_Part_1.pdf</span>]

---

## Overview of networking technologies for IoT

.center[
    <img src="images/iot-protocols-overview.png" alt="" style="width:800px;"/>
]

---

## Mapping IoT technologies to OSI layers

.center[
    <img src="images/iot-stacks.png" alt="" style="width:700px;"/>
    <br><br>
    &#x21d2; RIOT supports ZigBee (6LowPAN), Thread and soon BLE and WiFi
]

---

## Lots of IoT specifications exist

- **Physical layer**

  &#x21d2; PLC, BACnet, Z-WAze, BLE, IEEE 802.15.4, LoRa, SigFox, IEEE 802.11

- **Network layer** interop with IP networks

  &#x21d2; 6TiSCH, 6LowPAN, RPL, OLSRv2, AODVv2, LoRaWAN

- **Application layer** interop with the Web

  &#x21d2; CoAP, LwM2M, MQTT, CBOR, DTLS, OSCOAP

- **New paradigms**

  &#x21d2; Information centric network (ICN)

.right[
    <img src="images/riot-802154-stack.png" alt="" style="width:210px;margin-top:-50px"/>
]

---

## Networking architecture in RIOT

&#x21d2; designed to integrate any network stack into RIOT

<table>
<tr>
  <td>
    <ul>
      <li>Network layer is decoupled from the hardware via the <b>netdev</b> API<br><br></li>
      <li>Application layer is decoupled from network stack via the <b>sock</b> API<br><br></li>
      <li>Each device driver runs in its <b>own thread</b><br><br></li>
      <li>Radio drivers are implemented in `drivers`<br><br></li>
      <li>Network APIs are defined in `sys/include/net` and implemented in `sys/net`<br><br></li>
    </ul>
  </td>
  <td>
.center[
    <img src="images/riot-network-stack.png" alt="" style="width:200px;"/>
]
  </td>
</tr>
</table>

---

## Available IP stacks

- **GNRC**
  - Generic in-house network stack

- **LwIP**
  - full featured network stack
  - provided as a package in `pkg/lwip`

- **emb6**
  - port of Contiki stack without protothreads
  - provided as a package in `pkg/emb6`

- **OpenThread**
  - Opensource implementation of the Thread specifications
  - provided as a package in `pkg/openthread`

---

## Other stacks

- **Bluetooth Low Energy** (BLE) stack
  - based on the [Apache Mynewt NimBLE](https://github.com/apache/mynewt-nimble)
    library

- **Controller Area Network** (CAN) stack
  - Native mode (SocketCAN) + driver for TJA1042 + STM32 peripheral driver

- **LoRaWAN**:
  - based Semtech [Loramac-node](https://github.com/Lora-net/LoRaMac-node)
    reference implementation
  - provided as a package in `pkg/semtech-loramac`


---

## Network device driver API

<table>
<tr>
  <td>
.center[
    <img src="images/netdev-rx.png" alt="" style="width:450px;"/>
]
<ul>
<li>Radio events trigger interrupts &#x21d2; ISR context</li>

<li>Use threads messaging to manage them nicely<br>
  &#x21d2; move fast from ISR context to netdev thread context</li>

<li>
    <a href="http://doc.riot-os.org/group__drivers__netdev__api.html">
        http://doc.riot-os.org/group__drivers__netdev__api.html
    </a>
</li>
</ul>
  </td>
  <td>
.center[
    <img src="images/riot-network-stack.png" alt="" style="width:200px;"/>
]
  </td>
</tr>
</table>

---

## The GNRC stack of RIOT

.center[
    <img src="images/riot-gnrc-stack.svg" alt="" style="width:400px;"/>
]

- Radio drivers are accessed through the **netdev** API

- All internal components use a single API: **netapi**

- The applications uses the **sock** API

---

## Basic IPv6 networking using the shell: practice

- **Exercise:** `~/riot-course/exercises/riot-networking/shell-basic-native`

Follow the [exercise README](https://github.com/aabadie/riot-course-exercises/tree/master/riot-networking/shell-basic-native)

- **Exercise:** `~/riot-course/exercises/riot-networking/shell-udp-native`

Follow the [exercise README](https://github.com/aabadie/riot-course-exercises/tree/master/riot-networking/shell-udp-native)

---

## Networking modules

- **GNRC:** All networking modules are loaded with the **gnrc_ipv6_default** module

- **lwIP**:

  - IPv4 networking modules are loaded with **lwip_ipv4**

  - IPv6 networking modules are loaded with **lwip_ipv6**

- Device drivers modules:

  - 802.15.4 drivers: <br>
    &#x21d2; **at86rf2xx**, **cc2420**, **kw2xrf**, **mrf24j40**, **xbee**

  - Ethernet drivers: <br>
    &#x21d2; **enc28j60**, **w5100**, **esp32**, **esp8266**

  - Also use **auto_init** for automatic initialization of drivers


---

## IPv6 addresses manipulations

- IPv6 manipulation functions are provided by the `ipv6_addr` module

- See: http://doc.riot-os.org/group__net__ipv6__addr.html

- Some useful functions:

```c
/* is loopback (::1) */
static bool ipv6_addr_is_loopback (const ipv6_addr_t *addr);

/* is mulicast (ff02::1, ff02::2, etc) */
static bool ipv6_addr_is_multicast (const ipv6_addr_t *addr);

/* is link local (fe80:x:x:z::/64) */
static bool ipv6_addr_is_link_local (const ipv6_addr_t *addr);

/* is global */
static bool ipv6_addr_is_global (const ipv6_addr_t *addr);

/* convert from string */
ipv6_addr_t * ipv6_addr_from_str (ipv6_addr_t *result, const char *addr);

/* convert to string */
char * ipv6_addr_to_str (char *result, const ipv6_addr_t *addr,
                         uint8_t result_len);
```

---

## The Sock API (1)

- Provides a common abstraction on top of any IP stack

- An application built on top of Sock is portable on any network stack

- 3 kinds of sock types provided:<br><br>
  &#x21d2; **Raw IPv4/IPv6**, **UDP** and **TCP**

- Depending on the stack used, import the right modules:<br><br>
  &#x21d2; with GNRC, modules are **gnrc_sock_ip**, **gnrc_sock_udp**, **gnrc_sock_tcp**

- More information: http://doc.riot-os.org/group__net__sock.html

---

## The Sock API (2)

- 3 different types:

  - **sock_ip_t**, include from `net/sock/ip.h`<br>
    &#x21d2; http://doc.riot-os.org/group__net__sock__ip.html

  - **sock_udp_t**, include from `net/sock/udp.h`<br>
    &#x21d2; http://doc.riot-os.org/group__net__sock__udp.html

  - **sock_tcp_t**, include from `net/sock/tcp.h`<br>
    &#x21d2; http://doc.riot-os.org/group__net__sock__tcp.html

- 4 functions to use (`<type>` can be `ip`, `udp` or `tcp`):

```c
/* Create the sock instance */
int sock_<type>_create(sock_<type>_t *sock, const sock_<type>_ep_t *local,
                       const sock_<type>_ep_t *remote, ...);
/* Send a packet using the sock instance to a remote */
ssize_t sock_<type>_send(sock_<type>_t *sock, const void *data, size_t len, ...,
                         const sock_<type>_ep_t *remote);
/* Wait for incoming packets from a remote */
ssize_t sock_<type>_recv(sock_<type>_t *sock, void *data, size_t max_len,
                         uint32_t timeout, sock_<type>_ep_t *remote);
/* Close the sock instance */
void sock_<type>_close(sock_<type>_t *sock);
```

---

## UDP client-server application: practice

**Exercise:** `~/riot-course/exercises/riot-networking/sock-udp`

Follow the [exercise README](https://github.com/aabadie/riot-course-exercises/tree/master/riot-networking/sock-udp)

---

## The Posix Socket API

- Provides a Posix compliant networking API

- Import module **posix_sockets**

- Use
```c
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
```

- Functions come from the Posix socket API:
```c
/* Create a socket */
int socket(int socket_family, int socket_type, int protocol);
/* Assign an address to the socket */
int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
/* Wait for incoming packets */
ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags,
                 struct sockaddr *src_addr, socklen_t *addrlen);
/* Send packets */
ssize_t sendto(int sockfd, const void *buf, size_t len, int flags,
               const struct sockaddr *dest_addr, socklen_t addrlen);
```

---

## UDP client-server application: practice

**Exercise:** `~/riot-course/exercises/riot-networking/posix-udp`

Follow the [exercise README](https://github.com/aabadie/riot-course-exercises/tree/master/riot-networking/posix-udp)

---

## The CoAP protocol

- CoAP is an HTTP-like designed for very small devices<br>
  &#x21d2; built on top of UDP, standard port is **5683**

- Standard from CORE working group at IETF<br>
  &#x21d2; RFC 7252 https://tools.ietf.org/html/rfc7252<br>
  &#x21d2; RFC 7959 https://tools.ietf.org/html/rfc7959<br>
  &#x21d2; RFC 8323 https://tools.ietf.org/html/rfc8323<br>

- 4 types of requests: `GET`, `POST`, `PUT`, `DELETE`

- `.well-known/core` URI describes the list of URIs on a CoAP server

- Others options: `OBSERVE`, Block-wise transfer

.center[
    <img src="images/coap-header.png" alt="" style="width:500px;"/>
]

---

## CoAP implementations

- Several implementations exists, in multiple languages:<br><br>

  &#x21d2; See http://coap.technology/impls.html

- RIOT provides support for CoAP:

  - Natively with **nanocoap** and **gcoap** modules

  - Via packages with **microcoap**

- **nanocoap**

  - designed to very memory efficient
  - limited features

- **gcoap**

  - provides more features: `OBSERVE`, coap client API
  - less memory efficient

---

## Using CoAP: practice

- **Exercise:** `~/riot-course/exercises/riot-networking/shell-coap-native`

Follow the [exercise README](https://github.com/aabadie/riot-course-exercises/tree/master/riot-networking/shell-coap-native)

---

## Using the gcoap API to setup a CoAP server (1)

- Include the required header
```c
#include "net/gcoap.h"
```
- Define a list of resources in an array of `coap_resource_t`:
```c
static const coap_resource_t _resources[] = {
        { "/coap/url", COAP_GET | COAP_PUT, _handler, NULL },
}
```
- The handler function signature is:
```c
static ssize_t _handler(coap_pkt_t* pdu, uint8_t *buf,
                            size_t len, void *ctx);
```
- Use other gcoap functions to format the reply:
```c
/* Initialize the reply */
gcoap_resp_init(coap_pkt_t *pdu, uint8_t *buf, size_t len, unsigned code);
/* Send the reply */
ssize_t gcoap_response(coap_pkt_t *pdu, uint8_t *buf,
                           size_t len, unsigned code);
```
---

## Using the gcoap API to setup a CoAP server (2)

- Register your resources in gcoap listener:
```c
static gcoap_listener_t _listener = {
    &_resources[0],
    sizeof(_resources) / sizeof(_resources[0]),
    NULL
};
```
- Finally, start the gcoap listener:
```c
gcoap_register_listener(&_listener);
```

- Find more details at http://doc.riot-os.org/group__net__gcoap.html

---

## Using gcoap: practice

- **Exercise:** `~/riot-course/exercises/riot-networking/gcoap`

Follow the [exercise README](https://github.com/aabadie/riot-course-exercises/tree/master/riot-networking/gcoap)

---

## Testing RIOT networking on hardware: use IoT-LAB

.center[<a href=https://www.iot-lab.info>https://www.iot-lab.info</a><br><br>
IoT-LAB is a large scale experimentation testbed]

  - Can be used for testing wireless communication networks on small devices

  - Can be used for learning IoT programming and communication protocols

  - Can be used for testing software platforms

.center[
      <img src="images/iotlab-sites.png" alt="" style="width:220px;"/>&nbsp;
      <img src="images/iotlab-nodes.png" alt="" style="width:220px;"/>&nbsp;
      <img src="images/iotlab-photo.png" alt="" style="width:220px;"/>
  ]

---

## IoT-LAB in short

- **2300** programmable nodes, 4 architectures
  <br> &#x21d2; Cortex-M, MSP430, Cortex-A8, AVR

- Heterogeneous platforms
  <br> &#x21d2; RPI3, iotlab-m3, Atmel SAMR21-Xpro, ST B-L072Z-LRWAN1, nrf52, etc

- Heterogeneous radios &#x21d2; 802.15.4, 802.15.4g, LoRa, BLE

- Start learning IoT with IoT-LAB at
  <a href=https://www.iot-lab.info/tutorials/>https://www.iot-lab.info/tutorials/</a>

.center[
      <img src="images/use-iotlab.png" alt="" style="width:450px;"/>
  ]

---

## Testing RIOT networking on hardware: practice




---

## Using an Atmel SAMR21 XPlained Pro on IoT-LAB

See: https://www.iot-lab.info/tutorials/use-samr21-nodes/

---

## Public IPv6 networking

See: https://www.iot-lab.info/tutorials/riot-public-ipv66lowpan-network-with-m3-nodes/

Small change:

- Use samr21-xpro instead of iotlab-m3

- Skip border-router related steps

---

## CoAP

See: https://www.iot-lab.info/tutorials/coap-using-riot-with-m3-nodes/

Small change:

- Use samr21-xpro instead of iotlab-m3

- Skip border-router related steps

---

class: center, middle

[Back to the course](https://github.com/aabadie/riot-course#content-of-the-course)
