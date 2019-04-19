## RIOT course VM

### Requirements

* Virtualbox:

      sudo apt-get install -y virtualbox
      sudo apt-get install -y virtualbox-guest-additions-iso

* Vagrant: (https://www.vagrantup.com/downloads.html)

      wget https://releases.hashicorp.com/vagrant/2.x.x/vagrant_2.x.x_x86_64.deb
      dpkg -i vagrant_2.x.x_x86_64.deb

### About the VM

- Get the VM

    mkdir vagrant && cd vagrant
    vagrant init riot-course/ubuntu-riot

- Start the VM

    vagrant up

- Connect to the VM (headless)

    vagrant ssh

- Stop the VM

    vagrant stop

### Build the VM

Use Packer:  Packer: https://www.packer.io/downloads.html

    packer build packer/ubuntu-riot.json
    mkdir vagrant && cd vagrant
    vagrant init
    vagrant box add ubuntu-riot ../packer/builds/ubuntu-riot.box
    vagrant box list
