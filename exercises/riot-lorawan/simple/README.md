# Simple LoRaWAN test in RIOT

## Goal

Write an application that periodically sends data to a LoRaWAN network.

## Instructions

- Configure the application for OTAA activation (use your Device EUI,
  application EUI and application key)

- Follow the
  [RIOT Semtech Loramac package online documentation](http://doc.riot-os.org/group__pkg__semtech-loramac.html)
  and implement an application that sends "This is RIOT!" every 20 seconds.

_Note_: Don't take into account the reception and persistence parts.

_TIP_: In the `Payload formats > Payload format` of your application console,
select the `Custom` payload format and in the `Decoder` text edit, add the
following decoding javascript function:

```js
function Decoder(bytes, port)
{
var message = "";

for  (var i=0; i < bytes.length; i++) {
    message += String.fromCharCode(bytes[i]);
}
var decoded = {};
decoded.message = message;
return decoded;
}
```

Thanks to this, each data sent by the device, visible in the device web console
under `Devices > <device_id> > Data, is displayed in a human readable format.
