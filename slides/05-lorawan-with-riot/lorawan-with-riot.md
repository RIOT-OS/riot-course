class: center, middle

# LoRaWAN with RIOT

---

## Généralités sur LoRaWAN


<br/>

- Protocole IoT créé par Semtech et aujourd'hui soutenu par la LoRa Alliance

<br/>
.center[
    <a href=https://www.semtech.com/><img src="images/semtech.png" alt="" style="width: 200px;"/></a>
    <a href=http://www.lora-alliance.org/><img src="images/lora-alliance.png" alt="" style="width: 200px;"/></a>
]

<br/>


- Version 1.0 de la spécification LoRaWAN parue en 2015


- Protocole de communication IoT longue portée


- Topologie de réseau en étoile



---

## Rappels sur LoRa

<!-- <img src="images/lorawan-datarates.jpeg" alt="" style="width: 200px;"/><br/> -->

<table style="width:100%;margin-top:-40px">
<tr>
  <td><ul>
  <li>Technologie radio longue portée<br/><br/></li>
  <li>Modulation à étalement de spectre: <br/><br/>&#x21d2; "Chirp Spread Spectrum"<br/><br/></li>
  <li>Très robuste au bruit</li>
  </ul></td>
  <td>.center[
      <img src="images/lora-chirp.jpg" alt="" style="width: 200px;"/><br/>
      <img src="images/lora-css.jpg" alt="" style="width: 280px;"/>
    ]
</tr>
<tr>
  <td><ul>
        <li>Quand le Spreading factor augmente:
        <br/><br/>
            <ul>
                <li>la portée augmente (jusqu'à plusieurs kilomètres)</li>
                <li>le débit diminue</li>
                <li>le airtime augmente</li>
            </ul>
        </li>
    </ul>
  </td>
  <td><img src="images/lorawan-datarate-sf.png" alt="" style="width: 400px;"/></td>
</tr>
</table>

---

## Le protocole LoRaWAN

.center[<img src="images/lorawan-classes.jpg" alt="" style="width: 500px;"/><br/>]

<br/>

- Utilise des bandes de fréquences différentes en fonction des régions


- Utilisation de la modulation LoRa


- 3 classes de device &#x21d2; A, B et C


- Couche application directement liée à la couche MAC

---

## Accès au support physique

.center[
    <img src="images/lorawan-frequency.png" alt="" style="width: 600px;"/>
]

<br/>

- Utilisation dans la bande ISM : exemple EU868 (ETSI)


- Occupation du support physique contraint en temps &#x21d2; Duty Cycle (1%)


- Canaux de largeurs 125kHz, 250kHz ou 500kHz


- En europe, au moins 16 canaux utilisables dans la bande des 868MHz


---

## Les classes de device A et C

<table style="width:100%">
<tr>
  <td><b>Device de classe A</b>
  <ul>
  <li>Il faut envoyer pour recevoir</li>
  <li>Classe la plus économe</li>
  <li>Utilisable sur batterie</li>
  </ul>
  
  </td>
  <td><img src="images/lorawan-class-a.png" alt="" style="width: 350px;"/><br/>
  .center[<img src="images/lorawan-consumption.png" alt="" style="width: 250px;"/><br/>
<span style="left-margin: 10px;font-style: italic;font-size:12px;text-align:right">Consommation énergétique d'un device de classe A</span>]</td>
</tr>
</table>

<table style="width:100%">
<tr>
  <td><b>Device de classe C</b>
  <ul>
  <li>Latence faible</li>
  <li>Plus gourmand en énergie</li>
  <li>Pas utilisable sur batterie</li>
  </ul>
  </td>
  <td><img src="images/lorawan-class-c.png" alt="" style="width: 350px;"/><br/></td>
</tr>
<table>

---

## Architecture d'un réseau LoRaWAN

.center[
    <img src="images/lorawan-system.png" alt="" style="width: 600px;"/><br/>
]

- Les devices communiquent en LoRa avec les gateways

- Les gateways communiquent par internet avec le serveur du réseau

- L'accès aux données se fait via une application qui intéragit avec le serveur

- La sécurité des données est assurée par l'algorithme de chiffrement par clés symétriques **AES**

---

## Schéma structurel des éléments du réseau

<br/>

.center[
    <img src="images/lorawan-network.png" alt="" style="width: 750px;"/><br/>
]

---

## Communication d'un device avec le réseau

.center[
    <img src="images/lorawan-encryption.png" alt="" style="width: 650px;"/><br/>
]

<br/>

- Chaque device est identifié sur le réseau par une adresse sur 4 octets

- "Network session key" &#x21d2; chiffrement des données propres au réseau (MAC)

- "Application session key" &#x21d2; chiffrement des données propres à l'application

---

## Activation OTAA d'un device

.center[
    <img src="images/loraotaa.jpg" alt="" style="width: 600px;"/><br/>
]

- Un challenge est effectué entre le serveur et un device pour obtenir son adresse
et un "nonce"

- Les 2 clés de session sont calculées à partir de la clé d'application et du nonce

<div style="font-size:18px;background:lightgrey;padding:5px">
<b>Remarque :</b> il existe aussi l'activation ABP (Activation By
Personnalization) pour laquelle l'adresse du device et les clés d session sont
connus à l'avance par le réseau et le device
</div>

---