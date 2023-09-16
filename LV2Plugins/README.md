# General

**!!! WORK IN PROGRESS !!!**

Plugins in this repo are tested with Carla and Ardour unless otherwise stated.

## Dependencies (debian / ubuntu)

    sudo apt-get install build-essential xxd
    sudo apt-get install pkg-config lv2-dev libx11-dev libpng-dev

## Build and install

You can build and install all plugins with following:
 
    make
    make install

Or you can build and install individual plugins:

    make <name>
    make install-<name> 

Individual plugins can also be uninstalled:

    make uninstall-<name>


# Plugins
## SMS Northern Perkele (Work in Progress!)

**Distortion / Amp! *Rad AF*!** Made to slaugther your enemies, friends, and puppies without mercy.

!! Pair with cabinet, e.g., *LV2 Convolution* with any half-decent impulse response !!

    make SMSNorthernPerkele
    make install-SMSNorthernPerkele

## SMS Stereo Delay

Based on the world famous *SMS Amateur Delay*, but with stereo output and separate L/R delays.

Protip: *SMS Northern Perkele* + *[some cabinet sim]* + *SMS Stereo Delay* = profit!

    make SMSStereoDelay
    make install-SMSStereoDelay


## SMS Amateur Delay

*LADIES AND GENTLEMEN! The first ever SudoMetalStudio LV2 Plugin has arrived!*

Thus also it's named *"SMS **Amateur** Delay"*, as I have absolutely no idea if its implementation is done as it "should". 

It has a variable delay time, variable decay, and varible level. And it's real-time. My amateur opion is that it is as good as it gets.

    make SMSAmateurDelay
    make install-SMSAmateurDelay
 
## SMS 440Hz

Want to get constant 440Hz tone? Me neither, but at least we can now.

    make SMS440Hz
    make install-SMS440Hz

## SMS White Noise

*Hishshhhshshhshhshshshshshhsh.*

I used it to do spectrum analysis of my IIR filter implementations.

    make SMSWhiteNoise
    make install-SMSWhiteNoise

## SMS Switch

Simple 1-channel switch to either bypass or cut the signal. Extremely usefull when mapped to extenal MIDI controller!
For example: Use a midi footswitch for "push-to-talk" setup in Carla ;) 

    make SMSSwitch
    make install-SMSSwitch

## LV2Neuro
    
Future attempt to create LSTM NN based DSP. Currently just a learning playground.
    
