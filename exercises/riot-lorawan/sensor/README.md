# Sensor data to LoRaWAN

## Goal

Write an application that periodically sends data read from a sensor to the
LoRaWAN network.

## Info

- This task is a follow up from [simple](../simple) task.
- A HTS221 relative humidity and temperature sensor will be used

## Instructions

- Read relative humidity and temperature from HTS221 sensor.
- Send every 20s the sensor values to the LoRaWAN network. The format of the
  message will be `T: XX.X°C, H: XX.X%`

_TIP_: Reuse parts of the code from
[getting-started/sensor](../../getting-started/sensor) application
