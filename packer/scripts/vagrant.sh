#!/bin/bash -eux

date > /etc/vagrant_box_build_time

mkdir /home/user/.ssh
wget --no-check-certificate \
    'https://raw.githubusercontent.com/hashicorp/vagrant/master/keys/vagrant.pub' \
    -O /home/user/.ssh/authorized_keys
chown -R user /home/user/.ssh
chmod -R go-rwsx /home/user/.ssh
