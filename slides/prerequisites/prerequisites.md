class: center, middle

# Prerequisites

---

## Your working environment

- In all sections, we assume that this course is located in **~/riot-course**

- Exercises are located in: **~/riot-course/exercises**

- The RIOT sources (2019.04) are located in: **~/riot-course/RIOT**

- The [FIT IoT-LAB](https://www.iot-lab.info) testbed can be used to achieve
  the exercises requiring some hardware (especially in the
  [riot-networking](https://aabadie.github.io/riot-course/slides/04-networking-in-riot)
  section)

- For simplicity, all exercises can be done using a pre-configured virtual
  machine (VM): this VM is compatible with [Virtualbox](https://www.virtualbox.org/)
  (>= 5.2) or [VMWare player](https://www.vmware.com/products/workstation-player.html)

---

## Setup the VM

There are 2 ways to install it:

1. Download the VM from [here](http://fit-demo.inria.fr/vms/RIOT-VM.ova)
   and import it in Virtualbox or VMWare

2. Setup and start the riot-course VM with
  [vagrant](https://www.vagrantup.com/)
  ```sh
  $ git clone https://github.com/aabadie/riot-course
  $ cd riot-course
  $ vagrant up
  $ vagrant ssh
  ```

*Note:* To toggle the keyboard layout, for example to `fr`:
- From the command line, use
```sh
$ setxkbmap fr
```
- From the GNOME interface, click on `en` at the top right of the menu bar and
  switch to `fr`

---

## Retrieve the latest version course

1. Open a terminal in the VM (or use `vagrant ssh`)

2. Update the sources of the riot-course:
```sh
$ cd ~/riot-course
$ git pull
$ git submodule update --recursive exercises
$ git submodule update --recursive RIOT
```

---

## Setup your FIT IoT-LAB access (optional)

- First you need to create an account on FIT IoT-LAB at
  <a href=https://www.iot-lab.info/testbed/#/signup>
  https://www.iot-lab.info/testbed/#/signup</a>

- In the VM, setup your SSH access to the FIT IoT-LAB by following
  [this tutorial](https://www.iot-lab.info/tutorials/ssh-access/)

- In the VM, register your FIT IoT-LAB login/password locally using:
  ```sh
  $ iotlab-auth -u <your login>
  ```

In any case, it is recommended to play the
[online FIT IoT-LAB tutorials](https://www.iot-lab.info/tutorials/) first.

---

class: center, middle

[Back to the course](https://github.com/aabadie/riot-course#content-of-the-course)
