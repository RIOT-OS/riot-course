## RTC

### Introduction

In this exercise, we propose to experiment the RTC API.

### Exercise

1. Go to `~/riot-course/exercises/riot-basics/rtc`

2. Write an application that gets the current RTC time and print it to stdout
   (Don't forget to add `periph_rtc` to the list of required features and to
   include it in your application).

3. Start one thread, called `blink_thread`, that waits for incoming messages.
   For each message, the thread turns on the LED1 during 1 seconds, then it
   turns it off

4. After turning off the LED, the thread gets the current time and prints it

5. Finally, it sets an RTC alarm 5 seconds later

6. In the RTC alarm callback, send a message to the `blink_thread

Now let's continue in the
[riot-basics slides](https://riot-os.github.io/riot-course/slides/03-riot-basics/#32).
