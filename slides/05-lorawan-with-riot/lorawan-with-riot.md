class: center, middle

# LoRaWAN with RIOT

---

# Overview of LoRaWAN


<br/>

- IoT protocol by Semtech and promoted by the LoRa Alliance

<br/>
.center[
    <a href=https://www.semtech.com/><img src="images/semtech.png" alt="" style="width: 200px;"/></a>
    <a href=http://www.lora-alliance.org/><img src="images/lora-alliance.png" alt="" style="width: 200px;"/></a>
]

<br/>


- First release 1.0 of the LoRaWaN specification in 2015


- Based on long range radio communication modulation, LoRa


- Star network topology



---

## A few words on LoRa

<table style="width:100%;margin-top:-40px">
<tr>
  <td><ul>
  <li>Long range radio technology<br/><br/></li>
  <li>Spread Spectrum modulation: <br/><br/>&#x21d2; "Chirp Spread Spectrum"<br/><br/></li>
  <li>Very robust to noise</li>
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
                <li>decreases the bandwidth</li>
                <li>increases the time on air</li>
            </ul>
        </li>
    </ul>
  </td>
  <td><img src="images/lorawan-datarate-sf.png" alt="" style="width: 400px;"/></td>
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

<br/>

.center[
    <img src="images/lorawan-network.png" alt="" style="width: 750px;"/><br/>
]

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

2 type of activation procedures:

- Over-The-Air Activation(OTAA)

- Activation By Personnalization (ABP)

.center[
    <img src="images/loraotaa.jpg" alt="" style="width: 600px;"/><br/>
]

---

## Activation procedures


- in **OTAA**:
  - Requires Device EUI, Application EUI and Application Key information

  - The device initiates a handshake with the server to get its address and a "nonce" &#x21d2; the device address changes after each activation

  - The 2 session keys are derived from the application key and the nonce

- in **ABP**

  - Requires Application session key, Network session key and device address

  - No handshake required
