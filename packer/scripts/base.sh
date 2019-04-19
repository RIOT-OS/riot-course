#!/bin/bash -eux

apt-get update
apt-get -y upgrade
apt-get -y install linux-headers-$(uname -r)
apt-get -y install ubuntu-desktop
apt-get -y install language-pack-fr

# Remove welcome wizard
apt-get -y remove gnome-initial-setup

# Remove Amazon, etc launcher
apt -y purge ubuntu-web-launchers

# Fix locale setup
locale-gen
localectl set-locale LANG="en_US.UTF-8"

# disable daily apt unattended updates.
echo 'APT::Periodic::Enable "0";' >> /etc/apt/apt.conf.d/10periodic

# autologin
cp /etc/gdm3/custom.conf /etc/gdm3/custom.conf.bak
echo "[daemon]" > /etc/gdm3/custom.conf
echo "AutomaticLoginEnable = true" >> /etc/gdm3/custom.conf
echo "AutomaticLogin = user" >> /etc/gdm3/custom.conf
echo "[security]" >> /etc/gdm3/custom.conf
echo "[xdmcp]" >> /etc/gdm3/custom.conf
echo "[chooser]" >> /etc/gdm3/custom.conf
echo "[debug]" >> /etc/gdm3/custom.conf

# Keyboard layouts
sed -i 's/XKBLAYOUT=.*/XKBLAYOUT="us,fr"/g' /etc/default/keyboard
# sed -i 's/XKBOPTIONS=.*/XKBOPTIONS="grp:ctrl_shift_toggle"/g' /etc/default/keyboard

echo "UseDNS no" >> /etc/ssh/sshd_config
