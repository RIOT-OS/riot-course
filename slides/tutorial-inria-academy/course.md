class: center, middle

## Microcontroller based IoT

# A hand-on course with RIOT

### Inria Academy

<br/><br/><br/>

.right[.footer[
  Alexandre Abadie - alexandre.abadie@inria.fr<br/>
  Francisco Molina - francois-xavier.molina@inria.fr
]]
---

## What is RIOT

<img src="images/riot-logo-circular.png" alt="" style="width:200px;position:fixed;right:20px;top:70px"/>

- **operating system** for microcontrollers

 - **microkernel architecture** &#x21d2; require very low resources
 - **real-time** and **multi-threaded**
 - comes with **in-house networking stacks**
<br><br>

- **open-source**: <a href="https://github.com/RIOT-OS/RIOT">https://github.com/RIOT-OS/RIOT</a>

 - free software platform
 - **world-wide community** of developers

<img src="images/github-logo.png" alt="" style="width:150px;position:fixed;right:80px;top:300px"/>
<br>

- **easy to use** and __reuse__

 - Standard programming in C
 - Standard tooling
 - **API is independent** from the hardware

<img src="images/c-logo.png" alt="" style="width:120px;position:fixed;right:70px;top:420px"/>
<img src="images/gnu.png" alt="" style="width:100px;position:fixed;right:200px;top:460px"/>
<img src="images/linux.jpg" alt="" style="width:120px;position:fixed;right:20px;top:520px"/>

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

  - So far, **+250** different contributors to the master branch
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

- Stable **release every 3 months**: &lt;year&gt;.&lt;month&gt; (ex: 2020.04, 2020.07, etc)


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

- **~200 boards supported**

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

- Embedded interpretors: Javascript, Micropython, LUA

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

- Example of packages: lwIP, Openthread, lvgl, loramac, etc

<br><br>

.center[
    <img src="images/packages.png" alt="" style="width:400px;"/>
]

---

## Network stacks

**IP oriented stacks** &#x21d2; designed for Ethernet, WiFi, 802.15.4 networks

- **GNRC**: the in-house 802.15.4/6LowPAN/IPv6 stack of RIOT

--

- **lwIP**: full-featured network stack designed for low memory consumption

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

---

## Other network support

- In-house Controller Area Network (**CAN**)
<br><br>

--

- **BLE** stack support: <a href="https://github.com/apache/mynewt-nimble">NimBLE</a>
<img src="images/ble.png" alt="" style="width:180px;position:fixed;top:150px;right:100px"/>
<br><br>

--

- **LoRaWAN** stack
&#x21d2; Compliant with LoRaWAN 1.0.2
<img src="images/lorawan.png" alt="" style="width:200px;position:fixed;top:235px;right:100px"/>
<br><br>

--

- **SigFox** support for ATA8520e modules
<img src="images/sigfox.png" alt="" style="width:100px;position:fixed;top:300px;right:125px"/>

---

## Other important features

- Full featured USB stack (CDC-ACM, CDC-ECM, etc)

<img src="images/usb-logo.png" alt="" style="width:180px;position:fixed;top:80px;right:100px"/>

<br><br>

--

- Standard and secure software update implementation

.center[https://datatracker.ietf.org/wg/suit/about/]

<br>

--

## Coming soon

- NB-IoT support

<img src="images/nb_iot_logo.jpg" alt="" style="width:180px;position:fixed;top:450px;right:100px"/>
<br>

- Simplified configuration with Kconfig

<img src="images/kconfig.jpeg" alt="" style="width:180px;position:fixed;top:525px;right:100px"/>

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
**Algramo: Automatic cereal dispenser**<br><br>
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

.center[<a href="https://github.com/riot-os/riot-course">https://github.com/riot-os/riot-course</a>]

<br>

- MOOC

.center[<a href="https://www.fun-mooc.fr/courses/course-v1:inria+41020+session01/about">MOOC "Internet of Things on microcontrollers: a hands-on course"</a>]

---

class: center, middle

# Hands-on time!

---

## Tutorial Tooling (1)

1. Embedded software: we use the RIOT code base + ecosystem

--

2. Embedded hardware: we use the open-access testbed IoT-LAB to run RIOT code remotely on micro-controllers

.center[
    <img src="images/tutorial-summary.png" alt="" style="width:720px;"/>
]

---

## Tutorial Tooling (2)

- No setup required, all activities are performed online in Jupyter Notebooks

.center[
    <img src="images/jupyter.png" alt="" style="width:75px;"/>
]

- Run the RIOT applications on the [IoT-LAB](https://www.iot-lab.info) testbed

- Use [IoT-LAB M3](https://www.iot-lab.info/docs/boards/iot-lab-m3/) boards:

<br/>
.center[
    <img src="images/iotlab-m3.png" alt="" style="width:300px;"/>
]

---

## About the Jupyter Notebooks

.center[
Available at **https://labs.iot-lab.info**

<img src="images/iotlab-jupyterhub.png" alt="" style="width:300px;"/>

**Short demo: discover Jupyterlab notebooks!**
<form class=notebook>
    <input class=login id="login_start" type="text" oninput="check_login('login_start', 'launcher_start')" placeholder="Enter your IoT-LAB login">
    <input class=launcher id="launcher_start" type="button" value="Launch notebook" onclick="open_notebook('login_start', 'start.ipynb')" disabled>
</form>
]

---

class: center, middle

## Getting started

---

## Structure of a RIOT application

A minimal RIOT application consists in:

- A `Makefile`

```mk
APPLICATION = example

BOARD ?= native

RIOTBASE ?= $(CURDIR)/../../../RIOT

DEVELHELP ?= 1

include $(RIOTBASE)/Makefile.include
```

- A C-file containing the main function

```c
#include <stdio.h>

int main(void)
{
    puts("My first RIOT application");
    return 0;
}
```

---

## Build a RIOT application

- The build system of RIOT is based on **make** build tool

--

- To build an application, **make** can be called in 2 ways:

  - From the application directory:
  ```sh
  $ cd <application_directory>
  $ make
  ```

  - From anywhere, by using the `-C` to specify the application directory:
  ```sh
  $ make -C <application_directory>
  ```

--

- Use the **BOARD** variable to specify the target at build time
```sh
$ make BOARD=<target> -C <application_directory>
```
`BOARD` can be any board supported by RIOT<br>
&#x21d2; see the **RIOT/boards** directory for the complete list

--

- Use the **RIOTBASE** variable to specify the RIOT source base directory

---

## Run a RIOT application

This depends on the target board:

- Running on **native**: the RIOT application executed is a simple Linux process
```sh
$ make BOARD=native -C <application_dir>
$ <application_dir>/bin/native/application.elf
```

- Running on **hardware**: the RIOT application must be *flashed* first on the
  board

--

&#x21d2; use the **flash** and **term** targets with make
  - **flash**: build and write the firmware on the MCU flash memory

  - **term**: opens a terminal client connected to the serial port of the
    target

All this can be done in one command:

```sh
$ make BOARD=<target> -C <application_dir> flash term
```

*Note:* the last command can also be used with **native** target

---

## Exercise: your first RIOT application

Let's build and run our first RIOT application !<br><br>

In jupyterlab, open the notebook **riot/basics/hello-world/hello-world.ipynb**
and follow the instructions.

.center[
<form class=notebook>
    <input class=login id="login_hello" type="text" oninput="check_login('login_hello', 'launcher_hello')" placeholder="Enter your IoT-LAB login">
    <input class=launcher id="launcher_hello" type="button" value="Launch notebook" onclick="open_notebook('login_hello', 'riot/basics/hello-world/hello-world.ipynb')" disabled>
</form>
]

---

## How to extend the application

&#x21d2; by adding modules in the application `Makefile` or from the command line:

- Add extra modules with **USEMODULE**<br>
    &#x21d2; `xtimer`, `fmt`, `shell`, `ps`, etc

- Include external packages with **USEPKG**<br>
    &#x21d2; `lwip`, `semtech-loramac`, etc

- Use MCU peripherals drivers with **FEATURES_REQUIRED**:<br>
    &#x21d2; `periph_gpio`, `periph_uart`, `periph_spi`, `periph_i2c`

--

Example in a `Makefile`:
```mk
USEMODULE += xtimer shell

USEPKG += semtech-loramac

FEATURES_REQUIRED += periph_gpio
```
Example from the command line:
```sh
$ USEMODULE=xtimer make BOARD=b-l072z-lrwan1
```

---

## Exercise: write an application with a shell

Follow the instructions in the notebook **riot/basics/shell/shell.ipynb**

.center[
<form class=notebook>
    <input class=login id="login_shell" type="text" oninput="check_login('login_shell', 'launcher_shell')" placeholder="Enter your IoT-LAB login">
    <input class=launcher id="launcher_shell" type="button" value="Launch notebook" onclick="open_notebook('login_shell', 'riot/basics/shell/shell.ipynb')" disabled>
</form>
]


---

## Exercise: read sensor data

Follow the instructions in the notebook **riot/basics/sensors/sensors.ipynb**

.center[
<form class=notebook>
    <input class=login id="login_sensors" type="text" oninput="check_login('login_sensors', 'launcher_sensors')" placeholder="Enter your IoT-LAB login">
    <input class=launcher id="launcher_sensors" type="button" value="Launch notebook" onclick="open_notebook('login_sensors', 'riot/basics/sensors/sensors.ipynb')" disabled>
</form>
]

---

class: center, middle

## All complete ? Well done!
