class: center, middle

# LoRaWAN with RIOT

---

## IoT protocols

.center[
  iser  <img src="images/iot-protocols-overview.png" alt="" style="width:800px;"/>
]

---

## Overview of LoRaWAN

<br/>

- Designed by Semtech and promoted by the LoRa Alliance

<br/>
.center[
    <a href=https://www.semtech.com/><img src="images/semtech.png" alt="" style="width: 200px;"/></a>
    <a href=http://www.lora-alliance.org/><img src="images/lora-alliance.png" alt="" style="width: 200px;"/></a>
]

<br/>


- First release 1.0 of the LoRaWaN specification in 2015

- Latest release 1.1 in 2018

- Based on long range radio communication modulation, LoRa

- Star network topology &#x21d2; devices talks to the network via gateways

---

## A few words on LoRa

<table style="width:100%;margin-top:-40px">
<tr>
  <td><ul>
  <li>Long range radio technology<br/><br/></li>
  <li>Spread Spectrum modulation: <br/><br/>&#x21d2; "Chirp Spread Spectrum"<br/><br/></li>
  <li>Very robust to noise, multipath and Doppler effect</li>
  </ul></td>
  <td>.center[
      <img src="images/lora-chirp.jpg" alt="" style="width: 200px;"/><br/>
      <img src="images/lora-css.jpg" alt="" style="width: 280px;"/>
    ]
</tr>
<tr>
  <td><ul>
        <li>Raising the spreading factor:
        <br/><br/>
            <ul>
                <li>increases the range (until several kilometers)</li>
                <li>increases the time on air</li>
                <li>increases energy consumption</li>
            </ul>
        </li>
    </ul>
  </td>
  <td><img src="images/lorawan-datarate-sf.png" alt="" style="width: 300px;"/></td>
</tr>
</table>

---

## The LoRaWAN protocol

.center[<img src="images/lorawan-classes.jpg" alt="" style="width: 500px;"/><br/>]

<br/>

- Different frequency bands depending on the geographical regions


- Use LoRa modulation


- 3 device classes &#x21d2; A, B & C


- The application layer is directly on top of the MAC layer

---

## Access to the physical layer

.center[
    <img src="images/lorawan-frequency.png" alt="" style="width: 600px;"/>
]

<br/>

- Public and free **ISM bands** used: EU868 (ETSI), US915, etc

- Bands are divided into **channels** of 3 different widths: 125kHz, 250kHz ou 500kHz

- Time constrained access to the physical layer &#x21d2; **Duty Cycle** (1% / channel)

- Example: at least 16 channels can be used in EU868 band


---

## Time On Air

Dependent on several factors: payload, bandwidth, spreading factor, etc.

Calculating the TOA:
- [LoRa Airtime Calculator spreadsheet](https://docs.google.com/spreadsheets/d/1voGAtQAjC1qBmaVuP1ApNKs1ekgUjavHuVQIXyYSvNc/edit#gid=0)
- [lorawan_toa package](https://github.com/tanupoo/lorawan_toa)
- [Equations from LoRa designer's guide](https://www.semtech.com/uploads/documents/LoraDesignGuide_STD.pdf)

---

## Class A & C devices

<table style="width:100%">
<tr>
  <td><b>Class A device</b>
  <ul>
  <li>Can only receive after a send</li>
  <li>Smallest power consumption</li>
  <li>Can be used on battery</li>
  </ul>
  
  </td>
  <td><img src="images/lorawan-class-a.png" alt="" style="width: 350px;"/><br/>
  .center[<img src="images/lorawan-consumption.png" alt="" style="width: 250px;"/><br/>
<span style="left-margin: 10px;font-style: italic;font-size:12px;text-align:right">Power consumption of a class A device</span>]</td>
</tr>
</table>

<table style="width:100%">
<tr>
  <td><b>Class C device</b>
  <ul>
  <li>Always listening: low latency</li>
  <li>More power consumption</li>
  <li>Cannot be used on battery</li>
  </ul>
  </td>
  <td><img src="images/lorawan-class-c.png" alt="" style="width: 350px;"/><br/></td>
</tr>
<table>

---

## LoRaWAN network architecture

.center[
    <img src="images/lorawan-system.png" alt="" style="width: 600px;"/><br/>
]

- **Devices and gateways** exchange messages using LoRa communications

- **Gateway** are connected to the network server via regular Internet protocols

- Users access their data via an application connected to the network server

- Security of the data is garantueed by **AES** encryption (symmetric keys)

---

## Structural overview of the network parts

.center[
    <img src="images/lorawan-network.png" alt="" style="width: 700px;"/><br/>
]

<table style="width:100%">
<tr>
  <td><b>Gateway manufacturers</b>
  <ul>
  <li>IMST Lite Gateway https://shop.imst.de</li>
  <li>Kerlink https://www.kerlink.fr/</li>
  <li>Multitech: https://www.multitech.com/</li>
  </ul>
  </td>
  <td><b>Network servers implementation</b>
  <ul>
  <li>https://www.loraserver.io/ (Opensource)</li>
  <li>https://www.resiot.io/en/<br><br><br></li>
  </ul>
  </td>
</tr>
<table>

---

## How to program the end-device

Existing open-source implementations:

- Arduino LMIC https://github.com/matthijskooijman/arduino-lmic
  &#x21d2; nearly unmaintained

- Loramac-node https://github.com/Lora-net/LoRaMac-node
  &#x21d2; reference implementation, used for certification from LoRa Alliance

<br>

End-device high-level support (generally based on Loramac-node):

- ARM mbedOS: https://www.mbed.com/en/platform/mbed-os/

- Mynewt: https://mynewt.apache.org/

- Micropython: https://pycom.io/

- RIOT: https://riot-os.org/

---

## Device communication on the network

.center[
    <img src="images/lorawan-encryption.png" alt="" style="width: 650px;"/><br/>
]

<br/>

- Every device is identified by a 4 bytes address

- "Network session key" &#x21d2; used to encrypt the network related data (MAC)

- "Application session key" &#x21d2; used to encrypt the application related data

---

## Activation procedures

.center[To exchange data, all devices must be activated by the network]

&#x21d2; 2 type of activation procedures:

- Over-The-Air Activation(OTAA)

- Activation By Personnalization (ABP)

.center[
    <img src="images/loraotaa.jpg" alt="" style="width: 600px;"/><br/>
]

---

## Activation procedures


- in **OTAA**:
  - Requires Device EUI, Application EUI and Application Key information

  - The device initiates a handshake with the server to get its address and
    a "nonce" &#x21d2; the device address changes after each activation

  - The 2 session keys are derived from the application key and the nonce

- in **ABP**

  - Requires Application session key, Network session key and device address

  - No handshake required

---

## Network operators

Lots of public network operators:

- Actility https://www.actility.com/

- Loriot https://www.loriot.io/

- Objenious (Bouygues Telecom) http://objenious.com/

- Orbiwise  https://www.orbiwise.com/

- TheThingsNetwork https://www.thethingsnetwork.org/

.center[
    <img src="images/ttn-logo.svg" alt="" style="width: 200px;"/><br/>
]

---

## TheThingsNetwork (TTN)

- The network deployment is **community based**

- Software stack is open-source

.center[
    <img src="images/ttn-map.png" alt="" style="width: 650px;"/><br/>
]

- Unlimited access to the backend

  - no device limit

  - no message limit (with respect to the duty-cycle)

  - friendly API (MQTT)

---

## First steps with TTN: practice

1. Create an account<br>
  https://account.thethingsnetwork.org/register

  Manage your gateways and application from your web console: https://console.thethingsnetwork.org/

2. Managing your gateways (optional)<br>
  https://www.thethingsnetwork.org/docs/gateways/registration.html

3. Add a new application<br>
  https://console.thethingsnetwork.org/applications

4. Register your device in your application<br>
  https://console.thethingsnetwork.org/applications/yourapplication

---

## Test TTN with RIOT: practice (1)

- <a href="http://doc.riot-os.org/group__pkg__semtech-loramac.html">LoRaWAN port documentation</a>

- Build and run the demo application provided by RIOT (in `~/riot-course/RIOT`)

```sh
make -C tests/pkg_semtech-loramac flash term
```

- Configure the device using the shell of RIOT

```sh
> loramac set deveui 0000000000000000
> loramac set appeui 0000000000000000
> loramac set appkey 00000000000000000000000000000000
```

- Join the network using OTAA activation procedure

```sh
> loramac join otaa
Join procedure succeeded!
```

- Send (and eventually receive) messages to the network

```sh
> loramac tx HelloWorld!
Tx done
```

---

## Test TTN with RIOT: practice (2)

- **Exercise:** `~/riot-course/exercises/riot-lorawan/simple`

Follow the [exercise README](https://github.com/aabadie/riot-course-exercises/tree/master/riot-lorawan/simple)

---

## Exercise: Send sensor data to TTN

- **Exercise:** `~/riot-course/exercises/riot-lorawan/sensor`

Follow the [exercise README](https://github.com/aabadie/riot-course-exercises/tree/master/riot-lorawan/sensor)

---

## Integration with external services

- Use of TTN http and/or MQTT API to retrieve the IoT data

- Super simple to integrate

- Available services:

  - Customizable dashboards with Cayenne<br>
    https://mydevices.com/

  - Location service with Collos<br>
    http://preview.collos.org/

  - Gather and analyze workspace use and sensors with OpenSensors<br>
    https://opensensors.com/

  - Just store your IoT data with TheThingsIndustries<br>
    https://www.thethingsindustries.com/

---

## An example: Cayenne

https://mydevices.com/cayenne/docs/lora/#lora-the-things-network

- Create only dashboards in a few clicks from your LoRaWAN data

- Access your sensor data from anywhere

- Payload format requirement: Low Power Payload (LPP)

  - Library available for python/micropython:<br>
  https://github.com/jojo-/py-cayenne-lpp

  - Library available for Arduino (C++):<br>
  https://github.com/sabas1080/CayenneLPP

  - Generic library in C<br>
  https://github.com/aabadie/cayenne-lpp

---

## Exercise: Integration with Cayenne LPP

- **Exercise:** `~/riot-course/exercises/riot-lorawan/lpp`

Follow the [exercise README](https://github.com/aabadie/riot-course-exercises/tree/master/riot-lorawan/lpp)

---

## The TTN MQTT API

- MQTT protocol uses a publish/subscribe approach
.center[
    <img src="images/pub-sub-model.png" alt="" style="width: 350px;"/><br/>
]

- TTN MQTT API documentation<br>
https://www.thethingsnetwork.org/docs/applications/mqtt/

- Reference implementation provided by the Eclipse Mosquitto project<br>
https://mosquitto.org/

- Eclipse also provides a python library: _paho_<br>
https://www.eclipse.org/paho/

---

## The TTN MQTT API

.center[
    <img src="images/overview_application.png" alt="" style="width: 350px;"/><br/>
]

---

## Exercise: Downlink from a LoRaWAN network

- **Exercise:** `~/riot-course/exercises/riot-lorawan/downlink`

Follow the [exercise README](https://github.com/aabadie/riot-course-exercises/tree/master/riot-lorawan/downlink)

---

## Exercise: enable low power

- **Exercise:** `~/riot-course/exercises/riot-lorawan/pm`

Follow the [exercise README](https://github.com/aabadie/riot-course-exercises/tree/master/riot-lorawan/pm)

---

class: center, middle

# The End

[Back to the course](https://github.com/aabadie/riot-course#content-of-the-course)
