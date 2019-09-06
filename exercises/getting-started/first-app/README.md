## Your first RIOT application

### Build and run the application on **native** target

1. Open a command line window and `cd` to
  `~/riot-course/exercises/getting-started/first-app`

2. Build the application for **native** using the **make** command:
  ```sh
  $ make
  ```
Note that by default the `native` target is selected in the application
`Makefile`.

The **native** target builds a RIOT application which is a simple
**Linux process**.

The build system prints the location of the application file. Here it's
`~/riot-course/exercises/getting-started/first-app/bin/native/first-app.elf`

The build process also prints information about different sizes and binary
structure of the application.

3. Check the type of the elf file generated using `file` command and verify
   that it's a regular Linux process.

4. Run the application:
  - by calling it directly
  - using the **term** target of `make`
  ```
  $ make term
  .../getting-started/first-app/bin/native/example.elf
  RIOT native interrupts/signals initialized.
  LED_RED_OFF
  LED_GREEN_ON
  RIOT native board initialized.
  RIOT native hardware initialization complete.

  main(): This is RIOT! (Version: vm-riot)
  My first RIOT application
  ```

### Build and run the application on a specific hardware

In this section, you will build the same application but this time for the
[ST B-L072Z-LRWAN1](https://www.st.com/en/evaluation-tools/b-l072z-lrwan1.html)
target board.

The codename of this board in RIOT is **b-l072z-lrwan1**.

1. Use `BOARD` variable to select this target at build time.

```sh
$ make BOARD=b-l072z-lrwan1
Building application "first-app" for "b-l072z-lrwan1" with MCU "stm32l0".

"make" -C /home/user/RIOT/boards/b-l072z-lrwan1
"make" -C /home/user/RIOT/core
"make" -C /home/user/RIOT/cpu/stm32l0
"make" -C /home/user/RIOT/cpu/cortexm_common
"make" -C /home/user/RIOT/cpu/cortexm_common/periph
"make" -C /home/user/RIOT/cpu/stm32_common
"make" -C /home/user/RIOT/cpu/stm32_common/periph
"make" -C /home/user/RIOT/cpu/stm32l0/periph
"make" -C /home/user/RIOT/drivers
"make" -C /home/user/RIOT/drivers/periph_common
"make" -C /home/user/RIOT/sys
"make" -C /home/user/RIOT/sys/auto_init
"make" -C /home/user/RIOT/sys/isrpipe
"make" -C /home/user/RIOT/sys/newlib_syscalls_default
"make" -C /home/user/RIOT/sys/pm_layered
"make" -C /home/user/RIOT/sys/tsrb
"make" -C /home/user/RIOT/sys/uart_stdio
 text   data    bss    dec    hex filename
 7596    140   2740  10476   28ec .../getting-started/first-app/bin/b-l072z-lrwan1/first-app.elf
```

2. Check the type of the generated file. It's a binary application compiled for
  the ARM architecture

3. Run the application on hardware.
  <br><br>_**Important notes:**_
    - if you use a node on IoT-LAB, you need to also
  pass to the `make` command the `IOTLAB_NODE` variable with the correct node
  assigned to it.<br>
  __Example:__ `IOTLAB_NODE=st-lrwan1-10.saclay.iot-lab.info`.<br>
    - if you use a board on the table, simply plug it via USB to your computer.

  - Use **term** target to open a serial terminal on the board:
  ```sh
  $ make BOARD=b-l072z-lrwan1 term
  ```
  **term** opens a serial terminal on the board (using pyterm by default). In the
  case of IoT-LAB, it opens a SSH tunnel to IoT-LAB and redirects the serial port
  from there.
  <br>**Keep the serial terminal open.**
  - **In another terminal window**, use the **flash** target to program the
  board:
  ```
  $ make BOARD=b-l072z-lrwan1 flash
  ```
  Now take a look at the message displayed by the RIOT application in the first
  serial terminal.

**flash** calls the flasher tool automatically (OpenOCD or iotlab-node in the
case of IoT-LAB)

```sh
$ make BOARD=b-l072z-lrwan1 flash term
[...]
### Flashing Target ###
Open On-Chip Debugger 0.10.0+dev-00290-g5a98ff78 (2018-01-31-14:50)
[...]
INFO # Connect to serial port /dev/ttyACM0
Welcome to pyterm!
Type '/exit' to exit.
INFO # main(): This is RIOT! (Version: vm-riot)
INFO # My first RIOT application
```

Now let's continue with the
[getting-started slides](https://riot-os.github.io/riot-course/slides/02-getting-started/#11).
