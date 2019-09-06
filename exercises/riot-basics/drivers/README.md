## Drivers

### Introduction

In this exercise, we propose to read and print values from 2 sensor in 2
separate threads.

This exercise, as-is, can only work with boards providing HTS221 and LSM6DSL
sensors but can easily be adapted to other sensors supported by RIOT.

### Exercise

- Go to `~/riot-course/exercises/riot-basics/drivers`

- Write an application that starts 2 threads
  - `thread1` reads the HTS221 sensors values (temperature and humidity)
    every 2 seconds and prints the values to stdout
  - `thread2` reads the LSM6DSL accelerometer values every 100ms and prints
    the values to stdout

- The drivers are initialized in the `main` function **before** the threads

- Don't forget to load the driver modules in the application Makefile


_Tip_: You can refer to the online documentation of the device drivers

  - HTS221: http://doc.riot-os.org/group__drivers__hts221.html

  - LSM6DSL: http://doc.riot-os.org/group__drivers__lsm6dsl.html

  - Test applications are also helpful: <br>
    &#x21d2; `~/RIOT/tests/drivers_hts221`<br>
    &#x21d2; `~/RIOT/tests/drivers_lsm6dsl`

Now let's continue in the
[riot-basics slides](https://riot-os.github.io/riot-course/slides/03-riot-basics/#37).
