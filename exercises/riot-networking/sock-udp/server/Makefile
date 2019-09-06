APPLICATION = sock_server

BOARD ?= native

RIOTBASE ?= $(CURDIR)/../../../../RIOT

SERVER_PORT ?= 8888

# Import driver modules

# Import network modules

# include shell commands for printing IP addresses
USEMODULE += shell_commands

DEVELHELP ?= 1

CFLAGS += -DSERVER_PORT=$(SERVER_PORT)

include $(RIOTBASE)/Makefile.include
