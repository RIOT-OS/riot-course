class: center, middle

# Prerequisites

---

## Retrieve the course

1. Install and setup Git:
```sh
$ sudo apt-get install git
$ git config --global user.name "Your name"
$ git config --global user.email "Your email"
```
2. Clone this course from GitHub:
```sh
$ git clone --recursive https://github.com/aabadie/riot-course
```

- In the next sections, we assume that the sources are located in
**~/riot-course**

- Exercises are located in: **~/riot-course/exercises**

- The RIOT code (2019.04) is located in: **~/riot-course/RIOT**

---

## Setup your working environment

- All commands of the course are now supposed to be run from the pre-configured
  virtual machine (VM)

- This VM is compatible with [Virtualbox](https://www.virtualbox.org/) (>= 5.2)
  or [VMWare player](https://www.vmware.com/products/workstation-player.html)

- You can install it by 2 means:

  1. Download the VM from [here](http://fit-demo.inria.fr/vms/RIOT-VM.ova)
     and import it in Virtualbox or VMWare

  2. Setup and start the riot-course VM with
     [vagrant](https://www.vagrantup.com/)
  ```sh
  $ cd ~/riot-course
  $ vagrant up
  $ vagrant ssh
  ```

*Note:* To toggle the keyboard layout, for example to `fr`:
- From the command line, use
```sh
$ setxkbmap fr
```
- From the GNOME interface, click on `en` at the top right of the menu bar

---

## Using IoT-LAB (optional)

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
