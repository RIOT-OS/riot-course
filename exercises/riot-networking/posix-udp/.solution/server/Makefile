APPLICATION = posix_server

BOARD ?= native

RIOTBASE ?= $(CURDIR)/../../../../../RIOT

SERVER_PORT ?= 8888

# Import radio driver module
USEMODULE += gnrc_netdev_default
USEMODULE += auto_init_gnrc_netif

# Import network modules
USEMODULE += gnrc_ipv6_default
USEMODULE += gnrc_sock_udp

# Import posix sockets
USEMODULE += posix_sockets

# include this for printing IP addresses
USEMODULE += shell_commands

DEVELHELP ?= 1

CFLAGS += -DSERVER_PORT=$(SERVER_PORT)

include $(RIOTBASE)/Makefile.include
