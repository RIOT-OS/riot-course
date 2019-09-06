APPLICATION=lorawan

BOARD ?= b-l072z-lrwan1

# Default radio driver is Semtech SX1276 (used by the B-L072Z-LRWAN1 board)
DRIVER ?= sx1276

# Default region is Europe and default band is 868MHz
REGION ?= EU868

USEMODULE += xtimer
USEMODULE += hts221
USEMODULE += $(DRIVER) 
USEPKG += semtech-loramac

DEVELHELP ?= 1

RIOTBASE ?= $(CURDIR)/../../../../RIOT

CFLAGS += -DREGION_$(REGION)
CFLAGS += -DLORAMAC_ACTIVE_REGION=LORAMAC_REGION_$(REGION)

include $(RIOTBASE)/Makefile.include
