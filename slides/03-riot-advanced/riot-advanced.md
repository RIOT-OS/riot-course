class: center, middle

# RIOT advanced

---

## Source code organization

- **boards:** board specific definitions, cpu model, clock, peripherals
   config, documentation, serial and flasher config (dist)

- **core:** kernel initialization, thread, ipc

- **cpu:**  support for microcontroller (cmsis, definitions, peripheral
  drivers), entry point (_reset\_handler\_default_)

- **dist:** management and utility tools (script, ci, static checkers, etc)

- **doc:** doxygen documentation

- **drivers:** high-level devices drivers (sensors, actuators, radios), HAL API

- **examples:** sample applications

- **makefiles:** build and management system makefiles

- **pkg:** external packages

- **sys:** system libraries, network, shell, xtimer, etc

- **tests:** unittests, test applications (can be used as examples)

---

## The build system

- A set of hand crafted `Makefiles` &#x21d2; more control

- Run **make** from the application directory:
```
$ cd <application_dir> && make all
$ make -C <application_dir> all
```

- _RIOTBASE_ variable points to the RIOT source code

- _$(RIOTBASE)/Makefile.include_ defines all targets

- Modules:
  - `module name = directory basename`
  - simply include _$(RIOTBASE)Makefile.base_ in the module _Makefile_
  - all `.c` are added to the module

- in drivers/sys/pkg
  - _Makefile.include_ add include specific directories to the build system
  - _Makefile.dep_ manage dependencies between modules

---

## The build system

- High-level useful targets (besides _all_, _flash_, _term_, _debug_):

  - **info-build:** give useful information about the build (board supported, cpu, modules included, etc)

  - **flash-only:** don't rebuild before flashing (_flash_ depends on _all_)

  - **list-ttys:** return the list of serial ports available with information on the board connected (useful when working with multiple boards)

  - use `<tab>` (autocompletion) to get the full list

- For every module `xx` imported, a **MODULE_XX** macro is created:
```c
#ifdef MODULE_XX
/* conditional code when module XX is loaded */
#endif
```
&#x21d2; very useful to optimize code size

---

## The RIOT kernel

boot sequence

detail kernel_init() function

tickless scheduler

---

## The RIOT kernel: dealing with Threads

thread_create, stack

---

## The RIOT kernel: exchanging messages

messages queue, send receive message

---

## Power management

The principle

Available APIs

---

## Main system modules

xtimer

shell

auto_init

---

## The hardware abstraction layer

---

## Drivers and SAUL

- "SAUL" : Sensor Actuator Uber Layer

---

## Packages

