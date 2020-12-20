APPLICATION=lorawan

BOARD ?= b-l072z-lrwan1

# Default radio driver is Semtech SX1276 (used by the B-L072Z-LRWAN1 board)
DRIVER ?= sx1276

# Default LoRa region is Europe and default band is 868MHz
LORA_REGION ?= EU868

USEMODULE += hts221
USEMODULE += $(DRIVER) 

USEPKG += semtech-loramac
USEPKG += cayenne-lpp

FEATURES_REQUIRED += periph_rtc
FEATURES_REQUIRED += periph_eeprom

DEVELHELP ?= 1

RIOTBASE ?= $(CURDIR)/../../../../RIOT

# Enable lowest possible power mode (e.g. STANDBY mode on STM32)
CFLAGS += -DPM_BLOCKER_INITIAL=0x01010100

include $(RIOTBASE)/Makefile.include
