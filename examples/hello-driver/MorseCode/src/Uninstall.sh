#!/bin/sh
module="keymorse"
device="mo"
mode="664"

rm -f /dev/${device}0
/sbin/rmmod -f ./$module.ko
