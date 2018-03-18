class: center, middle

<br/><br/><br/><br/><br/><br/>

# RIOT Workshop

### Hands-on tutorial

<br/><br/><br/><br/>

.footnote[
Alexandre Abadie, Inria
]

---

## Day one

1. Introduction

2. Getting started with RIOT

    - Setup your environment
    - Build your first application
    - Using the native target
    - Debug your application

3. RIOT internals

    - Structure and organization of the operating system
    - Main modules of RIOT
    - Hardware support and drivers
    - External packages

---

## Day two

1. Networking with RIOT

    - An overview of available stacks
    - GNRC: Generic Network Stack
    - Practicing on IoT-LAB

2. Using LoRaWAN with RIOT

---

## What is RIOT?

RIOT is

- a real-time operating system

- built with networking capababilities

- targetting microcontroller based devices

---

## RIOT in the IoT world

.center[<img src="images/iot-overview.png" alt="" style="width:600px;"/>]

---

## RIOT in the IoT world

.center[<img src="images/iot-overview-high-end.png" alt="" style="width:600px;"/>]

---

## RIOT in the IoT world

.center[<img src="images/iot-overview-low-end.png" alt="" style="width:600px;"/>

&#x21d2; RIOT is useful on low-end devices]

---

## History of the project

2008: Firekernel, micro-kernel for wireless sensor networks

2013: Inria with FU Berlin funded RIOT

---

## The philosophy behind RIOT

LGPLv2.1

Follow Linux principle

Grass-root

---

## The community today

Academics

RIOT Summit

---

## Competitors

Oleg picture

Contiki
FreeRTOS
Zephyr
Mbed OS

---

## Technical aspects

Hardware support: 8/16/32-bit, AVR,MIPS,ARM

Use standard tools: make, gdb

---

## Technical aspects

Microkernel based

