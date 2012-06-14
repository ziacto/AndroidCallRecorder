mount -o remount /dev/block/mtdblock0 /system
mount -o remount /dev/block/mtdblock1 /
cp ./libasound.so /system/lib
cp ./alsa_amixer /system/xbin
cp ./alsa_aplay /system/xbin
cp ./alsa_ctl /system/xbin
cp ./alsa_client /
cp ./alsa_daemon /
cp ./live.conf /
cp ./t1.cfg /
cp ./t2.cfg /
cd /system/xbin
chmod 775 alsa_amixer alsa_aplay alsa_ctl
cd /
chmod 775 alsa_daemon alsa_client t1.cfg t2.cfg live.conf
echo "complete"
