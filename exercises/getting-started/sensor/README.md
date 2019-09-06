## Read and print sensor values using shell commands

### Introduction

In this exercise, we propose to write 2 new shell commands that read
temperature and relative humidity values from a
[ST HTS221 sensor](https://www.st.com/en/mems-and-sensors/hts221.html).

This sensor is available on the
[ST X-NUCLEO-IKS01A2 shield](https://www.st.com/en/ecosystems/x-nucleo-iks01a2.html)
plugged on the [B-L072Z-LRWAN1](https://www.st.com/en/evaluation-tools/b-l072z-lrwan1.html)
board.

This exercise can only be run on hardware.

Here is the expected behaviour:
```sh
> temperature
Temperature: 18.3°C
> humidity: 75%
```

### Exercise

1. Go into the `~/riot-course/exercises/getting-started/sensor` application
  directory

2. Add the `hts221` module dependency to the application `Makefile`:
```mk
USEMODULE += hts221
```

3. Have a look at the
[hts221 test application](https://github.com/RIOT-OS/RIOT/blob/master/tests/driver_hts221/main.c)
source in RIOT codebase to see how it can be used.
For a detailed description of the driver API, see the
[online documentation](http://doc.riot-os.org/group__drivers__hts221.html).

4. Add necessary includes and declarations at the beginning of `main.c`
(after existing include):
```c
#include "hts221.h"
#include "hts221_params.h"

static hts221_t dev;
```

5. Add driver initialization code at the beginning of the main function
(after the existing startup message):
```c
if (hts221_init(&dev, &hts221_params[0]) != HTS221_OK) {
    puts("Cannot initialize hts221 sensor");
    return -1;
}
if (hts221_power_on(&dev) != HTS221_OK) {
    puts("Failed to set hts221 power on");
    return -2;
}
if (hts221_set_rate(&dev, dev.p.rate) != HTS221_OK) {
    puts("Failed to set hts221 continuous mode");
    return -3;
}
```
Indeed, the sensor driver must be correctly initialized before starting the
shell.

6. Add shell handler functions for the 'temperature' and 'humidity' functions.
You can start from the led application previously written in
`~/riot-course/exercises/getting-started/led` (there's a `.solution` directory
containing a working code)

7. Build and run the application for the B-L072Z-LRWAN1 board

<br><br>_**Remember:**_ if you use a node on IoT-LAB, you need to also
pass to the `make` command the `IOTLAB_NODE` variable with the correct node
assigned to it.<br>
__Example:__ `IOTLAB_NODE=st-lrwan1-10.saclay.iot-lab.info`.

```sh
$ make BOARD=b-l072z-lrwan1 flash term
```

Now let's continue with the
[getting-started slides](https://riot-os.github.io/riot-course/slides/02-getting-started/#18).
