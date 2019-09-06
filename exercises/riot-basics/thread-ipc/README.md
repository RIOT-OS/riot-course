## IPC

### Introduction

In this exercise, we propose to exchange messages between threads using the IPC
API.

You will write a shell command that sends a string to a thread. The receiver
thread prints each receive message.

At the beginning, you will run the application on `native` and at the end of
the exercise, you will run this same application, unchanged, on real hardware.

### Exercise

- Go to `~/riot-course/exercises/riot-basics/thread-ipc`

#### Write the application

- In the send command handler, use `msg_send` and attach the string to send
  to the content ptr of a message (`msg_t)

- In the receiver thread handler, just wait for incoming IPC messages with
  `msg_receive`, in a loop.

- Test your application:
```sh
$ make -C ~/riot-course/exercices/riot-basics/thread-ipc all term
> send "Hello World"
Message received: Hello World
```

#### Run on hardware

- Test your application on the ST `b-l072z-lrwan1` board:
```c
$ make BOARD=b-l072z-lrwan1 -C ~/riot-course/exercices/riot-basics/thread-ipc flash term
```

_Note:_ If you use hardware on FIT IoT-LAB, add `IOTLAB_NODE=auto-ssh` to `make`.

Now let's continue in the
[riot-basics slides](https://riot-os.github.io/riot-course/slides/03-riot-basics/#18).
