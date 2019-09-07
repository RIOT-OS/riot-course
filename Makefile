.PHONY: all init-submodules build-exercises clean-exercises packer packer-clean packer-upload

all: init-submodules build-exercises

init-submodules:
	@git submodule update --recursive

build-exercises:
	@make -C exercises

clean-exercises:
	@make -C exercises clean

packer:
	@make -C packer

packer-clean:
	@make -C packer clean

packer-upload:
	@make -C packer upload
