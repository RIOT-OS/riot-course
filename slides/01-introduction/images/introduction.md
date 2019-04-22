class: center, middle

# Introduction

---

## What is RIOT

- **operating system** for microcontrollers

 - **microkernel architecture** &#x21d2; require very low resources
 - **real-time** and **multi-threaded**
 - comes with **in-house networking stacks**

--

<br>

- **open-source**: <a href="https://github.com/RIOT-OS/RIOT">https://github.com/RIOT-OS/RIOT</a>

 - free software platform
 - **world-wide community** of developers

--

<br>

- **easy to use** and __reuse__

 - Standard programming in C
 - Standard tooling
 - **API is independent** from the hardware

<br><br>

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

- 2013: Inria, FU Berlin and HAW founded RIOT

 - stemed from a French-German research project
 - kernel evolved from FireKernel

--

- The community today:

  - So far, **+200** different contributors to the master branch
  - Academics: Berkeley, UCLA, MIT, AIT, TZI, etc
  - Industrial: Cisco, Samsung, ImgTec, Fujitsu, Thalès
  - SME: Zolertia, OTAKeys, Mesotic, Eistec, We-sens
  - Member of the EdgeXFoundry initiative

--

- Annual RIOT Summit: https://summit.riot-os.org

.center[
<img src="images/riot-summit.png" alt="" style="width:220px;"/>&nbsp;
<img src="images/summit-2018.jpg" alt="" style="width:220px;"/>
]

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

 - requires less memory & adapts to a wider range of architectures

 - fosters an open-source philosophy more akin to Linux

 - provides more integrated high-level functionalities

---

## The RIOT philosophy & community

- RIOT is free-software, licensed under **LGPLv2.1**

- The community takes inspiration from Linux

<img src="images/linux.jpg" alt="" style="width:150px;position:fixed;top:120px;right:100px;"/>

--

- Use standards whenever possible <br>
  (C-ANSI, standard tools, standard protocols, standard procedures)

- Follow **POSIX** standards

--

- Avoid code duplication, easy to program, increase **portability**, modularity

- Vendor & Technology **independence**

--

- Decisions and orientations are taken by a **grass-root community**

.center[
    <img src="images/riot-contributors.png" alt="" style="width:350px"/>
]

---

## Ecosystem & community processes

- Standard tooling and build system: **Makefiles**, **OpenOCD**, **GDB**

--

- Distributed and fast CI, Murdock: https://ci.riot-os.org

    &#x21d2; **Build and run** all test/example applications<br><br>
    &#x21d2; **Static tests** (Cppcheck, Coccinelle, etc)<br>

.center[
<img src="images/murdock.png" alt="" style="width:400px"/>
]
--

- **Online documentation** &#x21d2; https://doc.riot-os.org

--

- In-depth **code reviews**

- Stable **release every 3 months**: &lt;year&gt;.&lt;month&gt; (ex: 2018.07, 2018.10, etc)


---

class: center, middle

# Technical overview

<br/>
Long story short: paper in IEEE Internet of Things Journal<br/>
Preprint available: http://riot-os.org/files/2018-IEEE-IoT-Journal-RIOT-Paper.pdf

---

## OS characteristics

- **Micro-kernel** based architecture: modular approach

<img src="images/riot-architecture.png" alt="" style="width:250px;position:fixed;right:50px;top:120px"/>

--

- Small footprint <br> &#x21d2; **2.8kB** RAM, **3.2kB** ROM on 32-bit Cortex-M

--

- **Real-Time** scheduler
  - &#x21d2; fixed priorities preemption with O(1) operations
  - &#x21d2; tickless scheduler

--

- **Multi-Threading** and IPC:
  - Separate thread contexts with separate <br>thread memory stack
  - Minimal thread control block (TCB)
  - Thread synchronization using mutexes, <br>semaphores and messaging

<img src="images/riot-application.png" alt="" style="width:300px;position:fixed;right:50px;top:350px"/>

---

## Multi-Threading

2 threads by default:

- the `main` thread: running the `main` function

- the `idle` thread:

  - lowest priority <br>&#x21d2; fallback thread when all other threads are blocked or terminated
  - switches the system to low-power mode

The ISR context handles external events and notifies threads using IPC messages

.center[
    <img src="images/riot-application.png" alt="" style="width:300px;"/>
]

---

## Hardware abstraction layer

- Divided in 3 blocks: boards, cpus, drivers

- CPUs are organized as follows:<br>
**architecture** (ARM) > **family** (stm32) > **type** (stm32l4) > **model** (stm32l476rg)

- Generic API for cpu peripherals (gpio, uart, spi, pwm, etc)

    &#x21d2; same API for all architectures

- Only based on vendor header files (CMSIS) &#x21d2; implementation from scratch

    &#x21d2; less code duplication, more efficient, more work

- One application &#x21d2; one board &#x21d2; one cpu model

.center[
    <img src="images/riot-architecture.png" alt="" style="width:300px;"/>
]

---

## Hardware support overview

- **Hardware abstraction layer:** support for 8/16/32 bit, ARM, AVR, MIPS

- Supported vendors: Microchip, NXP, STMicroelectronics, Nordic, TI, ESP, RISC-V, etc

- **Large list of sensors and actuators** supported (e.g drivers)

- _native_ board: **run RIOT as process on your computer**

- **+100 boards supported**

.center[
    <img src="images/riot-boards.png" alt="" style="width:620px;"/>
]

---

## A modular OS

Features are provided as modules &#x21d2; **only build what's required**

- System libraries: **xtimer**, **shell**, crypto, etc

--

- Sensors and actuators

- Display drivers, filesystems, etc

<img src="images/riot-ucglib.jpg" alt="" style="width:200px;position:fixed;right:100px;top:250px"/>

--

- Embedded interpretors: Javascript, LUA

--

- High-level network protocols: CoAP, MQTT-SN, etc

--

- External packages

.center[
<img src="images/packages.png" alt="" style="width:400px"/>
]

---

## Useful system libraries

- **xtimer**

  - high-level timer subsystem that provides full abstraction from the hardware timer

  - Can set callbacks, put a thread to sleep, etc

- **shell**

  - provides interactive command line interface

  - useful for interactive debugging or examples

- **Others:** crypto, fmt, math, etc

---

## External packages

- RIOT can be extended with external packages

- Integrated (and eventually patched) on-the-fly while building an application

- Easy to add: just requires 2 `Makefiles`

- Example of packages: lwIP, Openthread, u8g2, loramac, etc

<br><br>

.center[
    <img src="images/packages.png" alt="" style="width:400px;"/>
]

---

## Network stacks

**IP oriented stacks** &#x21d2; designed for Ethernet, WiFi, 802.15.4 networks

- **GNRC**: the in-house 802.15.4/6LowPAN/IPv6 stack of RIOT

--

- **Thread**: 802.15.4 IPv6 stack provided by the ThreadGroup

.center[
    <img src="images/openthread-logo.png" alt="" style="width:200px"/>
]

--

- **OpenWSN** (experimental): a deterministic MAC layer implementing the <br/>IEEE 802.15.4e TSCH protocol

.center[
    <img src="images/Openwsn_logo.png" alt="" style="width:100px"/>
]

--

- Other IPv6 stacks:

 - **lwIP**: full-featured network stack designed for low memory consumption

 - **emb6**: A fork of Contiki network stack that can be used without proto-threads

---

## Other network support

- In-house Controller Area Network (**CAN**)
<br><br>

--

- **BLE** stack support: <a href="https://github.com/apache/mynewt-nimble">NimBLE</a>
<img src="images/ble.png" alt="" style="width:180px;position:fixed;top:200px;right:200px"/>
<br><br>

--

- **LoRaWAN** stack
&#x21d2; Compliant with LoRaWAN 1.0.2
<img src="images/lorawan.png" alt="" style="width:200px;position:fixed;top:300px;right:200px"/>
<br><br>

--

- **SigFox** support for ATA8520e modules
<img src="images/sigfox.png" alt="" style="width:100px;position:fixed;top:400px;right:250px"/>

---

## Coming soon

- NB-IoT support

<img src="images/nb_iot_logo.jpg" alt="" style="width:180px;position:fixed;top:150px;right:400px"/>
<br><br>

--

- Full featured USB stack (CDC-ACM, CDC-ECM, etc)

<img src="images/usb-logo.png" alt="" style="width:180px;position:fixed;top:220px;right:400px"/>

<br><br>

--

- Standard and secure software update implementation

.center[https://datatracker.ietf.org/wg/suit/about/]

<br>

--

- And many other cool things !

---

class: center, middle

# RIOT in action

---

## IoT deployments using RIOT

.center[
    **Telefonica Chile: LoRa devices in a mine**<br><br>
    <img src="images/drop-watcher.png" alt="" style="width:630px"/><br/>
    <a href="http://riot-os.org/files/RIOT-Summit-2017-slides/6-2-Network-Session-DropWatcher.pdf">More information</a>
]

---

## IoT deployments using RIOT

.center[
**Almagro: Automatic cereal dispenser**<br><br>
<img src="images/almagro-feeder.png" alt="" style="width:200px"/><br/>
<a href="https://www.indiegogo.com/projects/the-venture-algramo-chile#/">More information</a>
]

---

## IoT deployments using RIOT

.center[
**Home automation using KNX**<br><br>
<img src="images/knx-element.png" alt="" style="width:400px"/><br>
<img src="images/knx-element2.png" alt="" style="width:200px"/>
<img src="images/knx-board.png" alt="" style="width:150px"/><br><br>
<a href="http://summit.riot-os.org/2018/wp-content/uploads/sites/10/2018/09/2_2-Bas-Stottelaar-KNX.pdf">More information</a>
]

---

## IoT products & services using RIOT

- Environment monitoring: Hamilton IoT (USA), Unwired Devices (Russia)

.center[
    <img src="images/hamilton-board.png" alt="" style="width:200px"/>
    <img src="images/unwired-one-fingers.jpg" alt="" style="width:200px"/>
]

- On-Board diagnostics for connected cars: OTAKeys (Continental)

- Design Office: Eistec (Sweeden), Mesotic (France)

---

## RIOT on FIT/IoT-LAB large scale testbed

.center[<a href=https://www.iot-lab.info>https://www.iot-lab.info</a><br><br>
IoT-LAB is a **large scale experimentation testbed**]

  - Can be used for **testing wireless communication** networks on **small devices**

  - Can be used for **learning** IoT programming and **communication protocols**

  - Can be used for testing software platforms on **heterogeneous hardware**

.center[
      <img src="images/iotlab-nodes.png" alt="" style="width:250px;"/>&nbsp;
      <img src="images/iotlab-sites.png" alt="" style="width:250px;"/>
  ]


---

## Learn RIOT

- RIOT Tutorials

.center[<a href="https://github.com/RIOT-OS/Tutorials">https://github.com/RIOT-OS/Tutorials</a>]

<br>

- RIOT online course

.center[<a href="https://github.com/aabadie/riot-course">https://github.com/aabadie/riot-course</a>]

<br>


---

















## The RIOT philosophy & community

- RIOT is free-software, licensed under LGPLv2.1

- The community takes inspiration from Linux

.right[
    <img src="images/linux.jpg" alt="" style="width:150px;margin-top:-100px"/>
]

- Use standards whenever possible <br>
  (C-ANSI, standard tools, standard protocols, standard procedures)

- Follow POSIX standards

- Avoid code duplication, easy to program, increase portability, modularity

- Vendor & Technology independence

- Decisions and orientations are taken by a grass-root community

.center[
    <img src="images/riot-contributors.png" alt="" style="width:350px"/>
]

---

## Who is using RIOT?

**Example IoT solutions deployments using RIOT**

- Telefonica: LoRa devices in a mine<br>
http://summit.riot-os.org/2017/blog/2017/10/06/slides/

- Almagro: Automatic cereal dispenser<br>
https://www.indiegogo.com/projects/the-venture-algramo-chile#/

- Fujitsu: IoT modules orchestration<br>
http://riot-os.org/files/RIOT-Summit-2017-slides/4-3-Virtualization-Session-Fujitsu.pdf

- Cisco, Huawei: experimental deployment using ICN-IoT

**Example IoT products & services using RIOT**

- Environment monitoring: Hamilton IoT (USA), Unwired Devices (Russia)

- On-Board diagnostics for connected cars: OTAKeys (Continental)

- Smart House, Smart City: Eistec (Sweeden), Mesotic (France)

- GPS tracking device with GSM modem: Sleeping Beauty (Germany)

---

class: center, middle

# Technical overview

<br/>
Long story short: paper in IEEE Internet of Things Journal<br/>
Preprint available: http://riot-os.org/files/2018-IEEE-IoT-Journal-RIOT-Paper.pdf

---

## OS characteristics

- Micro-kernel based architecture: modular approach

.center[
    <img src="images/riot-architecture.png" alt="" style="width:300px;"/>
]

- Multi-Threading and IPC:
  - Separate thread contexts with separate thread memory stack
  - Minimal thread control block (TCB)
  - Thread synchronization using mutexes, semaphores and messaging

- Real-Time scheduler
  - &#x21d2; fixed priorities preemption with O(1) operations
  - &#x21d2; tickless scheduler

- Small footprint &#x21d2; 2.8kB RAM, 3.2kB ROM on 32-bit Cortex-M

---

## Multi-Threading

2 threads by default:

- the `main` thread: running the `main` function

- the `idle` thread:

  - lowest priority <br>&#x21d2; fallback thread when all other threads are blocked or terminated
  - switches the system to low-power mode

The ISR context handles external events and notifies threads using IPC messages

.center[
    <img src="images/riot-application.png" alt="" style="width:300px;"/>
]

---

## Hardware support overview

- Support for 8/16/32 bit, ARM, AVR, MIPS

- `native` board: run RIOT as process on your computer

- Supported vendors: Microchip, NXP, STMicroelectronics, Nordic, TI, etc

- Large list of sensors and actuators supported (e.g drivers)

- Concept of "board" that simplify ports &#x21d2; +100 boards supported

<br><br>

.center[
    <img src="images/riot-boards.png" alt="" style="width:600px;"/>
]

---

## Hardware abstraction layer

- Divided in 3 blocks: boards, cpus, drivers

- CPUs are organized as follows:<br>
**architecture** (ARM) > **family** (stm32) > **type** (stm32l4) > **model** (stm32l476rg)

- Generic API for cpu peripherals (gpio, uart, spi, pwm, etc)

    &#x21d2; same API for all architectures

- Only based on vendor header files (CMSIS) &#x21d2; implementation from scratch

    &#x21d2; less code duplication, more efficient, more work

- One application &#x21d2; one board &#x21d2; one cpu model

.center[
    <img src="images/riot-architecture.png" alt="" style="width:300px;"/>
]

---

## High-level drivers

- Sensors and actuators

    &#x21d2; temperature, pressure, humidity, IMU, light sensors, radios, sd card, etc

- Memory Techonology Device (MTD) abstraction and filesystems

    &#x21d2; FatFS, LittleFS, SPIFFS

- Display drivers

    &#x21d2; u8g2, ucglib, HD44780

.center[
    <img src="images/riot-ucglib.jpg" alt="" style="width:200px;"/>
]

---

## Useful system libraries

- **xtimer**

  - high-level timer subsystem that provides full abstraction from the hardware timer

  - Can set callbacks, put a thread to sleep, etc

- **shell**

  - provides interactive command line interface

  - useful for interactive debugging or examples

- **Others:** crypto, fmt, math, etc

---

## Network stacks and protocols

3 types of network stacks:

- IP oriented stacks &#x21d2; designed for Ethernet, WiFi, 802.15.4 networks
  - **GNRC**: the in-house 802.15.4/6LowPAN/IPv6 stack of RIOT

  - **Thread**: another 802.15.4 IPv6 stack supported by NestLabs (Google)
.center[
    <img src="images/openthread-logo.png" alt="" style="width:200px;"/>
]
  - **lwIP**: full-featured network stack designed for low memory consumption

  - **emb6**: A fork of Contiki network stack that can be used without proto-threads

- In-house Controller Area Network (**CAN**)

- **LoRaWAN** stack: port of Semtech loramac-node reference implementation

.center[
    <img src="images/lorawan.png" alt="" style="width:200px;margin-top:-30px"/>
]

---

## External packages

- RIOT can be extended with external packages

- Integrated (and eventually patched) on-the-fly while building an application

- Easy to add: just requires 2 `Makefiles`

- Example of packages: lwIP, Openthread, u8g2, loramac, etc

<br><br>

.center[
    <img src="images/packages.png" alt="" style="width:400px;"/>
]

---

## Ecosystem & community processes

- Tooling and build system

      - hand crafted makefiles for building a RIOT application

  - On-Chip debugging with **OpenOCD** and **GDB**

- Distributed and fast CI, Murdock: https://ci.riot-os.org

    &#x21d2; Build all test/example applications for all targets<br><br>
    &#x21d2; Static tests (Cppcheck, Coccinelle, etc)<br><br>
    &#x21d2; Run on hardware (WIP)

- Online documentation generated with Doxygen

    &#x21d2; https://doc.riot-os.org

- In-depth code reviews

- One release every 3 month: **&lt;year&gt;.&lt;month&gt;** (ex: 2018.01, 2018.04, etc)

---

## Summary

- Generalities on RIOT: history, community, users

- A technical overview:

  - OS charactéristics

  - hardware support

  - libraries

  - network stack

  - import external libraries via packages

- The RIOT ecosystem:

  - standard tools

  - CI

  - documentation

  - releases

---

class: center, middle

[Back to the course](https://github.com/aabadie/riot-course#content-of-the-course)
