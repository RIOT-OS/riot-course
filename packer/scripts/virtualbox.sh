mkdir /tmp/virtualbox
VERSION=$(cat /home/user/.vbox_version)
mount -o loop /home/user/VBoxGuestAdditions_$VERSION.iso /tmp/virtualbox
sh /tmp/virtualbox/VBoxLinuxAdditions.run
umount /tmp/virtualbox
rmdir /tmp/virtualbox
rm /home/user/*.iso
