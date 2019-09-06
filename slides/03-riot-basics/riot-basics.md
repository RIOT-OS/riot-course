class: center, middle

# RIOT basics

---

## System overview

.center[
    <img src="images/riot-apis.png" alt="" style="width:500px;"/>
]

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

  - use `<tab>` (autocompletion) to get the full list

- For every module **_xx_** imported, a **MODULE_XX** macro is created:
```c
#ifdef MODULE_XX
/* conditional code when module XX is loaded */
#endif
```
&#x21d2; very useful to optimize code size

---

## The build system: debugging an application

- Use **debug** target. For example with OpenOCD:

  - Starts a GDB server

  - Starts the GDB client, connects to the GDB server and loads the application<br><br>
    &#x21d2; Ready to debug

- **DEVELHELP:** variable that enables safety checks (assert, get thread names, etc)

- Useful `CFLAGS` options:<br>

  - -DLOG_LEVEL=LOG_DEBUG : enable debug output globally

  - -DDEBUG_ASSERT_VERBOSE : catch `FAILED ASSERTION` errors and give the file
    and line number

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
  - Goes into lowest power possible mode

- A thread is just a function with signature:
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

- Useful: `thread_getpid()` return the current thread pid

--

.center[&#x21d2; more usage examples in `tests/thread_*` test applications]

---

## Exercise: Thread

Follow the instructions of the
[first thread exercise README](https://github.com/riot-os/riot-course/tree/master/exercises/riot-basics/first-thread)

---

## Managing thread concurrency

- Threads have their own stack

- But threads can also access the global shared memory of the application

    &#x21d2; protection and synchronization mechanisms are required

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

## Exercise: Thread concurrency

Follow the instructions of the
[thread concurrency exercise README](https://github.com/riot-os/riot-course/tree/master/exercises/riot-basics/thread-concurrency)

---

## IPC

- IPC messages can be exchanged between threads or between ISR and threads

- IPC are **synchronous** by default or **asynchronous**

- The messaging API is defined in `msg.h` (in `core`):
  - The message type is `msg_t`
  - Each message has a `type` and a `content`

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

- Typical use case: a thread waiting for messages from another thread or ISR

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

- When using asynchronous messaging (typically the case with ISR), always
  initialize a thread message queue in the thread handler:

```c
msg_t msg_queue[8];
msg_init_queue(msg_queue, 8);
```

---

## Exercise: IPC

Follow the instructions of the
[thread IPC exercise README](https://github.com/riot-os/riot-course/tree/master/exercises/riot-basics/thread-ipc)

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
      <li>API is defined in `pm_layered.h` from system `pm_layered` module</li>
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

## Timers

- High level timer provided by module `xtimer`

- `xtimer` multiplexes hardware timers

- microseconds accuracy

- Simple API:

  - get current system time in microseconds

```c
xtimer_ticks32_t now = xtimer_now();
```

  - add a `sec` seconds delay

```c
xtimer_sleep(sec);
```

  - add a `microsec` mircroseconds delay

```c
xtimer_usleep(microsec);
```

---

## Timers (continued)

- Use xtimer for periodic wakeups:

```c
void xtimer_periodic_wakeup(xtimer_ticks32_t *last_wakeup, uint32_t period);
```

  - Use an `xtimer_t` variable to send a message at a given time:

```c
void xtimer_set_msg(xtimer_t *timer, uint32_t offset, msg_t *msg,
                    kernel_pid_t target_pid);
```

  - Use an `xtimer_t` variable to trigger a callback function at a given time:

```c
xtimer_set(xtimer_t *timer, uint32_t offset);
```

- helper defines are also provided by `timex.h` to convert seconds to us, ms to us, etc:
```c
US_PER_SEC  /* number of microseconds per seconds */
US_PER_MS   /* number of milliseconds per seconds */
```

---

## Exercise: Timers

Follow the instructions of the
[timers exercise README](https://github.com/riot-os/riot-course/tree/master/exercises/riot-basics/timers)

---

## The hardware abstraction layer

- Hardware abstraction layer relies on 3 blocks: **cpus**, **boards** and **drivers**

.center[
    <img src="images/riot-architecture.png" alt="" style="width:400px;"/>
]

- Reflects IoT devices targeted by RIOT<br><br>
    &#x21d2; a microcontroller with devices connected together on a board

- One application is built for one board with one cpu and with potentially multiple devices (sensors, actuators, radios)

---

## CPU abstraction

CPUs classification follows a hierarchical approach:

- **architecture** e.g ARM, AVR

- **family** e.g stm32, sam

- **type** e.g stm32l0, stm32l1, sam0, sam3

- **model** e.g stm32l072cz, samd21g18a

<table>
<tr>
  <td>
    <ul>
      <li>This organisation is not mandatory<br><br></li>
      <li>`native` port is provided in a single module<br><br></li>
    </ul>
  </td>
  <td>
.center[
    <img src="images/riot-cpus.png" alt="" style="width:400px;"/>
]
  </td>
</tr>
</table>

---

## Board abstraction

- Each directory in `boards` creates a board module<br>
  &#x21d2; `BOARD=<board module name>`

- MCU family and model used are defined in `Makefile.include`

- The list of features provided (e.g MCU peripheral) is defined in `Makefile.features`

- The configurations of MCU clocks and peripherals are defined in `periph_conf.h`

- `board.h` provides specific on-board defines for:

  - Configurations for the `xtimer` module

  - on-board LEDs and buttons pins

  - on-board high-level device drivers (sensor, actuators, radios)

---

## MCU peripherals APIs

- Uniform APIs built on top of heterogeneous hardware

- The same code can run potentially on every hardware

- APIs are defined in `drivers/include/periph` and implemented in each cpus `periph` subdirectory

- Explicitly include a peripheral module in your Makefile with the **FEATURES_REQUIRED** variable

- The peripheral drivers are implemented from scratch. This guarantees:

  - Memory efficiency

  - Less code duplication

  - Vendor independent implementations

- See `tests/periph_*` application for usage examples

- See APIs documentation: http://doc.riot-os.org/group__drivers__periph.html

---

## GPIO peripheral API

- Module name is **periph_gpio**, include from **periph/gpio.h**

- use GPIO_PIN(PORT, PIN) macro to get a gpio pin from port/pin

- all GPIO usual mode could be used, but this depends on the hardware behind

- Interrupt management is enabled with **periph_gpio_irq** module

- Use a `gpio_init_int()` to configure a gpio as external interrupt:

```c
static void gpio_cb(void *arg)
{
    (void) arg;
    /* manage interrupt */
}

int main()
{
    gpio_init_int(GPIO_PIN(PA, 0), GPIO_IN, GPIO_RISING, gpio_cb, NULL);
}
```

---

## Exercise: GPIO

Follow the instructions of the
[gpio exercise README](https://github.com/riot-os/riot-course/tree/master/exercises/riot-basics/gpio)

---

## UART peripheral API

- Allows to send and receive messages asynchronously from an UART

- Module name is **periph_uart**, include from **periph/uart.h**

- UART peripheral triggers an interrupt on each character received

```c
static void uart_cb(void *arg, uint8_t data)
{
    (void) arg;
    /* manage interrupt */
}

int main()
{
    uart_init(UART_DEV(0), BAUDRATE, uart_cb, NULL);
}
```

---

## Exercise: UART

Follow the instructions of the
[uart exercise README](https://github.com/riot-os/riot-course/tree/master/exercises/riot-basics/uart)

---

## Peripheral APIs: RTC

- Provide an accurate and low power access to timings

- Still running even when the CPU is in low-power/deep-sleep mode

- Use standard lib `tm` struct from `time.h`

- Simple API:

```c
/* Set current time of the RTC */
rtc_set_time(struct tm *time);

/* Get current time */
rtc_get_time(struct tm *time);
```

- Can be used to configure an alarm:

```c
static void rtc_alarm_cb(void *)
{
    /* manage the alarm */
}

[...]
struct tm alarm_time;
rtc_set_alarm(&alarm_time, rtc_alarm_cb, NULL);
```

---

## Exercise: RTC

Follow the instructions of the
[rtc exercise README](https://github.com/riot-os/riot-course/tree/master/exercises/riot-basics/rtc)

---

## Other peripheral drivers available

- **Timer**: module `periph_timer`, include from `periph/timer.h`

- **I2C**: module `periph_i2c`, include from `periph/i2c.h`

- **SPI**: module `periph_spi`, include from `periph/spi.h`

- **PWM**: module `periph_pwm`, include from `periph/pwm.h`

- **ADC**: module `periph_adc`, include from `periph/adc.h`

- **DAC**: module `periph_dac`, include from `periph/dac.h`

- **RTT**: real-time ticker, include from `periph/rtt.h`

.center[etc]

--

&#x21d2; good example applications provided in `tests/periph_*`

---

## High-level drivers

.center[
    <img src="images/riot-architecture.png" alt="" style="width:400px;"/>
]

- Built on top of peripheral APIs &#x21d2; ensures portability

- Current design allows multiple drivers of the same type to be used:<br>

  &#x21d2; Concept of **device descriptors** containing runtime state

- Drivers are defined in `drivers/include/<driver name>` and implemented in `drivers/<driver name>`

- **SAUL** (Sensor Actuator Uber Layer) &#x21d2; high level abstraction built on top of the drivers

---

## High-level drivers: initialization

- Drivers implementations provide default initialization parameters in `drivers/<driver name>/include/<driver name>_params.h`

- Default params can be overridden:

  - in application code: add your own `<driver name>_params.h` there

  - board configuration `board.h`: predefine required macros

- A typical driver `driver_name` initialization is:

```c
#include "driver_name.h"
#include "driver_name_params.h"

static driver_name_t dev;

[...]

/* in main */
driver_name_init(&dev, &driver_name_params[0]);
```

---

## Exercise: Use High-level drivers

Follow the instructions of the
[drivers exercise README](https://github.com/riot-os/riot-course/tree/master/exercises/riot-basics/drivers)

---

## Packages

**Principle:** Integrate an external library from source to the final built firmware

**Workflow:**

1. Fetch the source either from local or using `git`

2. Patch the source (optional)

3. Copied the RIOT makefile to the fetched sources: creates one (or more) module

**Simple to add:**

- Packages are downloaded in the application `bin` directory

- Only 3 files are required at minimum:

  - `Makefile` defines the url, version and commands to build the package
  - `Makefile.include` defines the inclusion directory
  - `Makefile.<package_name>` the RIOT makefile copied to the fetched sources

---

## Summary

- Organization of the code

- The build system

- The RIOT kernel: boot sequence, threads, IPC

- Timers

- Power management

- The hardware abstraction layer: board, cpu peripherals

- Drivers

- Packages

---

class: center, middle

[Back to the course](https://github.com/riot-os/riot-course#content-of-the-course)
