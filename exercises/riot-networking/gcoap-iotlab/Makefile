APPLICATION = gcoap_iotlab

# use iotlab-m3:
BOARD = iotlab-m3

RIOTBASE ?= $(CURDIR)/../../../RIOT

# Import radio driver module
USEMODULE += gnrc_netdev_default
USEMODULE += auto_init_gnrc_netif

# Import network modules
USEMODULE += gnrc_ipv6_default

# Add gcoap module dependency here
USEMODULE += gcoap

# Import lps331ap driver module


# include this for printing IP addresses
USEMODULE += shell_commands

DEVELHELP ?= 1

include $(RIOTBASE)/Makefile.include
