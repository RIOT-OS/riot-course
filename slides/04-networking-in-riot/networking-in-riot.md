class: center, middle

# Networking in RIOT

---

## Overview of networking technologies for IoT

---

## Radio technologies

- 802.15.4 (ZigBee) => Mesh networks, designed for IoT

- LoRa, SigFox => Low power

- BLE => widely available

- WiFi, GSM => consumption problems

- NB-IoT, 5G for later

---

## Network protocols: mesh networks

=> 6LoWPAN/IPv6/RPL

Typical infrastructure

---

## Network protocols: start networks

LoRaWAN, SigFox

Typical infrastructure

---

## Application protocols

High level protocols

---

## Other protocols

- CANbus: automobile,

- BACnet, Z-Wave, Enocean, ANT: domotique

---

## The GNRC stack of RIOT

Architecture

---

## Principle

- One radio device per-thread

- Radio event in ISR context => message to the radio thread

---

## Netdev and netapi APIs

---

## Networking modules

---

## Other available stacks

- **LwIP**
  - full featured network stack
  - provided as a package in `pkg/lwip`

- **emb6**
  - port of Contiki stack without protothreads
  - provided as a package in `pkg/emb6`

- **OpenThread**
  - Opensource implementation of the Thread specifications
  - provided as a package in `pkg/openthread`

- **Controller Area Network** (CAN) stack
  - Native mode (SocketCAN) + driver for TJA1042

- **LoRaWAN**:
  - based Semtech Loramac-node reference implementation
  - provided as a package in `pkg/semtech-loramac`

---

class: center, middle

# IPv6 communication on IoT-LAB

---

## What is IoT-LAB

---

## IPv6 networking

---

### Principle of IoT-LAB

- Book nodes

- SSH to frontend server

- Interact with nodes using the serial link

---

## Starting an experiment on IoT-LAB

- SSH to the Saclay site frontend

- Launch an experiment on 2 nodes

---

## Interacting with the nodes locally

- Flash a firmware

- Interact with the node:
  - `ifconfig`
  - `udp server start 8888`
  - `udp server send`

---

## Public IPv6 networking

- Principle of the border router in RIOT

---

## CoAP messaging

---

## MQTT messaging

