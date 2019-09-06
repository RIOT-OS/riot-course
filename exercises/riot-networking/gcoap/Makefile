APPLICATION = gcoap_basic

BOARD ?= native

RIOTBASE ?= $(CURDIR)/../../../RIOT

# Import radio driver module
USEMODULE += gnrc_netdev_default
USEMODULE += auto_init_gnrc_netif

# Import network modules
USEMODULE += gnrc_ipv6_default

# Add gcoap module dependency here


# fmt is required by coap server value handler


# include this for printing IP addresses
USEMODULE += shell_commands

DEVELHELP ?= 1

include $(RIOTBASE)/Makefile.include
