#!/bin/bash -eux

apt-get -y upgrade
apt-get -y autoremove
apt-get -y clean

echo "cleaning up guest additions"
rm -rf VBoxGuestAdditions_*.iso VBoxGuestAdditions_*.iso.?

echo "cleaning permissions"
chown -R user:user /home/user
