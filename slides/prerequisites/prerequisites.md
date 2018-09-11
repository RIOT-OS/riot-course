class: center, middle

# Prerequisites

---

## Retrieve the course

1. Install and setup Git:
```bash
$ sudo apt-get install git
$ git config --global user.name "Your name"
$ git config --global user.email "Your email"
```
2. Clone this course from GitHub:

```
$ git clone --recursive https://github.com/aabadie/riot-course
```

In the next sections, we assume that the sources are located in
**~/riot-course**

Exercises are located in: **~/riot-course/exercises**
The RIOT code (2018.07) is located in: **~/riot-course/RIOT**

---

## Setup your working environment (1)

First possibility: install a toolchains and development tools locally (Linux only):
  - Build essential tools (make, gcc, etc):
```bash
$ sudo apt-get install build-essential g++-multilib python-serial
```
  - Install toolchains (ARM):
```bash
$ sudo add-apt-repository ppa:team-gcc-arm-embedded/ppa
$ sudo apt-get update
$ sudo apt-get install gcc-arm-embedded
```
  - Install OpenOCD programming tool (version >= 0.10 required)
```bash
$ sudo apt-get install openocd
```

---

## Setup your working environment (2)

- Using Docker
```bash
$ docker pull riot/riotbuild
$ cd <application directory>
$ make BUILD_IN_DOCKER=1
```

- Using a VM, with vagrant
```bash
$ vagrant up
$ vagrant ssh
```

- More info on the Wiki:

.right[&#x21d2; &nbsp;&nbsp;https://github.com/RIOT-OS/RIOT/wiki/Setup-a-Build-Environment
]
