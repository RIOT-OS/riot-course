# Downlinks from the LoRaWAN network

## Goal

Write an application that prints a message when it receives a downlink
from the LoRaWAN network.

## Instructions

- Reuse the [riot-lorawan/lpp](../lpp) application as a starting point
- Follow the
  [package documentation](http://doc.riot-os.org/group__pkg__semtech-loramac.html)
  to extend the application with receiving thread.
- Send downlink messages to your node from the TTN network: go to
  `Devices> [your_device] > Downlinks`
- **Optional**: Use the TTN MQTT broker to send and receive data from
  your node. Check the appendix below.

_TIP_: Read received payload, length and port from the
[`rx_data` member](http://doc.riot-os.org/structsemtech__loramac__t.html)
in the loramac descriptor.


## Appendix 1: Using the MQTT API

- Follow the MQTT quick start in TTN at
  `https://www.thethingsnetwork.org/docs/applications/mqtt/quick-start.html`
- Publish data to your node and subscribe to uplink messages

_TIP_: Use the mosquitto-clients command line tools to publish/subscribe to
MQTT topics.

_TIP_: base64 payload can be decoded with the following command:
```sh
`$ base64 -d <<< dGVzdA==`
```

## Appendix 2: Retrieve MQTT data from a custom script

- Edit the python script in the [script](../script) directory and replace
`USERNAME`, `PASSWORD` and `DEVICE_ID` with your TTN information.
- You can run the script with the following command:
```
$ python mqtt-client.py
```
- Modify the python script to make it send a downlink after each message
reveived from the device.
