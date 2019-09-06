## GPIO

### Introduction

In this exercise, we propose to use the GPIO API of RIOT to raise an
interrupt when an on-board button is pressed. The interrupt sub-routine is then
used to toggle an on-board LED.

### Exercise

- Go to `~/riot-course-exercises/riot-basics/gpio`

#### Write the application

**Note:** Use predefined `BTN_B1_PIN` and `LED1_PIN` macros and include `board.h`

- Add the GPIO's feature to the requirements of the application (in the `Makefile`):

```mk
FEATURES_REQUIRED += periph_gpio
FEATURES_REQUIRED += periph_gpio_irq
```

- Add the GPIO header file in your application:

```c
#include "periph/gpio.h"
```

- Write an application with one thread that waits for incoming messages

- For each message, the thread toggles the on-board LED0

- The on-board B1 user button and LED0 are initialized as follows in `main()`:
  - LED0 is initialized in GPIO_OUT mode
  - B1 is initialized in GPIO_IN mode with an interrupt callback function,
    `gpio_cb`, an interrupt is raised each time the button is pressed

- For each interrupt, a message is sent from the ISR to the led management
  thread &#x21d2; it toggles the LED0 state

_Note: we won't take care of the debounce issue_

_Note: don't connect the X-NUCLEO-IKS01A2 extension board since the on-board
       button pin is connected to the X-NUCLEO-IKS01A2 level translator which
       affects the level state for the button._

Now let's continue in the
[riot-basics slides](https://riot-os.github.io/riot-course/slides/03-riot-basics/#28).
