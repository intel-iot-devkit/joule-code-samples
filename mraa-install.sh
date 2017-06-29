#!/bin/bash
#Installing Mraa

clear
echo "Beginning install!"
sleep 1
mkdir buildMraa
cd buildMraa
checkCmake="1"
#Check if Cmake exists
command -v cmake >/dev/null 2>&1 || { echo >&2 "MRAA requires Cmake, Installing Cmake!"; checkCmake="0"; }
if [ "$checkCmake" = "0" ]; then #Have to install Cmake
        sleep 1
        git clone https://github.com/Kitware/CMake.git
        cd CMake
        ./bootstrap
        make
        make install
        cd ..
        clear
        echo "CMake installed! Preparing to build Mraa."
        sleep 1
fi
echo "CMake already installed, preparing to build Mraa."
sleep 1
#Remove previous version of Mraa
rm /usr/lib/libmraa.so* 
rm /usr/lib/pkgconfig/mraa.pc
#Add new mraa version
git clone https://github.com/intel-iot-devkit/mraa.git
cd mraa
mkdir build
cd build
cmake .. -DCMAKE_INSTALL_PREFIX:PATH=/usr -DCMAKE_INSTALL_LIBDIR=lib
make
make install #Should install Mraa in /usr/lib/
#Cleanup
cd ../../../
rm -r buildMraa
clear
echo $'Install complete!\n'
mraa-gpio version
