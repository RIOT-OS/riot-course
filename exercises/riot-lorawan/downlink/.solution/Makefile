APPLICATION=lorawan

BOARD ?= b-l072z-lrwan1

# Default radio driver is Semtech SX1276 (used by the B-L072Z-LRWAN1 board)
DRIVER ?= sx1276

# Default region is Europe and default band is 868MHz
LORA_REGION ?= EU868

USEMODULE += $(DRIVER) 
USEPKG += semtech-loramac
USEMODULE += semtech_loramac_rx

DEVELHELP ?= 1

RIOTBASE ?= $(CURDIR)/../../../../RIOT

include $(RIOTBASE)/Makefile.include
