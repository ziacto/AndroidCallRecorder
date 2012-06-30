su
mount -o remount /dev/block/mtdblock0 /system
mount -o remount /dev/block/mtdblock1 /data
cd /data
mkdir tmp
cd /system/usr/share
mkdir alsa
cd ./alsa
mkdir pcm
mkdir cards
cd /data/data/org.footoo.android.callrecorder/files/
cat ./libasound.so > /system/lib/libasound.so
cat ./alsa_amixer > /system/xbin/alsa_amixer
cat ./alsa_aplay > /system/xbin/alsa_aplay
cat ./alsa_ctl > /system/xbin/alsa_ctl
cat ./alsa_client > /data/tmp/alsa_client
cat ./alsa_daemon > /data/tmp/alsa_daemon
cat ./live.conf > /data/tmp/live.conf
cat ./t1.cfg > /data/tmp/t1.cfg
cat ./t2.cfg > /data/tmp/t2.cfg
cat ./pcm2wav > /data/tmp/pcm2wav
cat ./aliases.conf > /system/usr/share/alsa/cards/aliases.conf
cat ./alsa.conf > /system/usr/share/alsa/alsa.conf
cat ./center_lfe.conf > /system/usr/share/alsa/pcm/center_lfe.conf
cat ./default.conf > /system/usr/share/alsa/pcm/default.conf
cat ./dmix.conf > /system/usr/share/alsa/pcm/dmix.conf
cat ./dpl.conf > /system/usr/share/alsa/pcm/dpl.conf
cat ./dsnoop.conf > /system/usr/share/alsa/pcm/dsnoop.conf
cat ./front.conf > /system/usr/share/alsa/pcm/front.conf
cat ./iec958.conf > /system/usr/share/alsa/pcm/iec958.conf
cat ./modem.conf > /system/usr/share/alsa/pcm/modem.conf
cat ./rear.conf > /system/usr/share/alsa/pcm/rear.conf
cat ./side.conf > /system/usr/share/alsa/pcm/side.conf
cat ./surround40.conf > /system/usr/share/alsa/pcm/surround40.conf
cat ./surround41.conf > /system/usr/share/alsa/pcm/surround41.conf
cat ./surround41.conf > /system/usr/share/alsa/pcm/surround50.conf
cat ./surround51.conf > /system/usr/share/alsa/pcm/surround51.conf
cat ./surround71.conf > /system/usr/share/alsa/pcm/surround71.conf
cd /system/xbin
chmod 775 alsa_amixer alsa_aplay alsa_ctl
cd /data/tmp
chmod 775 alsa_daemon alsa_client t1.cfg t2.cfg live.conf pcm2wav