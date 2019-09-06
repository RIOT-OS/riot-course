# Adding Low Power

## Goal

Write an application that periodically sends data and sleeps between each send
for reducing power consumption (using STANDBY low power mode).

## Instructions

- Start from application [riot-lorawan/lpp](../lpp)
- In the application Makefile, unlock by default the STANDBY low power mode by
  adding before the line `include $(RIOTBASE)/Makefile.include`:
  ```
  CFLAGS += '-DPM_BLOCKER_INITIAL={ .val_u32 = 0x01010100 }'
  ```
- Still in the application Makefile, add the required RTC and EEPROM features:
  ```
  FEATURES_REQUIRED += periph_rtc
  FEATURES_REQUIRED += periph_eeprom
  ```
- in main.c, edit the EUIS and key for OTAA activation
- Modify the sender function to become a sender thread and start it at the end
  of the main function
- Modify the sender thread so that it triggers a lorawan send only after an IPC
  message (`msg_t` type) is received (e.g. use `msg_receive` at the beginning
  of the while loop)
- After a LoRaWAN send, configure an RTC alarm 20s later and finally unlock the
  STOP power mode
- In the RTC alarm callback, lock the STOP power mode (1) and then send a
  message to the sender thread
- Test your application

_TIP_: Check the RIOT RTC API in
 `http://doc.riot-os.org/group__drivers__periph__rtc.html`

_TIP_: Check the Layered PM infrastructure in
 `http://doc.riot-os.org/group__sys__pm__layered.html`
