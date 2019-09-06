## Write an application with a basic shell

### Introduction

In this exercise, we propose to discover the ways proposed by RIOT to add a
shell functionnality to a RIOT application.
You will first add existing shell commands by adding required modules to an
application and after you will write your own shell command.

### Exercise

#### Build an run a basic application with a shell

1. Go into the `~/riot-course/exercises/getting-started/shell` application
  directory and edit the `Makefile`

2. Add the **shell** module to the `Makefile`

```mk
USEMODULE += shell
```

3. Modify the `main.c`:

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

Your application runs on native with an empty shell: no commands are available.

#### Add commands to the shell

To add shell commands, there are 3 cases:

- you can include the `shell_commands` module &#x21d2; this will add default
  commands (`reboot`) or commands provided for other included modules

- you can include extra modules with predefined commands: `ps`, `random`

- you can define your own command handler in `main.c`:
  ```c
  static int cmd_handler(int argc, char **argv)
  {
      /* Your code */
  }
  ```
  The command handler needs to be registered in the array of available
  commands:
  ```c
  static const shell_command_t shell_commands[] = {
    { "command", "description", cmd_handler },
    { NULL, NULL, NULL }
  };
  ```
  In this case, `shell_run` must be called like the following (use
  `shell_commands` instead of `NULL` for the first argument):
  ```c
  shell_run(shell_commands, line_buf, SHELL_DEFAULT_BUFSIZE);
  ```

Now let's add new commands:

1. Add `shell_commands` and `ps` modules to the application `Makefile`:
```mk
USEMODULE += shell_commands
USEMODULE += ps
```

2. Build and run the application and verify that a new `ps` command is added:
```sh
$ make all term
```

3. Write a command handler that requires 2 arguments and print them. The
handler prints a usage message if an invalid list of argument is given.

4. Register this new handler to the list of shell commands

5. Build and run tha application. Verify that the new handler works as
expected.

6. Now re-build the same application for the `b-l072z-lrwan1` board and run it
<br><br>_**Remember:**_ if you use a node on IoT-LAB, you need to also
pass to the `make` command the `IOTLAB_NODE` variable with the correct node
assigned to it.<br>
__Example:__ `IOTLAB_NODE=st-lrwan1-10.saclay.iot-lab.info`.
```sh
$ make BOARD=b-l072z-lrwan1 flash term
```

It works exactly the same on hardware without modifications :)

Now let's continue with the
[getting-started slides](https://riot-os.github.io/riot-course/slides/02-getting-started/#14).