APPLICATION = sock_client

BOARD ?= native

RIOTBASE ?= $(CURDIR)/../../../../RIOT

SERVER_PORT ?= 8888
SERVER_ADDR ?= fe80::1

# Import radio driver module

# Import network modules

DEVELHELP ?= 1

CFLAGS += -DSERVER_PORT=$(SERVER_PORT)
CFLAGS += -DSERVER_ADDR=\"$(SERVER_ADDR)\"

include $(RIOTBASE)/Makefile.include
