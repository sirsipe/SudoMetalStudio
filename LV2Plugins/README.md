# General

**!!! WORK IN PROGRESS !!!**

Plugins in this repo are tested with Carla and Ardour unless otherwise stated.

## Dependencies (debian / ubuntu)

    sudo apt-get install build-essential
    sudo apt-get install pkg-config lv2-dev libsndfile1-dev libx11-dev libcairo2-dev

## Build and install

You can build and install all plugins with following:
 
    make
    make install

Or you can build and install individual plugins;

    make <name>
    make install-<name> 

Individual plugins can also be uninstalled

    make uninstall-<name>

For example
    make SMSAmateurDelay
    make install-SMSAmateurDelay
    make uninstall-SMSAmateurDelay


# Plugins
## SMSAmateurDelay

*LADIES AND GENTLEMEN! The first ever SudoMetalStudio LV2 Plugin has arrived!*
Thus also it's named *SudoMetalStudio *Amateur* Delay*, as I have absolutely no idea if its implementation is done as it "should". 

It has a variable delay time, variable decay, and varible level. And it's real-time. My amateur opion is that it is as good as it gets.

## LV2Neuro
    
Future attempt to create LSTM NN based DSP. Currently just a learning playground.
    
