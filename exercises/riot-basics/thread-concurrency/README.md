## Thread concurrency

### Introduction

In this exercise, we propose to write and read in a globally shared buffer and
in thread-safe way.

You will start 2 threads:
- a first thread writes some content in a shared buffer every 100ms. Each write
  takes 200ms to complete
- a first thread reads the content of the shared buffer and prints it every
  200ms

You will start by running the application on `native` and at the end of
the exercise, you will run this same application, unchanged, on real hardware.

### Exercise

- Go to `~/riot-course/exercises/riot-basics/thread-concurrency`

#### Write a non thread-safe application

- Implement the logic of the printer thread: every 200ms it will print the
  content of the `buffer` attribute of `data`. Use `xtimer_usleep` function
  to add the 200ms delay. `US_PER_MS` macro is also useful for converting ms in
  us.

- Implement the logic of the writer thread: it will modify the content of the
  buffer and the wait 100ms before doing so again. Here we want to simulate an
  action that takes time,
  so this should be done in 3 steps:
  - Write some content in the buffer (use `sprintf` or equivalent)
  - Wait 200ms
  - Write the end of the content in the buffer
  ```c
  size_t p = sprintf(data.buffer, "start: %"PRIu32"", xtimer_now().ticks32);
  xtimer_usleep(200 * US_PER_MS);
  p += sprintf(&data.buffer[p], " - end: %"PRIu32"", xtimer_now().ticks32);
  ```

- Build and run this application: you should see the messages printed are very
  often invalid. This is because the buffer is not completely written when the
  printer thread reads it: we need a synchronization mecanism.
  ```sh
  start: 24
  start: 24 - end: 200172
  start: 300267
  start: 300267 - end: 500409
  start: 600555
  start: 900836
  start: 900836 - end: 1100944
  start: 1201012
  start: 1501294
  start: 1501294 - end: 1701402
  start: 1801475
  start: 2101777
  start: 2101777 - end: 2301924
  start: 2401998
  start: 2702242
  start: 2702242 - end: 2902380
  ```

#### Make the application thread-safe

To make this application thread-safe, we propose to use mutexes.
The `data` variable already provide a `mutex` attribute and we'll use it to
synchronize the printer and the writer threads.

- In the writer thread, protect the buffer writes with calls to `mutex_lock`/
  `mutex_unlock` functions:
  ```c
  mutex_lock(&data.lock);
  [...]
  mutex_unlock(&data.lock);
  ```
- Do the same for the access to the buffer in the printer thread

- Build and run the application: now the content of the buffer is correctly
  written each time!
  ```sh
  start: 30 - end: 200193
  start: 300285 - end: 500418
  start: 600567 - end: 800697
  start: 900809 - end: 1100906
  start: 1201024 - end: 1401154
  start: 1501293 - end: 1701448
  start: 1801585 - end: 2001705
  start: 2101908 - end: 2302040
  ```

  
#### Run on hardware

- Test your application on the ST `b-l072z-lrwan1` board:
```c
$ make BOARD=b-l072z-lrwan1 -C ~/riot-course/exercices/riot-basics/thread-concurrency flash term
```

_Note:_ If you use hardware on FIT IoT-LAB, add `IOTLAB_NODE=auto-ssh` to `make`

Now let's continue in the
[riot-basics slides](https://riot-os.github.io/riot-course/slides/03-riot-basics/#15).
