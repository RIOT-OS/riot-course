# RIOT online course

This project provides a learning course for [RIOT](https://riot-os.org), an
operating system for constrained IoT devices, i.e. powered by microcontrollers.

## Content of the course

The course is divided in 5 sections:

- [Introduction](https://riot-os.github.io/riot-course/slides/01-introduction)
  contains generalities about the RIOT project
- [Getting started](https://riot-os.github.io/riot-course/slides/02-getting-started)
  contains the basics to start building and programming basic applications
  with RIOT
- [RIOT basics](https://riot-os.github.io/riot-course/slides/03-riot-basics)
  contains information about the internal structure of the OS (source code
  organization, build system, kernel) but also gives information about the
  hardware abstraction layer, the drivers and packages
- [Networking in RIOT](https://riot-os.github.io/riot-course/slides/04-networking-in-riot)
  provides basics on IoT protocols supported by RIOT (6LowPAN/IPv6, LoRa) and
  lists the network stacks provided by the OS
- [LoRaWAN with RIOT](https://riot-os.github.io/riot-course/slides/05-lorawan-with-riot)
  gives an overview of the LoRaWAN protocol and how to use it with RIOT
- [Security with RIOT](https://riot-os.github.io/riot-course/slides/06-security-with-riot)
  gives an overview of the IoT security requirements and tools to address those

The full course is designed for 2 full days of work by mixing lectures and
exercises to put in practice the exposed notions.

## How to use the course

Only a web browser with an internet connection is needed:

- The slides of each section can be followed online, directly from GitHub
- All exercises are using Jupyterlab Notebooks hosted on
  [https://labs.iot-lab.info](https://labs.iot-lab.info). All you need is an
  [IoT-LAB account](https://www.iot-lab.info/testbed/signup).
  The source code of the Jupyter Notebooks is available at
  [https://github.com/iot-lab/iot-lab-training](https://github.com/iot-lab/iot-lab-training).


## Hardware used

The boards used during the exercises are all hosted on the
[IoT-LAB testbed](https://www.iot-lab.info):

- The [IoT-LAB M3](https://www.iot-lab.info/docs/boards/iot-lab-m3/) boards for
  exercises from the [RIOT basics](https://riot-os.github.io/riot-course/slides/03-riot-basics)
  and [Networking in RIOT](https://riot-os.github.io/riot-course/slides/04-networking-in-riot) sections,

- ST boards for applications requiring LoRa radio: the
  [B-L072Z-LRWAN1](http://www.st.com/en/evaluation-tools/b-l072z-lrwan1.html)
  with the
  [X-NUCLEO-IKS01A2](http://www.st.com/en/ecosystems/x-nucleo-iks01a2.html)
  extension board.

### Tutorials based on this course

This course together with the exercices can be used for shorter and more
oriented tutorials.
Here is a list of existing tutorials:

- [RIOT Summit - Beginner Tutorial on LoRaWAN](https://riot-os.github.io/riot-course/slides/tutorial-summit-lorawan)
- [RIOT Summit - Beginner Tutorial on Security](https://riot-os.github.io/riot-course/slides/tutorial-summit-security)
- [RIOT Summit - Beginner Tutorial on Networking](https://riot-os.github.io/riot-course/slides/tutorial-summit-networking)
- [Inria Academy Master Class - Inria Chile](https://riot-os.github.io/riot-course/slides/tutorial-inria-academy)

## License

All course material (slides) is licensed under the Creative commons license
[CC-BY-ND](https://creativecommons.org/licenses/by-nd/4.0/)

![CC-BY-ND](https://mirrors.creativecommons.org/presskit/buttons/80x15/png/by-nd.png)
