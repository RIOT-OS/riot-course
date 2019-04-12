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

## Available IPv6 stacks

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

## The GNRC stack of RIOT

.center[
    <img src="images/riot-gnrc-stack.png" alt="" style="width:400px;"/>
]

- Radio drivers are accessed through the **netdev** API

- All internal components use a single API: **netapi**

- The applications uses the **sock** API (previously called `conn`)

---

## Network device driver API

<br>

.center[
    <img src="images/netdev-rx.png" alt="" style="width:500px;"/>
]

- Radio events trigger interrupts &#x21d2; ISR context

- RIOT makes a good use of thread to manage them nicely<br>
  &#x21d2; move fast from ISR context to netdev thread context

- More information here: <br>
http://doc.riot-os.org/group__drivers__netdev__api.html

---

## Basic IPv6 networking using the shell: practice

- **Exercise:** `~/riot-course/exercises/riot-networking/shell-basic-native`

Follow the [exercise README](https://github.com/aabadie/riot-course-exercises/tree/master/riot-networking/shell-basic-native)

- **Exercise:** `~/riot-course/exercises/riot-networking/shell-udp-native`

Follow the [exercise README](https://github.com/aabadie/riot-course-exercises/tree/master/riot-networking/shell-udp-native)

---

## The CoAP protocol

---

## Using CoAP: practice

- **Exercise:** `~/riot-course/exercises/riot-networking/shell-coap-native`

Follow the [exercise README](https://github.com/aabadie/riot-course-exercises/tree/master/riot-networking/shell-coap-native)

---

## Using CoAP: practice (old)

- Build the `nanocoap_server` example application for native:

```sh
$ make -C ~/RIOT/examples/nanocoap_server all
```

- Start a native instance of RIOT:

```sh
$ sudo PORT=tap0 make -C ~/RIOT/examples/nanocoap_server term
main(): This is RIOT! (Version: workshop-captronic)
RIOT nanocoap example application
Waiting for address autoconfiguration...
Configured network interfaces:
Iface  5  HWaddr: 0a:46:47:86:27:e8 
          MTU:1500  HL:64  Source address length: 6
          Link type: wired
          inet6 addr: fe80::846:47ff:fe86:27e8  scope: local
```

- From the Linux host, query the CoAP server running on the native instance:

```sh
$ coap-client -m get coap://[fe80::846:47ff:fe86:27e8%tapbr0]/.well-known/core
v:1 t:CON c:GET i:b615 {} [ ]
</.well-known/core>,</riot/board>,</riot/value>
$ coap-client -m get coap://[fe80::846:47ff:fe86:27e8%tapbr0]/riot/board
v:1 t:CON c:GET i:c84c {} [ ]
native
```
---

## Testing IPv6 on hardware

We will use an experiment platform called IoT-LAB: https://www.iot-lab.info
<br><br>

.center[
    <img src="images/iot-lab-principle.png" alt="" style="width:700px;"/>
]

.right[
    <img src="images/iotlab-photo.png" alt="" style="width:250px;margin-top:-60px; margin-right:-20px"/>
]

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
