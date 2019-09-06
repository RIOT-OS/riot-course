## Toggle LEDs with shell commands


### Introduction

RIOT defines macros for interacting with LEDs &#x21d2; **LEDi_ON**,
**LEDi_OFF**, **LEDi_TOGGLE** with i in {0, 1, ..., N}

These macros are defined in the **board.h** file of each board that provides
LEDs. This is because LEDs or buttons are specific to a board.
See `~/riot-course/RIOT/boards/b-l072z-lrwan1/include/board.h` for example.

In this exercise, we propose to write a shell command that toggles a LED given
its number:
```sh
> toggle
Usage: toggle <led num>
> toggle 0
Toggle led 0
> toggle 1
Toggle led 1
```

### Exercise

1. Go into the `~/riot-course/exercises/getting-started/led` application
  directory and edit the `main.c`

2. Add a shell command 'toggle' that toggles the on-board leds.
   You can start from the shell application previously written in
   `~/riot-course/exercises/getting-started/shell`.
   `board.h` also needs to be included.

   _note:_ ensure that LEDs number given doesn't exceeds the number of
   available LEDs (*clue:* the B-L072Z-LRWAN1 has 4 LEDs, native 2).

3. Build and run the application for `native` target:
```sh
$ make all term
```

3. Build and run the application for the B-L072Z-LRWAN1 board

<br><br>_**Remember:**_ if you use a node on IoT-LAB, you need to also
pass to the `make` command the `IOTLAB_NODE` variable with the correct node
assigned to it.<br>
__Example:__ `IOTLAB_NODE=st-lrwan1-10.saclay.iot-lab.info`.

```sh
$ make BOARD=b-l072z-lrwan1 flash term
```

Now let's continue with the
[sensor exercise](https://github.com/riot-os/riot-course/tree/master/exercises/getting-started/sensor).
