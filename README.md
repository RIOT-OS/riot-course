# Workshop workshop

## Access the slides

- Clone this repository:
```
git clone git@gitlab.inria.fr:aabadie/riot-workshop.git
```
- Slides are divided into section, open each section in a web browser:
  - 01-Introduction: `slides/01-introduction/introduction.html`
  - 02-Getting-Started: `slides/02-getting-started/getting-started.html`
  - 03-RIOT-Advanced: `slides/03-riot-basics/riot-basics.html`
  - 04-Networking-in-RIOT: `slides/04-networking-in-riot/networking-in-riot.html`
  - 05-LoRaWAN-with-RIOT: `slides/05-lorawan-with-riot/lorawan-with-riot.html`

----------------------------

**Agenda**

## Day 1

### Introduction

- General information

  - What is RIOT
  - A brief history of the project
  - RIOT's philosophy
  - RIOT, a community
  - Competitors
  - Who is using RIOT, for what

- Technical overview

  - OS characteristics
    - Microkernel architecture, RTOS, IPC, threads
    - external packages
    - High-level features: filesystems, displays
    - Network stacks and protocols

  - Hardware support overview
    - 8/16/32 bit, ARM, AVR, MIPS
    - and the other remarks you had about native, STM, Arduino...
    - Sensors and actuators
    - concept of "board" simplifying ports (reuse structure of RIOT paper section VI)?

  - Ecosystem & community processes
    - tooling & build system
    - CI
    - Code review
    - documentation online

### Getting started

- Setup your developement environment
- What is a RIOT application
- Building a RIOT application
  - Targets (BOARD)
  - Passing parameters (CFLAGS, etc)
  - verbose make
- Running the application
  - on native
  - on hardware
- Debugging an application
  - use GDB
  - special CFLAGS (DEBUG_ASSERT_VERBOSE)
- Adding extra modules to the application
  - USEMODULE, USEPKG, FEATURES_REQUIRED

### Going further with RIOT

- Source code organization
  - core: threads, ipc
  - sys: system modules, network modules, utilities (shell, xtimer, fmt, crypto, etc)
  - boards: configuration of supported boards
  - cpu: configuration of supported cpu, peripheral drivers implementations
  - drivers: generic peripheral drivers interfaces, external device drivers
  - pkg: external packages integration code
  - examples: sample application showcasing specific features
  - tests: test applications
  - dist: external scripts and tools (ci)
  - makefiles: make build system files

- The build system
  - Makefile.include
  - Makefile.base
  - Effects of modules inclusion to the code:
  - preprocessor macro `MODULE_XX`
  - what is built, `Makefile.base`

- Special things
  - The standard output
  - Using `DEBUG` macros

- The RIOT kernel

  - The boot sequence: `board_init()` => `cpu_init()` => `kernel_init()` => `main()`
  - `kernel_init()` => start idle and main threads, enable interrupts
  - Dealing with threads : `thread_create`, stacks, scheduler (priorities)
  - IPC: exchanging messages between threads

=> Exercise: threads creation and communication

- Main system modules

  - Managing delays with `xtimer`
  - Serial interaction with the `shell`

- Overview of the hardware abstraction layer APIs

  - Principle
  - GPIO
  - Timer
  - Serial buses: UART, I2C, SPI
  - PWM, ADC, DAC
  - RTC, RTT
  - Power management
  - Filesystem

=> Exercises: Playing with GPIOs, Reading values from the UART,
Communicating on SPI, I2C, RTC

- Drivers and SAUL

  - Overview of available drivers
  - SAUL + auto_init (drivers default configuration)
  - Integration and auto-configuration of on-board devices

=> Exercises: Read the HTS221 sensor values (using the driver API and
using SAUL ), Use the SX1276 driver API.

- Packages

  - Structure of a package
  - Integrating external packages
  - Using an external package

### Recap of the day

-------------------------------------

## Day 2

### Networking with RIOT

- Overview of networking technologies for IoT
  - Radio: 802.15.4, LoRa, SigFox, NB-IoT, 5G?
  - Network protocols: 6LowPAN/IPv6, LoRaWAN
  - Application protocols: MQTT, CoAP, LwM2M, etc
- The networking architecture of RIOT
- The GNRC stack
- Other available stacks
  - LwIP => provide IPv4, other protocols ?
  - OpenThread
  - CAN stack
  - LoRaWAN (Loramac-node)

### IPv6 communication on IoT-LAB

- Introduction to IoT-LAB
- Getting started with IoT-LAB: run an experiment, flash a firmware, etc
- Public IPv6 networking on IoT-LAB
- Using CoAP on an IPv6 network on IoT-LAB

### LoRaWAN communication with TheThingsNetwork

- Introduction to LoRaWAN with TheThingsNetwork
  - LoRaWAN overview
  - TheThingsNetwork overview
- Creating an account, setting up a LoRaWAN application with a device
- Using the RIOT test application
  - Join the network
  - Play with LoRaWAN parameters
  - Send and receive data
  - Use the MQTT API of TTN
- Writing an autonomous RIOT application
  - Use OTAA activation (some notes about ABP)
  - Use a dedicated sender thread
- Integrating a sensor (HTS221) to the application
- Triggering the send with an RTC alarm
- Adding low-power mode
