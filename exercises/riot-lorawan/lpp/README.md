# Integration with Cayenne LPP

## Goal

Write an application that sends sensor data to the Cayenne LPP
integration in TTN.

## Instructions

- Reuse the application in [riot-lorawan/sensor](../sensor). To
  send data in the Cayenne LPP format, use the `cayenne-lpp` package.
  An example of usage of Cayenne LPP format is available in this
  [RIOT test application](https://github.com/RIOT-OS/RIOT/tree/master/tests/pkg_cayenne-lpp)
- Add the Cayenne integration to your TTN application under
  `Integrations> add integration`, and follow the instructions for Cayenne.
- Select the Cayenne LPP payload format under
  `Payload formats> Payload format`. Check the received data in
  the TTN dashboard.
- **Optional**: Display the data in the `mydevices.com` dashboard.
  Follow the `Set up your myDevices account` in
  `https://www.thethingsnetwork.org/docs/applications/cayenne/`

_TIP_: Reuse parts from `~/RIOT/tests/pkg_cayenne-lpp`

_TIP_: Check the available `cayenne-lpp` functions in
 `https://github.com/riot-os/cayenne-lpp/blob/master/cayenne_lpp.h`
