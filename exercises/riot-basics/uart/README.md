## UART

### Introduction

In this exercise, we propose to use the UART API of RIOT in conjunction with
threads to print all characters received on the stdio.

### Exercise

- Go to `~/riot-course-exercises/riot-basics/uart`

#### Write the application

**Note:** Use first UART, e.g `UART_DEV(0)`

- Add the UART feature to the requirements of the application (in the `Makefile`):
```mk
FEATURES_REQUIRED += periph_uart
```

- Add the UART header file in your application:
```c
#include "periph/uart.h"
```

- Write an application with one thread, called `printer_thread`, that waits
  for incoming messages

- For each message, the thread prints "received &lt;c&gt;", with &lt;c&gt;
  the content of the message as a char

- Initialize `UART_DEV(0)` at 115200 bauds, with `uart_cb` as callback function

- For each character received on the UART (just press a key + return on your
  keyboard), send a message containing the character to the printer thread

- Experiment with long strings &#x21d2; you need a message queue or an
  external buffer

Now let's continue in the
[riot-basics slides](https://riot-os.github.io/riot-course/slides/03-riot-basics/#30).
