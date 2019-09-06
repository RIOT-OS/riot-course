## Timers

### Introduction

In this exercise, we propose to manage 3 LEDs from 3 different threads. Each LED
blinks differently:
- _thread 1_ toggles LED0 every 500ms
- _thread 2_ toggles LED1 every seconds
- _thread 3_ toggles LED2 every 2 seconds

By default, the application can run on the ST B-L072Z-LRWAN1 board but any
other board with at least 3 LEDs could be used.

### Exercise

- Go to `~/riot-course/exercises/riot-basics/timers`

#### Write the application

- Implement the LED0 toggling in thread1. Use `xtimer_usleep` and the
  `LED0_TOGGLE` macro.

- Repeat this for LED1 and LED2.

- Build and flash the application, and see the LEDs blinking!

Now let's continue in the
[riot-basics slides](https://riot-os.github.io/riot-course/slides/03-riot-basics/#22).
