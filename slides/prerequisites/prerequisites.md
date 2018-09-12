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

- The RIOT code (2018.07) is located in: **~/riot-course/RIOT**

---

## Setup your working environment (1)

First possibility: install a toolchains and development tools locally (Linux only)

- Build essential tools (make, gcc, etc):
```sh
$ sudo apt-get install build-essential g++-multilib python-serial
```
- Install toolchains (ARM):
```sh
$ sudo add-apt-repository ppa:team-gcc-arm-embedded/ppa
$ sudo apt-get update
$ sudo apt-get install gcc-arm-embedded
```
- Install OpenOCD programming tool (version >= 0.10 required)
```sh
$ sudo apt-get install openocd
```

---

## Setup your working environment (2)

- Second possibility: using the RIOT Docker image
```sh
$ docker pull riot/riotbuild
$ cd <application directory>
$ make BUILD_IN_DOCKER=1
```

- Second possibility: using a VM, with vagrant
```sh
$ cd <riot_base_directory>
$ vagrant up
$ vagrant ssh
```

<br>
More info on the Wiki:

.center[&#x21d2; &nbsp;&nbsp;https://github.com/RIOT-OS/RIOT/wiki/Setup-a-Build-Environment
]
