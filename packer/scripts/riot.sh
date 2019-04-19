#!/bin/bash -eux

apt-get -y install cmake curl git build-essential
apt-get -y install vim emacs
apt-get -y install python-setuptools
apt-get -y install python-argparse python3-pip python-pip python3-serial
apt-get -y install mosquitto-clients
apt-get -y install socat g++-multilib
DEBIAN_FRONTEND=noninteractive DEBCONF_NONINTERACTIVE_SEEN=true apt-get -y install tshark

# Allow usage of 
adduser user dialout

# Customize launchers
sudo -u user dbus-launch gsettings set org.gnome.shell favorite-apps \
    "['firefox.desktop', \
      'org.gnome.Nautilus.desktop', \
      'gnome-terminal.desktop', \
      'gedit.desktop', \
      'vim.desktop', \
      'emacs25.desktop']"

# Turn off screensaver
sudo -u user dbus-launch gsettings set org.gnome.desktop.screensaver lock-delay 3600
sudo -u user dbus-launch gsettings set org.gnome.desktop.screensaver lock-enabled false
sudo -u user dbus-launch gsettings set org.gnome.desktop.screensaver idle-activation-enabled false

# Install ARM GNU Embedded toolchain
ARM_GCC_URL="https://developer.arm.com/-/media/Files/downloads/gnu-rm"
ARM_GCC_VERSION="7-2018q2"
ARM_GCC_ARCHIVE="gcc-arm-none-eabi-7-2018-q2-update-linux.tar.bz2"
ARM_GCC_ARCHIVE_URL="${ARM_GCC_URL}/${ARM_GCC_VERSION}/${ARM_GCC_ARCHIVE}"

cd /opt && wget -nv -O - "${ARM_GCC_ARCHIVE_URL}" | tar -jxf -

echo "export PATH=/opt/gcc-arm-none-eabi-7-2018-q2-update/bin:\$PATH" >> /home/user/.bashrc

# IoT-LAB CLI tools
pip3 install iotlabwscli
pip3 install iotlabsshcli
pip3 install iotlabcli

# Python tools
pip3 install aiocoap paho-mqtt
pip install pyocd paho-mqtt

# GNU Radio
apt-install -y gnuradio gr-osmosdr

# OpenOCD
apt-get install -y build-essential libftdi-dev libhidapi-dev \
        libusb-1.0-0-dev libudev-dev autoconf libsqlite3-dev \
        libpopt-dev libxml2-dev ruby libtool pkg-config

git clone https://github.com/ntfreak/openocd openocd && \
    cd openocd && \
    git checkout 05e0d633bad9e8b0bdfaf16fc76ab1f9d9419d8b && \
    ./bootstrap && \
    ./configure --enable-cmsis-dap --enable-hidapi-libusb && \
    make -j2 && \
    make install && \
    cd .. && rm -rf openocd

# EDBG
git clone https://github.com/ataradov/edbg && \
    cd edbg && \
    git checkout 80c50d03aac831f87f513a5d5455df1286bcb540 && \
    make all && \
    install -m 755 edbg /usr/bin && \
    cd .. && rm -rf edbg

# Udev rules
# JLink
echo 'SUBSYSTEM=="usb", ATTRS{idVendor}=="1366", ATTRS{idProduct}=="1015", MODE="0664", GROUP="dialout"' \
     > /etc/udev/rules.d/riot-course.rules
# ST-Link
echo 'SUBSYSTEM=="usb", ATTRS{idVendor}=="0483", ATTRS{idProduct}=="374b", MODE="0664", GROUP="dialout"' \
     >> /etc/udev/rules.d/riot-course.rules
# CMSIS-DAP
echo 'SUBSYSTEM=="usb", ATTRS{idVendor}=="03eb", ATTRS{idProduct}=="2111", MODE="0664", GROUP="dialout"' \
     >> /etc/udev/rules.d/riot-course.rules
echo 'KERNEL=="hidraw*", ATTRS{idVendor}=="03eb", ATTRS{idProduct}=="2111", MODE="664", GROUP="dialout"' \
     >> /etc/udev/rules.d/riot-course.rules
# Arduino Zero
echo 'SUBSYSTEM=="usb", ATTRS{idVendor}=="03eb", ATTRS{idProduct}=="2157", MODE="0664", GROUP="dialout"' \
     >> /etc/udev/rules.d/riot-course.rules
echo 'KERNEL=="hidraw*", ATTRS{idVendor}=="03eb", ATTRS{idProduct}=="2157", MODE="664", GROUP="dialout"' \
     >> /etc/udev/rules.d/riot-course.rules
# DAPLink
echo 'SUBSYSTEM=="usb", ATTRS{idVendor}=="0d28", ATTRS{idProduct}=="0204", MODE="0664", GROUP="dialout"' \
     >> /etc/udev/rules.d/riot-course.rules
echo 'KERNEL=="hidraw*", ATTRS{idVendor}=="0d28", ATTRS{idProduct}=="0204", MODE="664", GROUP="dialout"' \
     >> /etc/udev/rules.d/riot-course.rules
# IoT-LAB M3
echo 'SUBSYSTEM=="usb", ATTR{idProduct}=="6010", ATTR{idVendor}=="0403", MODE="0664", GROUP="dialout"' \
     >> /etc/udev/rules.d/riot-course.rules
echo 'SUBSYSTEM=="usb", ATTR{idProduct}=="6011", ATTR{idVendor}=="0403", MODE="0664", GROUP="dialout"' \
     >> /etc/udev/rules.d/riot-course.rules

# Clone riot-course
cd /home/user && git clone --recursive https://github.com/aabadie/riot-course.git
