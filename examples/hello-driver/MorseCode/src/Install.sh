#!/bin/sh
module="keymorse"
device="mo"
mode="664"


# invoke insmod with all arguments we were passed
# and use a pathname, as newer modutils don’t look in . by default
/sbin/insmod -f ./$module.ko $* || exit 1

# remove stale nodes
rm -f /dev/${device}0

major=$(awk "\$2==\"$module\" {print \$1}" /proc/devices)

#first device
mknod /dev/${device}0 c $major 0

# give appropriate group/permissions, and change the group.
# Not all distributions have staff; some have "wheel" instead.
group="staff"
grep -q 'ˆstaff:' /etc/group || group="users"

chgrp $group /dev/${device}0
chmod $mode /dev/${device}0
