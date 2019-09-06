APPLICATION=gpio-application

BOARD ?= b-l072z-lrwan1

FEATURES_REQUIRED += periph_gpio
FEATURES_REQUIRED += periph_gpio_irq

DEVELHELP ?= 1

RIOTBASE ?= $(CURDIR)/../../../../RIOT

CFLAGS += -DAUTO_INIT_LED0

include $(RIOTBASE)/Makefile.include
