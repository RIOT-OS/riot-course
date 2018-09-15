class: center, middle

# Getting started

---

class: center, middle

If you don't use the preconfigured VM or if not done already,<br><br>
please ensure you followed the
**[prerequisites](https://aabadie.github.io/riot-course/slides/prerequisites)**

<br><br><br><br>

.right[Otherwise move to next slide]

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

Let's build and run our first RIOT application with the exercise in
`~/riot-course/exercises/getting-started/first-app`.
Just follow the instruction of the
[exercise README](https://github.com/aabadie/riot-course-exercises/tree/master/getting-started/first-app)

```sh
$ cd ~/riot-course/exercises/getting-started/first-app
$ make
Building application "example" for "native" with MCU "native".

"make" -C /home/user/RIOT/boards/native
"make" -C /home/user/RIOT/boards/native/drivers
"make" -C /home/user/RIOT/core
"make" -C /home/user/RIOT/cpu/native
"make" -C /home/user/RIOT/cpu/native/periph
"make" -C /home/user/RIOT/cpu/native/vfs
"make" -C /home/user/RIOT/drivers
"make" -C /home/user/RIOT/drivers/periph_common
"make" -C /home/user/RIOT/sys
"make" -C /home/user/RIOT/sys/auto_init
 text   data  bss    dec    hex   filename
 20206  568   47652  68426  10b4a .../getting-started/first-app/bin/native/example.elf
```

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
$ USEMODULE=xtimer make BOARD=bl-072z-lrwan1
```

---

## Exercise: write an application with a shell

Go to `~/riot-course/exercises/getting-started/shell` and follow the
instructions in the following
[exercise README](https://github.com/aabadie/riot-course-exercises/tree/master/getting-started/shell)

---

## Interaction with the hardware

Interaction with the hardware can be performed at 3 levels:

- At board level by using predefined macros for controlling LEDs and buttons

  &#x21d2; just include `board.h` to use them

--

- At cpu level by using the MCU peripheral drivers APIs

  &#x21d2; periph_gpio periph_i2c periph_uart, etc

  This level is considered as the **HAL** of RIOT since it provides a common
  API for all types/architectures of CPU

--

- At driver level by using high level driver APIs for specific external
  sensors/actuators/radios

  &#x21d2; bmp180, hts221, sx1276, etc

---

## Exercise: interaction with the hardware

- Go to `~/riot-course/exercises/getting-started/led` and follow the
  instructions of the
  [led exercise README](https://github.com/aabadie/riot-course-exercises/tree/master/getting-started/led)
  to toggle LEDs from shell commands

- Go to `~/riot-course/exercises/getting-started/sensor` and follow the
  instructions of the
  [sensor exercise README](https://github.com/aabadie/riot-course-exercises/tree/master/getting-started/sensor)
  to read values from a sensor with shell commands

---

## Going further: read existing applications source code

The RIOT source directory contains applications that can be used as examples
for almost all features provided by RIOT.

- See applications in the `examples` directory

- Test applications in `tests` directory also provides good examples to start
  the RIOT

---

## Summary

- Build & run your first RIOT application, native and on hardware

- How to extend an application, the `shell`

- Basic interaction with the hardware

- Read sensor values

---

class: center, middle

[Back to the course](https://github.com/aabadie/riot-course#content-of-the-course)
