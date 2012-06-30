echo "compiling kernel..."
#set cross_compile environment
export ARCH=arm
export SUBARCH=arm
export CROSS_COMPILE=arm-eabi-
cd ./kernel
make herring_defconfig
make
#compiling android source, here version is 4.0.3
echo "compiling source..."
cd ../
rm ./android_source/out/target/product/crespo/kernel
cp ./kernel/arch/arm/boot/zImage ./android_source/out/target/product/crespo/
mv ./android_source/out/target/product/crespo/zImage ./android_source/out/target/product/crespo/kernel
cd ./android_source
. build/envsetup.sh
lunch full_crespo-userdebug
make
cd ..
#make ROM
rm -rf ./update/system ./update/boot.img
echo "copy system..."
cp -rf ./android_source/out/target/product/crespo/system ./update
echo "copy boot.img..."
cp ./android_source/out/target/product/crespo/boot.img ./update
cd ./update
rm up.zip update.zip
echo "zip update.zip..."
zip up.zip -r META-INF/ boot.img data/ system/
echo "sign..."
java -classpath testsign.jar testsign up.zip update.zip
echo "finished!"
