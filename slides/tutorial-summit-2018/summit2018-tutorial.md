class: center, middle

# RIOT Beginner Tutorial

## Summit 2018

---

## Objective of the tutorial

1. Learn how to write and build a RIOT application

  .right[
      <img src="images/riot-logo.png" alt="" style="width:100px;"/>
  ]

--

2. Use IoT-LAB for testing a RIOT application remotely on real hardware

  .right[
      <img src="images/fit-iotlab-logo.png" alt="" style="width:100px;"/>
  ]

--

3. Learn the basics of LoRaWAN networks

  .right[
      <img src="images/lorawan-logo.png" alt="" style="width:100px;"/>
  ]

--

4. Write a LoRaWAN application based on RIOT and TheThingsNetwork provider

  .right[
      <img src="images/ttn-logo.png" alt="" style="width:100px;"/>
  ]

--

5. Publish sensor data to a Web dashboard

---

## Tutorial organization

- Use the preconfigured VM for building applications

- Use the IoT-LAB testbed to run the applications

- Hardware used

---

## About the VM

- It contains a version the RIOT course in `~/riot-course`

- All required tools are already installed:

  - The GNU ARM Embedded 7.3 toolchain is installed

  - The IoT-LAB cli-tools are installed

  - A basic list of common editors: Vim, Emacs, VSCode

---

## About IoT-LAB

.center[<a href=https://www.iot-lab.info>https://www.iot-lab.info</a>]

- IoT-LAB is a large scale experimentation testbed

  - Can be used for testing wireless communication networks on small devices

  - Can be used for learning IoT programming and communication protocols

  - Can be used for testing software platforms

--

- **2071** programmable nodes, 4 architectures
  <br> &#x21d2; Cortex-M, MSP430, Cortex-A8, AVR

--

- Heterogeneous platforms
  <br> &#x21d2; iotlab-m3, iotlab-a8, Atmel SAMR21-Xpro, Arduino Zero, ST B-L072Z-LRWAN1, Zolertia Firefly

--

- Heterogeneous radios &#x21d2; 802.15.4, 802.15.4g, LoRa, BLE (soon)

--

- Start learning IoT with IoT-LAB at <a href=https://www.iot-lab.info/tutorials/>https://www.iot-lab.info/tutorials/</a>

---

## Let's get started