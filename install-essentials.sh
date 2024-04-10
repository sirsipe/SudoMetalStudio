#!/bin/sh

apt-get update
apt-get install -y cmake libcairo2-dev libx11-dev lv2-dev libc6-dev x11proto-dev pkg-config

ORIG_USR=$(logname)

# Temporary working dir
mkdir ez-studio-temp
cd ez-studio-temp

# Get Neural Amp Modeler
git clone --recurse-submodules -j4 https://github.com/mikeoliphant/neural-amp-modeler-lv2
cd neural-amp-modeler-lv2/build
cmake .. -DCMAKE_BUILD_TYPE="Release" -DUSE_NATIVE_ARCH=ON
make -j4
cp -r neural_amp_modeler.lv2 /usr/lib/lv2/
cd ../..

# Get UI for Neural Amp Modeler
git clone https://github.com/brummer10/neural-amp-modeler-ui
cd neural-amp-modeler-ui
git submodule init
git submodule update
make
make install
cd ..

# Install GxPlugins
git clone https://github.com/brummer10/GxPlugins.lv2
cd GxPlugins.lv2
git submodule init
git submodule update
make
make install
cd ..

# Exit working folder and remove it
cd ..
rm -rf ez-studio-temp

# Get NAM Models
git clone https://github.com/pelennor2170/NAM_models
chown -R $ORIG_USR:$ORIG_USR NAM_models

# Get Some IRs
git clone https://github.com/rodamaralgeo/Speaker-Cabinets-IRs
chown -R $ORIG_USR:$ORIG_USR Speaker-Cabinets-IRs

# Prepare Preset Paths for Carla.
mkdir Carla
mkdir Carla/"LV2 Convolution Mono=>Stereo"
ln -s ../../Speaker-Cabinets-IRs/"Original 3 Impulses"/"GuitarHack Original Edge.wav" Carla/"LV2 Convolution Mono=>Stereo"/
mkdir Carla/"Neural Amp Modeler"
ln -s ../../NAM_models/"Helga B 6505+ Red ch - MXR Drive V2.nam" Carla/"Neural Amp Modeler"/
chown -R $ORIG_USR:$ORIG_USR Carla

su -c "carla SMS-Preset.carxp &" $ORIG_USR
