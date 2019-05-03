.PHONY: all clean init-submodules packer packer-upload

MAKE_CMD = make -j BUILD_IN_DOCKER=1

EXERCISES_DIR = exercises
GETTING_STARTED = $(EXERCISES_DIR)/getting-started
RIOT_BASICS = $(EXERCISES_DIR)/riot-basics
RIOT_NETWORKING = $(EXERCISES_DIR)/riot-networking
RIOT_LORAWAN = $(EXERCISES_DIR)/riot-lorawan

EXERCISES = $(GETTING_STARTED)/first-app \
            $(GETTING_STARTED)/shell/.solution \
            $(GETTING_STARTED)/led/.solution \
            $(GETTING_STARTED)/sensor/.solution \
            $(RIOT_BASICS)/first-thread/.solution \
            $(RIOT_BASICS)/thread-ipc/.solution \
            $(RIOT_BASICS)/thread-concurrency/.solution \
            $(RIOT_BASICS)/timers/.solution \
            $(RIOT_BASICS)/gpio/.solution \
            $(RIOT_BASICS)/uart/.solution \
            $(RIOT_BASICS)/rtc/.solution \
            $(RIOT_BASICS)/drivers/.solution \
            $(RIOT_NETWORKING)/sock-udp/.solution/client \
            $(RIOT_NETWORKING)/sock-udp/.solution/server \
            $(RIOT_NETWORKING)/posix-udp/.solution/client \
            $(RIOT_NETWORKING)/posix-udp/.solution/server \
            $(RIOT_NETWORKING)/gcoap/.solution \
            $(RIOT_NETWORKING)/gcoap-iotlab/.solution \
            $(RIOT_LORAWAN)/simple/.solution \
            $(RIOT_LORAWAN)/sensor/.solution \
            $(RIOT_LORAWAN)/lpp/.solution \
            $(RIOT_LORAWAN)/downlink/.solution \
            $(RIOT_LORAWAN)/pm/.solution \
            #

.PHONY: $(EXERCISES)

all: init-submodules $(EXERCISES)

clean:
	@for exercise in $(EXERCISES); \
	do BUILD_IN_DOCKER=1 make -C $${exercise} clean; \
	done

$(EXERCISES):
	@$(MAKE_CMD) -C $@

init-submodules:
	@git submodule update --recursive

packer:
	@make -C packer

packer-upload:
	@make -C packer upload

