# Make Your Own Damn Plugin!

*MYODP* is a "template framework" that works as extremely simple entry point for entry level LV2 Plugin development. Simply follow the quick steps below and you will have your very own plugin running in no time.

My YouTube channel is a good place to learn more: https://www.youtube.com/@SudoMetalStudio

## Quick steps

To create a plugin named **MyAmazingPlugin** *(it has to be simple ascii letters, without spaces, and it must not start with a number)*.

    sudo apt-get install git build-essential pkg-config lv2-dev
    git clone https://github.com/sirsipe/SudoMetalStudio
    cd SudoMetalStudio/LV2Plugins
    make MYODP-Create-MyAmazingPlugin
    make MYODP-BuildAndInstall-MyAmazingPlugin

And you are done! You should find *MyAmazingPlugin* e.g., from Carla's and Ardour's plugins listing (it's installed to **~/.lv2/**). 

Now, open **src/MyAmazingPlugin/MyAmazingPlugin.cpp** with your favourite code editor, and take a look at **MyAmazingPlugin::run** function. Make your changes for the signal processing, and apply them with

    make MYODP-BuildAndInstall-MyAmazingPlugin

Then restart the plugin host application to test your changes.

## Quick steps Explained

### 1. Install required tools/libries and clone the repo

    sudo apt-get install git build-essential pkg-config lv2-dev
    git clone https://github.com/sirsipe/SudoMetalStudio


### 2. Come up with a name for you plugin

It has to be simple ascii letters, without spaces, and it must not start with a number. 

For example: **MyAmazingPlugin**
 

### 3. Initialize new codebase for your plugin. This process is automated based on the name you chose and a ready-made template:

    cd SudoMetalStudio/LV2Plugins
    make MYODP-Create-MyAmazingPlugin

Your plugin is now created, but not yet installed.


### 4. Investigate the *src/MyAmazingPlugin/MyAmazingPlugin.cpp* file

...and especially the **MyAmazingPlugin::run** function.

If you need more inputs/outputs, ports are defined in *src/MyAmazingPlugin/MyAmazingPlugin.ttl* and **MyAmazingPlugin::connectPort** function must handle connection to them.


### 5. Build and install *MyAmazingPlugin*

    make MYODP-BuildAndInstall-MyAmazingPlugin


## 6. GoTo 4 

*indefinitely*


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
    
