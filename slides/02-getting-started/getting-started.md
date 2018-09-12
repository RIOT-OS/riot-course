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

Let's build and run our first RIOT application with this
[exercise](https://github.com/aabadie/riot-exercices/getting-started/first-app)

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

In the `Makefile` or from the command line:

- Add extra modules with **USEMODULE**<br>
    &#x21d2; `xtimer`, `fmt`, `shell`, `ps`, etc

- Include packages with **USEPKG**<br>
    &#x21d2; `lwip`, `semtech-loramac`, etc

- Use MCU peripherals with **FEATURES_REQUIRED**:<br>
    &#x21d2; `periph_gpio`, `periph_uart`, `periph_spi`, `periph_i2c`

Example:
```mk
USEMODULE += xtimer shell

USEPKG += semtech-loramac

FEATURES_REQUIRED += periph_gpio
```

---

## Exercise: writing an application with a shell

Go into the `getting-started/shell-app` application directory:

- Add the **shell** module to the `Makefile`

```mk
USEMODULE += shell
```

- Modify the `main.c`:

```c
#include "shell.h"
```

```c
/* in main */
char line_buf[SHELL_DEFAULT_BUFSIZE];
shell_run(NULL, line_buf, SHELL_DEFAULT_BUFSIZE);
return 0;
```

Build and run:
```sh
$ make all term
> help
help
Command              Description
---------------------------------------
> 
```

---

## Adding commands to the shell

- `shell_commands` module &#x21d2; add default commands (`reboot`)

- Include extra modules with predefined commands: `ps`, `random`

- Define your own handler:

```c
int cmd_handler(int argc, char **argv);
```

- Add it to the shell initialization:

```c
#include "shell.h"

static int cmd_handler(int argc, char **argv)
{
    /* Your code */
}

static const shell_command_t shell_commands[] = {
    { "command", "description", cmd_handler },
    { NULL, NULL, NULL }
};
[...]
shell_run(shell_commands, line_buf, SHELL_DEFAULT_BUFSIZE);
```

---

## An example of command handler

```c
static int cmd_handler(int argc, char **argv)
{
    if (argc < 3) {
        printf("usage: %s <arg1> <arg2>\n", argv[0]);
        return 1;
    }

    printf("Using arguments %s and %s\n", argv[1], argv[2]);
    return 0;
}
```

```c
$ make all term
> command
usage: command <arg1> <arg2>
> command arg1 arg2
Using arguments arg1 and arg2
```

It works the same on hardware without modifications:
```c
$ make BOARD=b-l072z-lrwan1 flash term
```

---

## Exercise: basic interaction with the hardware

- RIOT defines macros for interacting with LEDs:<br>
  &#x21d2; **LEDi_ON**, **LEDi_OFF**, **LEDi_TOGGLE** with i in {0, 1, ..., N}

- The _LEDi_ macros are defined in **board.h** files because they are specific to a board

- Open `getting-started/led-app/main.c`

- Add a shell command that toggles the on-board leds (_LEDi\_TOGGLE_):
```sh
$ make -C getting-started/led-app/ all term
[...]
> toggle
Usage: toggle <led num>
> toggle 0
LED_RED_TOGGLE
> toggle 1
LED_GREEN_TOGGLE
```

- Run it on the B-L072Z-LRWAN1 board
```sh
$ make BOARD=b-l072z-lrwan1 -C getting-started/led-app/ flash term
```

---

## Discovering the example applications

- Go to the RIOT source directory

- Build, flash and interact with the following applications:

  - `examples/default`

  - `examples/saul`

- Test applications also provides good examples to start the RIOT

---

## Summary

- Setup your environment

- Build & run your first RIOT application, native and on hardware

- Debug your application

- How to extend an application, the `shell`

- Basic interaction with the hardware