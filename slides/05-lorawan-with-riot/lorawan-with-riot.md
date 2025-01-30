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
  <td>
  <ul>
  <li>Long range radio technology<br/><br/></li>
  <li>Very robust to noise, multipath and Doppler effect</li>
  <li>Spread Spectrum modulation: <br/><br/>&#x21d2; "Chirp Spread Spectrum"<br/><br/></li>
  <li>The binary data is coded by shifting the symbol<br/><br/></li>
  <li>Bandwidth can be 125, 250 or even 500kHz</li>
  </ul>
  </td>
  <td>.center[
      <img src="images/LPWAN_chirps.png" alt="" style="width: 250px;"/>
    ]
</tr>
</table>
.center[
  <img src="images/LPWAN_Physical.png" alt="" width="400">
]

---

## The spreading factor

* Spreading factor (SF) = duration of a chirp &#x21d2; increase SF by 1 = duration x 2

* SF7 reprensents 7 bits in 1 symbol

* Signals using different SF don't interfere &#x21d2; they are orthogonal

* In short, raising the spreading factor:
    * increases the range (up to several kilometers)
    * reduce the throughput
    * increase the time on air
    * increases energy consumption

.center[
  <img src="images/LPWAN_SF.png" alt="" style="width: 350px;height: 170px;"/>
  <img src="images/lorawan-datarate-sf.png" alt="" style="width: 350px;"/>
]

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
- [TTN Airtime Calculator](https://www.thethingsnetwork.org/airtime-calculator)
- [LoRa Airtime Calculator spreadsheet](https://docs.google.com/spreadsheets/d/1voGAtQAjC1qBmaVuP1ApNKs1ekgUjavHuVQIXyYSvNc/edit#gid=0)
- [lorawan_toa package](https://github.com/tanupoo/lorawan_toa)

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

.center[
    <img src="images/loraotaa.jpg" alt="" style="width: 600px;"/><br/>
]

- Activation By Personnalization (ABP):<br/>
  &#x21d2; No handshake, only requires APPSKEY, NWKSKEY and DEVADDR

---

## Network operators

Some LoRaWAN operators:

- Orange https://www.orange-business.com/en/products/iot-connect-anywhere

- Actility https://www.actility.com/

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

  - no strong message limit (with respect to the duty-cycle)

  - friendly API (MQTT)

---

## Test TTN with RIOT: practice

Follow the instructions in the notebook **riot/lorawan/ttn-getting-started/ttn-getting-started.ipynb**

.center[
<form class=notebook>
    <input class=login id="login_ttn_getting_started" type="text" oninput="check_login('login_ttn_getting_started', 'launcher_ttn_getting_started')" placeholder="Enter your IoT-LAB login">
    <input class=launcher id="launcher_ttn_getting_started" type="button" value="Launch notebook" onclick="open_notebook('login_ttn_getting_started', 'riot/lorawan/ttn-getting-started/ttn-getting-started.ipynb')" disabled>
</form>
]

---

## Exercise: Send sensor data to TTN

Follow the instructions in the notebook **riot/lorawan/ttn-sensors/ttn-sensors.ipynb**

.center[
<form class=notebook>
    <input class=login id="login_ttn_sensors" type="text" oninput="check_login('login_ttn_sensors', 'launcher_ttn_sensors')" placeholder="Enter your IoT-LAB login">
    <input class=launcher id="launcher_ttn_sensors" type="button" value="Launch notebook" onclick="open_notebook('login_ttn_sensors', 'riot/lorawan/ttn-sensors/ttn-sensors.ipynb')" disabled>
</form>
]

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

## Exercise: Downlink from a LoRaWAN network

Follow the instructions in the notebook **riot/lorawan/ttn-mqtt/ttn-mqtt.ipynb**

.center[
<form class=notebook>
    <input class=login id="login_ttn_mqtt" type="text" oninput="check_login('login_ttn_mqtt', 'launcher_ttn_mqtt')" placeholder="Enter your IoT-LAB login">
    <input class=launcher id="launcher_ttn_mqtt" type="button" value="Launch notebook" onclick="open_notebook('login_ttn_mqtt', 'riot/lorawan/ttn-mqtt/ttn-mqtt.ipynb')" disabled>
</form>
]

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

Follow the instructions in the notebook **riot/lorawan/ttn-cayenne-lpp/ttn-cayenne-lpp.ipynb**

.center[
<form class=notebook>
    <input class=login id="login_ttn_cayenne_lpp" type="text" oninput="check_login('login_ttn_cayenne_lpp', 'launcher_ttn_cayenne_lpp')" placeholder="Enter your IoT-LAB login">
    <input class=launcher id="launcher_ttn_cayenne_lpp" type="button" value="Launch notebook" onclick="open_notebook('login_ttn_cayenne_lpp', 'riot/lorawan/ttn-cayenne-lpp/ttn-cayenne-lpp.ipynb')" disabled>
</form>
]

---

class: center, middle

# The End

[Back to the course](https://github.com/riot-os/riot-course#content-of-the-course)
