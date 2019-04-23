#!/bin/bash -eux

apt-get update
apt-get -y upgrade
apt-get -y install linux-headers-$(uname -r)
apt-get -y install ubuntu-desktop
apt-get -y install language-pack-fr

# Remove welcome wizard
apt-get -y remove gnome-initial-setup

# Remove Amazon, etc launchers
apt -y purge ubuntu-web-launchers

# Fix locale setup
locale-gen
localectl set-locale LANG="en_US.UTF-8"

# Remove default directories in home
echo "enabled=false" > /home/user/.config/user-dirs.conf
echo "" > /home/user/.config/user-dirs.dirs
rm -rf /home/user/{Desktop,Documents,Downloads,Music,Pictures,Public,Templates,Videos}

# Allow usage of serial port
adduser user dialout

# Customize launchers
sudo -u user dbus-launch gsettings set org.gnome.shell favorite-apps \
    "['firefox.desktop', \
      'org.gnome.Nautilus.desktop', \
      'gnome-terminal.desktop', \
      'gedit.desktop', \
      'vim.desktop', \
      'emacs25.desktop']"

# Disable lock screen and screensaver
sudo -u user dbus-launch gsettings set org.gnome.desktop.session idle-delay 0
sudo -u user dbus-launch gsettings set org.gnome.desktop.lockdown disable-lock-screen true
sudo -u user dbus-launch gsettings set org.gnome.settings-daemon.plugins.power sleep-inactive-battery-timeout 0
sudo -u user dbus-launch gsettings set org.gnome.settings-daemon.plugins.power sleep-inactive-ac-timeout 0
sudo -u user dbus-launch gsettings set org.gnome.settings-daemon.plugins.power idle-dim false
sudo -u user dbus-launch gsettings set org.gnome.desktop.screensaver idle-activation-enabled false
sudo -u user dbus-launch gsettings set org.gnome.desktop.screensaver lock-enabled false

# Disable software-update pop-up
sudo -u user dbus-launch gsettings set com.ubuntu.update-notifier no-show-notifications true
sudo -u user dbus-launch gsettings set com.ubuntu.update-notifier regular-auto-launch-interval 3650
sudo -u user dbus-launch gsettings set com.ubuntu.update-manager launch-time 1900000000

# disable daily apt unattended updates.
echo 'APT::Periodic::Enable "0";' >> /etc/apt/apt.conf.d/10periodic

echo '%sudo   ALL=(ALL:ALL) NOPASSWD:ALL' >> /etc/sudoers

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
