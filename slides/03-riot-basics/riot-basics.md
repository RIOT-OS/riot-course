class: center, middle

# RIOT basics

---

## Source code organization

- **boards:** board specific definitions, cpu model, clock, peripherals
   config, documentation, serial and flasher config (dist)

- **core:** kernel initialization, thread, ipc

- **cpu:**  support for microcontroller (cmsis, definitions, peripheral
  drivers), entry point (_reset\_handler\_default_)

- **dist:** management and utility tools (script, ci, static checkers, etc)

- **doc:** doxygen documentation

- **drivers:** high-level device drivers (sensors, actuators, radios), HAL API

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

  - use `<table>` (autocompletion) to get the full list

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

- `kernel_init()` is implemented in `core/kernel_init.c` file

- Example for ARM Cortex-M:

 - the entry point is `reset_handler_default`

 - implemented in `cpu/cortexm_common/vectors_cortexm.c` file

---

## The scheduler and the threads

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

## Dealing with Threads

- Threads are created using the `thread_create()` function from `thread.h`:
```c
kernel_pid_t pid;
pid = thread_create(stack,  /* stack array pointer */
                        sizeof(stack), /* stack size */
                        THREAD_PRIORITY_MAIN - 1, /* thread priority*/
                        flag, /* thread configuration flag, usually*/
                        thread_handler, /* thread handler function */
                        NULL, /* argument of thread_handler function*/
                        "thread name");
```
- By default, the thread starts immediately

- `stack` is a global static byte array:
```c
static char stack[THREAD_STACKSIZE_MAIN];
```

- Priority is higher than `main` thread

--

<br>

.center[&#x21d2; more usage in `tests/thread_*` test applications]

---

## Thread: practice

- **Exercise:** `~/riot-workshop-samples/riot-advanced/first-thread`

- **Board:** native

- In your application add a thread that prints "Hello from thread"<br><br>
_Reminder:_
```c
#include "thread.h"
static char stack[THREAD_STACKSIZE_MAIN];
void *thread_handler(void *arg)
{
        /* thread code */
        return NULL;
}
kernel_pid_t pid = thread_create(stack,
                                     sizeof(stack),
                                     THREAD_PRIORITY_MAIN - 1,
                                     0,
                                     thread_handler,
                                     NULL,
                                     "thread name");
```

- Verify the message is displayed on your input (use native and the board)

---

## Thread: practice

- Add `shell` and `ps` modules to your application

- Rebuild, restart and run `ps` command

- Display the list of threads. Comments?

--

.right[
    &#x21d2; The thread has already returned!
]

--

- Now add an infinite loop before the return:

```c
while (1) {}
```
- Reboot and run `ps` again. Comments ?

--

.right[
    &#x21d2; Your thread has a higher priority, so the shell never starts!
]

--

- Set a lowest priority to the `thread` (e.g. higher value)

- Test your final application on the ST `b-l072z-lrwan1` board

---

## Managing thread concurrency

- Threads have their own stack

- But threads can also access to the globally shared memory of the application

    &#x21d2; need for protection and synchronization mechanisms

- RIOT provides:

  - Mutexes in `mutex.h`:
```c
mutex_t lock;
mutex_lock(&lock);
mutex_unlock(&lock);
```

  - Semaphores in `sema.h` (also POSIX semaphores in `semaphores.h`)

--

<br>

.center[&#x21d2; More usage examples in `tests/mutex_*` test applications]

---

## IPC

- IPC messages can be exchanged between threads or between ISR and threads

- IPC are **synchronous** by default or **asynchronous**

- The messaging API is defined in `msg.h` (in `core`):
  - The message type is:
  - A message have a `type` and a `content`

```c
msg_t msg;
msg.type = MSG_TYPE;
msg.content.value = 42; /* content can be a value */
msg.content.ptr = array; /* or content can be a pointer */
```
  - Sending a message:

```c
msg_send(&msg, pid); /* block except when called from an interrupt */
msg_try_send(&msg, pid); /* non blocking send */
msg_send_receive(&msg, &msg_reply, pid); /* block until a reply is received */
msg_reply(&msg, &msg_reply); /* reply to a message */
```

---

## IPC

- Receiving messages:

```c
msg_receive(&msg); /* block until a message is received */
msg_try_receive(&msg); /* try to receive a message without blocking */
```

- Typical use case: a listener thread waiting for messages coming from ISR

```c
void *thread_handler(void *arg)
{
    /* endless loop */
    while (1) {
        msg_t msg;
        msg_receive(&msg);
        printf("Message received: %s\n", (char *)msg.content.ptr);
    }
    return NULL;
}
```

- With asynchronous messaging always initialize a thread message queue in the thread handler:

```c
msg_t msg_queue[8];
msg_init_queue(msg_queue, 8);
```

---

## IPC: practice

- **Exercise:** `~/riot-workshop-samples/riot-advanced/thread-ipc`

- **Board:** native and `b-l072z-lrwan1` board

- **Objective:**

  - Write a shell command that sends a string to a thread

  - The receiver thread prints each received message

- **Going further:** `~/riot-workshop-samples/riot-advanced/thread-safe-ipc`:

  - Modify a global static buffer and send a message to the receiver thread

  - Ensure thread safety using a mutex. You will have to define a struct:

  ```c
typedef struct {
        char data[BUFFER_SIZE];
        mutex_t lock;
} data_buffer_t;
  ```

  - Ensure thread safety using a blocking message exchange (use `msg_send_receive`, the previous struct is not needed)

---

## Timers

- High level timer provided by module `xtimer`

- `xtimer` multiplex hardware timers

- microseconds accuracy

- Simple API:

  - get current system time in microseconds
```c
xtimer_ticks32_t now = xtimer_now();
```

  - add a `sec` seconds delay
```c
xtimer_sleep(sec);

  - add a `microsec` mircroseconds delay
```c
xtimer_usleep(microsec);
```

- helper defines from `timex.h` to convert seconds to us, ms to us, etc:
```c
US_PER_SEC  /* number of microseconds per seconds */
US_PER_MS   /* number of milliseconds per seconds */
```

---

## Timers: practice

**Exercise:** `~/riot-workshop-samples/riot-advanced/timers`

- **Board:** ST `b-l072z-lrwan1` board

Reminder:
  - Use `LEDx_TOGGLE` macros from `board.h` to toggle the LEDs.
  - The ST board has 3 LEDs (LED1, LED2 and LED3)

**Objective:**

- Write an application with 3 extra threads:

  - add the module `xtimer` in the application `Makefile`

  - _thread\_1_ toggles the LED1 every half seconds

  - _thread\_2_ toggles the LED2 every seconds

  - _thread\_3_ prints the system time every 2 seconds

---

## Power management

**Principle:** <br>
> _when all threads are blocked/terminated, the scheduler switches to the_
> _idle thread._<br>
> _The idle thread then goes to lowest possible power mode._

<table>
<tr>
  <td>
  <ul>
  <li>the desired low-power mode must be unblocked<br><br></li>
  <li>the lowest possible power mode is selected ("Cascade")<br><br></li>
  <li>API is defined in system `pm_layered` module</li>
  </ul>
  </td>
  <td>
.center[
    <img src="images/riot-application.png" alt="" style="width:250px;"/>
]
</td>
</tr>
</table>

**Important:**
- The board MCU must import the `pm_layered` module
- Still WIP, the design is subject to change in the future


---

## The hardware abstraction layer

Organization: boards, cpus peripherals

APIs

---

## Boards abstraction layer

---

## Drivers and SAUL

- "SAUL" : Sensor Actuator Uber Layer

---

## Auto initialization

---

## Packages

