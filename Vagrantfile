Vagrant.configure("2") do |config|
  config.vm.box = "riot-course/riot-vm"
  config.vm.box_version = "0.1.0"
  config.ssh.username = "user"
  config.vm.synced_folder ".", "/vagrant", disabled: true
  config.vm.provider "virtualbox" do |v|
    v.name = "RIOT VM"
  end
end
