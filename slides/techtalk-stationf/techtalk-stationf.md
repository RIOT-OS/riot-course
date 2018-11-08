background-image: url(images/cover.png)

---

background-image: url(images/green-bands.png)

class: center, middle

<br><br><br><br>

<img src="images/riot-logo.png" alt="" style="width:200px;"/>

## An OS for Open Source IoT

### Inria Tech Talk

<br>

.right[.footer[
Alexandre Abadie<br>
Ingénieur de Recherche Inria<br>
Contributeur RIOT<br>
Team FIT/IoT-LAB]]

---

background-image: url(images/green-bands.png)

## What is RIOT

- **operating system** for microcontrollers

 - **microkernel architecture** &#x21d2; require very low resources
 - **real-time** and **multi-threaded**
 - comes with **in-house networking stacks**

<img src="images/microcontroller.jpeg" alt="" style="width:150px;position:fixed;top:160px;right:300px;"/>

--

<br>

- **open-source**: <a href="https://github.com/RIOT-OS/RIOT">https://github.com/RIOT-OS/RIOT</a>

 - free software platform
 - **world-wide community** of developers

<img src="images/gnu.png" alt="" style="width:100px;position:fixed;top:350px;right:320px;"/>

--

<br>

- **easy to use** and __reuse__

 - Standard programming in C
 - Standard tooling
 - **API is independent** of the hardware

<img src="images/finger-snap.png" alt="" style="width:100px;position:fixed;top:530px;right:320px;"/>

---

background-image: url(images/green-bands.png)

## RIOT in the IoT world

.center[<img src="images/iot-overview.png" alt="" style="width:600px;"/>
<br/><br/>
<br/><br/>
**&#x21d2; RIOT is designed for low-end devices (kB RAM, MHz, mW)**
]

---

background-image: url(images/green-bands.png)

## History of the project

- 2013: Inria, FU Berlin and HAW founded RIOT
 - stemed from a French-German research project
 - kernel evolved from FireKernel

<img src="images/logo-inria.png" alt="" style="width:150px;position:fixed;top:160px;right:400px;"/>
<img src="images/fu-berlin.jpeg" alt="" style="width:100px;position:fixed;top:150px;right:270px;"/>
<img src="images/haw-logo.png" alt="" style="width:150px;position:fixed;top:180px;right:90px;"/>

--

- The community today:

  - So far, 200 different contributors to the master branch
  - Academics: Berkeley, UCLA, MIT, AIT, TZI, etc
  - Industrial: Cisco, Samsung, ImgTec, Fujitsu, Thalès
  - SME: Zolertia, OTAKeys, Mesotic, Eistec, We-sens

--

- Annual RIOT Summit: https://summit.riot-os.org

<img src="images/riot-summit.png" alt="" style="width:250px;position:fixed;top:475px;right:650px;"/>
<img src="images/summit-2018.jpg" alt="" style="width:250px;position:fixed;top:475px;right:300px;"/>

---

background-image: url(images/green-bands.png)

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

 - provides more complete and stable OS functionalities

---

background-image: url(images/green-bands.png)

## The RIOT philosophy & community

- RIOT is free-software, licensed under LGPLv2.1

- The community takes inspiration from Linux

<img src="images/linux.jpg" alt="" style="width:150px;position:fixed;top:150px;right:300px;"/>

--

- Use standards whenever possible <br>
  (C-ANSI, standard tools, standard protocols, standard procedures)

- Follow POSIX standards

--

- Avoid code duplication, easy to program, increase portability, modularity

- Vendor & Technology independence

--

- Decisions and orientations are taken by a grass-root community

.center[
    <img src="images/riot-contributors.png" alt="" style="width:350px"/>
]

---

background-image: url(images/green-bands.png)

## Ecosystem & community processes

- Tooling and build system

  &#x21d2; **hand crafted makefiles** for building a RIOT application<br><br>
  &#x21d2; On-Chip debugging with **OpenOCD** and **GDB**<br>

<img src="images/gdb-logo.png" alt="" style="width:180px;position:fixed;right:350px;top:150px"/>

--

- Distributed and fast CI, Murdock: https://ci.riot-os.org

    &#x21d2; **Build and run** all test/example applications<br><br>
    &#x21d2; **Static tests** (Cppcheck, Coccinelle, etc)<br>

<img src="images/murdock.png" alt="" style="width:500px;position:fixed;right:100px;top:300px"/>

--

- **Online documentation** generated with Doxygen

    &#x21d2; https://doc.riot-os.org

--

- In-depth **code reviews**

- Stable **release every 3 months**: &lt;year&gt;.&lt;month&gt; (ex: 2018.07, 2018.10, etc)


---

class: center, middle
background-image: url(images/grey-bands.png)

# Technical overview

<br/>
Long story short: paper in IEEE Internet of Things Journal<br/>
Preprint available: http://riot-os.org/files/2018-IEEE-IoT-Journal-RIOT-Paper.pdf

---

background-image: url(images/green-bands.png)

## OS characteristics

- Micro-kernel based architecture: modular approach

<img src="images/riot-architecture.png" alt="" style="width:300px;position:fixed;right:120px;top:120px"/>

--

- Small footprint &#x21d2; 2.8kB RAM, 3.2kB ROM on 32-bit Cortex-M

--

- Real-Time scheduler
  - &#x21d2; fixed priorities preemption with O(1) operations
  - &#x21d2; tickless scheduler

--

- Multi-Threading and IPC:
  - Separate thread contexts with separate thread memory stack
  - Minimal thread control block (TCB)
  - Thread synchronization using mutexes, semaphores and messaging

<img src="images/riot-application.png" alt="" style="width:300px;position:fixed;right:120px;top:350px"/>

---

background-image: url(images/green-bands.png)

## Hardware support overview

- **Hardware abstraction layer:** support for 8/16/32 bit, ARM, AVR, MIPS

- Supported vendors: Microchip, NXP, STMicroelectronics, Nordic, TI, ESP, etc

- **Large list of sensors and actuators** supported (e.g drivers)

- _native_ board: **run RIOT as process on your computer**

- **+100 boards supported**

.center[
    <img src="images/riot-boards.png" alt="" style="width:620px;"/>
]

---

background-image: url(images/green-bands.png)

## A modular OS

Features are provided as modules &#x21d2; **only build what's required**

- System libraries: **xtimer**, **shell**, crypto, etc

<br>

--

- Sensors and actuators

<br>

- Display drivers, filesystems, etc

<img src="images/riot-ucglib.jpg" alt="" style="width:200px;position:fixed;right:200px;top:250px"/>

<br>

--

- Embedded interpretors: Javascript, LUA

<br>

--

- High-level network protocols: CoAP, MQTT-SN, etc

<img src="images/riot-802154-stack.png" alt="" style="width:150px;position:fixed;right:200px;top:500px"/>

---

background-image: url(images/green-bands.png)

## Network stacks

**IP oriented stacks** &#x21d2; designed for Ethernet, WiFi, 802.15.4 networks

- **GNRC**: the in-house 802.15.4/6LowPAN/IPv6 stack of RIOT

--

- **Thread**: 802.15.4 IPv6 stack provided by the ThreadGroup

<img src="images/openthread-logo.png" alt="" style="width:200px;position:fixed;top:250px;right:250px"/>

--

- **OpenWSN** (experimental): a deterministic MAC layer implementing the <br/>IEEE 802.15.4e TSCH protocol

<img src="images/Openwsn_logo.png" alt="" style="width:100px;position:fixed;top:300px;right:250px"/>

--

- Other IPv6 stacks:

 - **lwIP**: full-featured network stack designed for low memory consumption

 - **emb6**: A fork of Contiki network stack that can be used without proto-threads

---

background-image: url(images/green-bands.png)

## Other network support

- In-house Controller Area Network (**CAN**)
<br><br>

--

- **BLE** stack support: <a href="https://github.com/apache/mynewt-nimble">NimBLE</a>
<img src="images/ble.png" alt="" style="width:180px;position:fixed;top:200px;right:200px"/>
<br><br>

--

- **LoRaWAN** stack: port of <a href="">Semtech loramac-node</a> reference implementation<br>
&#x21d2; Compliant with LoRaWAN 1.0.2, considered stable
<img src="images/lorawan.png" alt="" style="width:200px;position:fixed;top:300px;right:200px"/>
<br><br>

--

- **SigFox** support for ATA8520e modules
<img src="images/sigfox.png" alt="" style="width:100px;position:fixed;top:400px;right:250px"/>

---

background-image: url(images/green-bands.png)

## External packages

- RIOT can be extended with external packages

- Integrated on-the-fly while building an application

- Easy to add: just requires 2 `Makefiles`

- Example of packages: Openthread, loramac, nimble, lwip, etc

<br><br>

.center[
    <img src="images/packages.png" alt="" style="width:400px;"/>
]

---

class: center, middle
background-image: url(images/grey-bands.png)

# RIOT in action

---

background-image: url(images/green-bands.png)

## Use RIOT for research

- Designed for easy integration of cutting edge technologies

--

- Community is close to IETF &#x21d2; **protocol standardisation**
<img src="images/ietf.png" alt="" style="width:100px;position:fixed;right:350px;top:200px"/>

--

- A platform with experimental networking technology <br>
&#x21d2; Cisco, Huawei: **deployment using ICN-IoT**

.center[<img src="images/icn_principle.png" alt="" style="width:600px"/>]

---

background-image: url(images/green-bands.png)

## Use RIOT for research

.center[**IoT modules orchestration** with Fujitsu <a href="https://www.runmyprocess.com">RunMyProcess</a>

<img src="images/runmyprocess.png" alt="" style="width:700px"/><br/>

<a href="http://riot-os.org/files/RIOT-Summit-2017-slides/4-3-Virtualization-Session-Fujitsu.pdf">More information</a>
]
---

background-image: url(images/green-bands.png)

## IoT deployments using RIOT

.center[
    **Telefonica Chile: LoRa devices in a mine**<br><br>
    <img src="images/drop-watcher.png" alt="" style="width:630px"/><br/>
    <a href="http://riot-os.org/files/RIOT-Summit-2017-slides/6-2-Network-Session-DropWatcher.pdf">More information</a>
]

---

background-image: url(images/green-bands.png)

## IoT deployments using RIOT

.center[
**Almagro: Automatic cereal dispenser**<br><br>
<img src="images/almagro-feeder.png" alt="" style="width:200px"/><br/>
<a href="https://www.indiegogo.com/projects/the-venture-algramo-chile#/">More information</a>
]

---

background-image: url(images/green-bands.png)

## IoT deployments using RIOT

.center[
**Home automation using KNX**<br><br>
<img src="images/knx-element.png" alt="" style="width:400px"/><br>
<img src="images/knx-element2.png" alt="" style="width:200px"/>
<img src="images/knx-board.png" alt="" style="width:150px"/><br><br>
<a href="http://summit.riot-os.org/2018/wp-content/uploads/sites/10/2018/09/2_2-Bas-Stottelaar-KNX.pdf">More information</a>
]

---

background-image: url(images/green-bands.png)

## IoT products & services using RIOT

- Environment monitoring: Hamilton IoT (USA), Unwired Devices (Russia)

.center[
    <img src="images/hamilton-board.png" alt="" style="width:200px"/>
    <img src="images/unwired-one-fingers.jpg" alt="" style="width:200px"/>
]

- On-Board diagnostics for connected cars: OTAKeys (Continental)

- Design Office: Eistec (Sweeden), Mesotic (France)

---

background-image: url(images/green-bands.png)

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

background-image: url(images/green-bands.png)

## RIOT on FIT/IoT-LAB large scale testbed

.center[
      <img src="images/use-iotlab.png" alt="" style="width:700px;"/>
  ]

---

## RIOT online demo

.center[<a href="http://riot-demo.inria.fr">http://riot-demo.inria.fr</a>]

<iframe src="http://riot-demo.inria.fr">

---

background-image: url(images/qa.png)

---

class: center, middle

<a href="https://aabadie.github.io/riot-course/slides/techtalk-stationf/#50">
https://aabadie.github.io/riot-course/slides/techtalk-stationf/#50</a>

---

background-image: url(images/green-bands.png)

## Getting started with RIOT

1. Learn how to write and build a RIOT application

  .center[
      <img src="images/riot-logo.png" alt="" style="width:100px;"/>
  ]

--

3. Learn the basics of LoRaWAN networks

  .center[
      <img src="images/lorawan.png" alt="" style="width:200px;"/>
  ]

--

4. Write a LoRaWAN application using RIOT and TheThingsNetwork provider

  .center[
      <img src="images/ttn-logo.png" alt="" style="height:100px;"/>
  ]

---

background-image: url(images/green-bands.png)

## Tutorial overview

- Use the preconfigured VM for building applications

- Hardware used:

  - [ST B-L072Z-LRWAN1](https://www.st.com/en/evaluation-tools/b-l072z-lrwan1.html): STM32L0 + LoRa radio

  .center[
      <img src="images/en.b-l072z-lrwan1.jpg" alt="" style="width:150px;"/>
  ]

  - [ST X-NUCLEO-IKS01A2](https://www.st.com/en/ecosystems/x-nucleo-iks01a2.html): extension shield with sensors

  .center[
      <img src="images/en.x-nucleo-iks01a2_image.jpg" alt="" style="width:100px;"/>
  ]

---

background-image: url(images/green-bands.png)

## About the VM

- Compatible with VirtualBox 5.2 or VMWare Player

--

- **Download it** from [here](http://demo-fit.saclay.inria.fr/vms/RIOT-LORA-VM.ova)
  and **import it** in VirtualBox/VMWare. Then **start it**.

--

- The full RIOT course is located in **~/riot-course**

  - A local clone of RIOT (master) is in **~/riot-course/RIOT**

  - Exercices are located in **~/riot-course/exercises**

--

- All required development tools are already installed:

  - The GNU ARM Embedded 7.3 toolchain is installed

  - The IoT-LAB cli-tools are installed

  - A list of common editors: Vim, Emacs, VSCode

---

background-image: url(images/green-bands.png)

## Let's go!

.center[
    Follow the <a href="https://aabadie.github.io/riot-course/slides/02-getting-started/#1">getting started slides</a>
]