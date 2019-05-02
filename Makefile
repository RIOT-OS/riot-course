.PHONY: all init-submodules packer packer-upload

MAKE_CMD = make -j BUILD_IN_DOCKER=1

all: init-submodules
	@$(MAKE_CMD) -C exercises/getting-started/first-app
	@$(MAKE_CMD) -C exercises/getting-started/shell
	@$(MAKE_CMD) -C exercises/getting-started/shell/.solution
	@$(MAKE_CMD) -C exercises/getting-started/led
	@$(MAKE_CMD) -C exercises/getting-started/led/.solution
	@$(MAKE_CMD) -C exercises/getting-started/sensor
	@$(MAKE_CMD) -C exercises/getting-started/sensor/.solution

init-submodules:
	@git submodule update --recursive

packer:
	@make -C packer

packer-upload:
	@make -C packer upload

