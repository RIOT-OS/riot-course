.PHONY: all clean

RIOT_VM_FILE ?= RIOT-VM.ova
OUTPUT_DIR ?= output-virtualbox-iso
RIOT_VM_BOX ?= riot-vm-0.1.0.box
BUILDS_DIR ?= builds

$(OUTPUT_DIR)/$(RIOT_VM_FILE):
	@packer build riot-vm.json

all: $(OUTPUT_DIR)/$(RIOT_VM_FILE)

clean:
	rm -rf $(BUILDS_DIR) $(OUTPUT_DIR)

upload: all
	@echo -n Computing MD5 checksum...
	@md5sum $(OUTPUT_DIR)/$(RIOT_VM_FILE) > $(OUTPUT_DIR)/$(RIOT_VM_FILE).MD5SUM
	@echo Done
	@echo -n Computing SHA256 checksum...
	@sha256sum $(OUTPUT_DIR)/$(RIOT_VM_FILE) > $(OUTPUT_DIR)/$(RIOT_VM_FILE).SHA256SUM
	@echo Done
	@chmod +r $(OUTPUT_DIR)/$(RIOT_VM_FILE)
	@scp $(OUTPUT_DIR)/$(RIOT_VM_FILE)* srv-http:/var/www/html/vms/.
	@chmod +r $(BUILDS_DIR)/$(RIOT_VM_FILE)
	@scp $(BUILDS_DIR)/$(RIOT_VM_BOX) srv-http:/var/www/html/vms/.
