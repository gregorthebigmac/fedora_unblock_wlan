# fedora_unblock_wlan
A service which checks once per second to see if the wlan interface has been soft-blocked by rfkill and if so, unblocks it.

It also blocks bluetooth by default, because for some reason even if you set it to soft-blocked, the next time you reboot, it comes right back on by default.
