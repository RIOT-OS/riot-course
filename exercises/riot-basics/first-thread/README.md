## Threads

### Introduction

In this exercise, we propose to discover the basic mecanism proposed by RIOT to
configure, start, and monitor threads.

You will use the `ps` module with the `shell` commands to monitor running
threads and play with thread priorities to ensure your application runs as
expected.

At the beginning, you will run the thread based application on `native` and at
the end of the exercise, we propose to run this same application, unchanged, on
real hardware.

### Exercise

Go to `~/riot-course/exercises/riot-basics/first-thread`

#### List running threads using the shell

- Add the `shell`, `shell_commands` and `ps` modules to the application
  `Makefile`:
  ```mk
  USEMODULE += shell
  USEMODULE += shell_commands
  USEMODULE += ps
  ```

- In `main.c`, add the code to start the shell with default commands:
  ```c
  #include "shell.h"
  ```
  And in the `main` function:
  ```c
  char line_buf[SHELL_DEFAULT_BUFSIZE];
  shell_run(NULL, line_buf, SHELL_DEFAULT_BUFSIZE);
  ```

- Build and run this application, list running threads:
  ```sh
  $ make -C ~/riot-course/exercices/riot-basics/first-thread all term
  > ps
  pid | name                 | state    Q | pri | stack  ( used) | base addr  | current     
    - | isr_stack            | -        - |   - |   8192 (   -1) | 0x56617380 | 0x56617380
    1 | idle                 | pending  Q |  15 |   8192 (  436) | 0x566150a0 | 0x56616f00 
    2 | main                 | running  Q |   7 |  12288 ( 3020) | 0x566120a0 | 0x56614f00 
      | SUM                  |            |     |  28672 ( 3456)
  ```

#### Start a new thread

- Start a new thread that just prints "Hello from thread"
```c
#include "thread.h"
static char stack[THREAD_STACKSIZE_MAIN];
void *thread_handler(void *arg)
{
        /* thread code */
        return NULL;
}
kernel_pid_t pid = thread_create(stack,
                                 sizeof(stack),
                                 THREAD_PRIORITY_MAIN - 1,
                                 0,
                                 thread_handler,
                                 NULL,
                                 "thread name");
```

- Build and run the application and verify the message is correctly displayed
  (use native and the board).
  Try again to display the list of threads. What is the problem ?

- Now add an infinite loop in the thread handler function, before the return:
```c
while (1) {}
```
- Build and run the application again. Try to list the available threads. What
  is happening now ?

- Change the priority of your thread to something lower (e.g. increase the
  value). Now you should be able to use the shell and see your thread in the
  result of the `ps` command.

#### Run on hardware

- Test your application on the ST `b-l072z-lrwan1` board:
```c
$ make BOARD=b-l072z-lrwan1 -C ~/riot-course/exercices/riot-basics/first-thread flash term
```

_Note:_ If you use hardware on FIT IoT-LAB, add `IOTLAB_NODE=auto-ssh` to `make`.

Now let's continue in the
[riot-basics slides](https://riot-os.github.io/riot-course/slides/03-riot-basics/#12).
