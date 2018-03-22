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

    - History of the project
    - RIOT's philosophy
    - The community
    - Competitors
    - RIOT users

2. Getting started with RIOT

    - Setup your environment
    - Build your first application
    - Using the native target
    - Debug your application

3. RIOT internals

    - Structure and organization of the operating system
    - Main modules of RIOT
    - Hardware abstraction layer and drivers
    - External packages

---

## Day two

1. Networking with RIOT

    - An overview of available stacks

    - GNRC: Generic Network Stack

    - Practicing on IoT-LAB

2. Using LoRaWAN with RIOT

    - An overview of LoRaWAN

    - Using RIOT with TheThingsNetwork

    - Building a LoRa device application with RIOT

---

## About me

<br/><br/>

- Research engineer at Inria in Saclay

- 10 years of experience in medical imaging

- Since 2015, open source contributor in Python and embedded projects

- RIOT maintainer since 2016

- FIT/IoT-LAB team member (https://www.iot-lab.info)

<br/><br/>

.center[<img src="images/inria_logo.png" alt="" style="width:150px;">]

---

class: center, middle

# Introduction

---

## What is RIOT

<br><br>

RIOT is

- a real-time multithreaded operating system

- built with in-house networking capababilities

- designed for microcontroller based devices

- open-source: https://github.com/RIOT-OS/RIOT

<br><br>

.center[
    <img src="images/riot.png" alt="" style="width:200px;"/>
]

---

## RIOT in the IoT world

.center[<img src="images/iot-overview.png" alt="" style="width:600px;"/>
<br/><br/>
<br/><br/>
&#x21d2; RIOT is designed for low-end devices
<br>(kB RAM, MHz, mW)
]

---

## History of the project

- 2008: Firekernel, micro-kernel for wireless sensor networks

- 2013: Inria & FU Berlin funded RIOT

- The community today:

  - Almost 180 contributors since the beginning

  - Academics: Inria, FU Berlin, HAW Hamburg, Berkeley, UCLA, MIT, TZI

  - Industrial: Thalès, Cisco, Samsung, ImgTec

  - SME: Zolertia, OTAKeys, Mesotic, Eisoc, We-sens

- Annual RIOT Summit: https://summit.riot-os.org

.right[
<img src="images/riot-summit.png" alt="" style="width:250px;margin-top:-40px"/>
]

---

## The philosophy behind RIOT

- RIOT is free-software, licensed under LGPLv2.1

- The community takes inspiration from Linux

- Decisions and orientations are taken by a grass-root community

- Use standards whenever possible <br>
  (C-ANSI, standard tools, standard protocols, standard procedures)

- Avoid code duplication

---

## Competitors

.center[
    <img src="images/os-timeline.png" alt="" style="width:600px;"/>
]
<div style="position: absolute;right: 100px;">
<span style="font-style: italic;font-size:12px;text-align:right">
Reference: O. Hahm et al. "Operating Systems for Low-End Devices<br>
in the Internet of Things: A survey," IEEE Internet of ThingsJournal, 2016.
</span>
</div>
<br>
<br>

- TinyOS: less active

- FreeRTOS: widely used RTOS

- Contiki: philosophy most similar to RIOT

- Zephyr: very active and sponsored by Intel

- Mbed OS: very active and sponsored by ARM

---

## Who is using RIOT

**IoT solutions deployments**

- LoRa devices in a Copper mine with Telephonica (Chile)<br>
http://summit.riot-os.org/2017/blog/2017/10/06/slides/

- Automatic cereal dispenser with Almagro (Chile)<br>
https://www.indiegogo.com/projects/the-venture-algramo-chile#/

- Fujitsu: IoT modules orchestration<br>
http://riot-os.org/files/RIOT-Summit-2017-slides/4-3-Virtualization-Session-Fujitsu.pdf

- Cisco, Huawei: experimental deployment using ICN-IoT

**IoT products**

- OTAKeys (Continental): On-Board diagnostics for connected cars

- Hamilton IoT (USA), Unwired devices (Russia)

- we-sens.com, mesotic

- Sleeping Beauty:  GPS tracking device with an integrated GSM modem

---

class: center, middle

# Technical overview

<br/>
Long story short:<br/>
http://riot-os.org/files/2018-IEEE-IoT-Journal-RIOT-Paper.pdf

---

## OS characteristics

- Microkernel architecture, RTOS, IPC, threads

- External packages

---

## OS characteristics

High-level features:

- filesystems,

- displays

- network stacks and protocols,

---

## Hardware support overview

- 8/16/32 bit, ARM, AVR, MIPS
- native port: can run as process on your computer
- Vendors: Microchip, NXP, STMicroelectronics, Nordic, TI, etc
- Large list of sensors and actuators supported (e.g drivers)
- Concept of "board" simplifying ports => +100 boards supported

---

## Ecosystem & community processes

- Tooling and build system
  - hand crafted makefiles for building a RIOT application
  - On-Chip debugging with OpenOCD and GDB

- Distributed and fast CI, Murdock: https://ci.riot-os.org

- In-depth code reviews

- Online documentation generated with Doxygen: https://doc.riot-os.org

---

class: center, middle

# Getting started

---

## Prerequisites: setup your environment

- vagrant
- install required toolchains: ARM, AVR, MIPS, etc
- install flash tools: OpenOCD
- Use the provided VMs

---

## 