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

- in `drivers`, `sys`, `pkg`
  - _Makefile.include_: add include specific directories to the build system

  - _Makefile.dep_: manage dependencies between modules

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

- Overview of the boot sequence:

.center[
    <img src="images/riot-boot.png" alt="" style="width:600px;"/>
]

- `board_init()` is implemented in `boards/<board name>/board.c` file

- `cpu_unit()` is implemented in `cpu/<cpu model>/cpu.c` file

- Example for for ARM Cortex-M:

 - the entry point is `reset_handler_default`

 - it is implemented in `cpu/cortexm_common/vectors_cortexm.c` file

---

## The RIOT kernel: the scheduler and the threads

- Tick-less scheduling policy (`O(1)`)

- Highest priority thread runs until finished or blocked:
  - 16 priority levels
  - the lower level the higher priority
  - Idle thread has priority 15
  - Main thread has priority 7

- ISR can preempt any thread at any time

- If all threads are blocked:
  - Switch to special IDLE thread
  - Goes into low-power mode

- A Thread is just a function with signature:
```c
void *thread_handler(void *arg);
```

- Threads manage their own memory stack

---

## The RIOT kernel: dealing with Threads

detail kernel_init() function

tickless scheduler

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

