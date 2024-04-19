
MAKE=make
APT=apt-get
SNAP=snap
CD=cd
CMAKE=cmake
GIT=git
CP=cp
RM=rm
MKDIR=mkdir
LN=ln
BUILD=.build
STATUS=.makestatus
FIND=find
SED=sed

all: SMS-Essentials

# Status folder
$(STATUS):
	@$(MKDIR) -p $(STATUS)

# This recipe utilizes pactl to obtain possible audio device names.
# Those are needed to replace I/O connections of the Carla presets
# with valid ones.
# THIS IS NOT READY YET. Device name works but also device input/output ports
# might be named differently.
$(STATUS)/audio-dev: $(STATUS)
	@devices=$$(pactl list sources | grep Description: | grep -v "Monitor of " | awk -F ': ' '{print $$2}'); \
	if [ $$(echo "$$devices" | wc -l) -eq 1 ]; then \
		selected_device=$$(echo "$$devices"); \
		if [ -z "$$selected_device" ]; then \
			echo ; \
			echo "ERROR: No couldn't find any audio devices :("; \
			echo ; \
			exit 1; \
        fi; \
	else \
		echo ; \
    	echo "Which one looks like your primary Audio Device?"; \
		echo ; \
    	echo "$$devices" | cat -n; \
    	echo ; \
		echo -n "Number: "; \
    	read choice; \
    	echo ;\
    	selected_device=$$(echo "$$devices" | $(SED) -n "$$choice p"); \
	fi; \
    echo "Selected Audio Device for Demo presets: $$selected_device"; \
    echo -n "$$selected_device" > $(STATUS)/audio-dev

# recipe to ensure NAM-models submodule has been fetched
$(STATUS)/nam-models.fetched: $(STATUS)
	@echo "Fetching 'NAM_models'..."
	@$(GIT) submodule update --init NAM_models > /dev/null
	@touch $(STATUS)/nam-models.fetched

# recipe to ensure Speaker-Cabinets-IRs submodule has been fetched
$(STATUS)/speaker-cabinets-irs.fetched: $(STATUS)
	@echo "Fetching 'Speaker-Cabinets-IRs'..."
	@$(GIT) submodule update --init Speaker-Cabinets-IRs > /dev/null
	@touch $(STATUS)/speaker-cabinets-irs.fetched

# Configure pipewire to 128 buffersize. This is needed to achieve reasonable latency.
$(STATUS)/pipewire.configured: $(STATUS)
	@echo "Configuring PipeWire..."
	@pw-metadata -n settings 0 clock.force-quantum 128 > /dev/null
	@touch $(STATUS)/pipewire.configured

# updated is used to ensure 'sudo apt update' has been 
# executed before installing any packages with apt 
$(STATUS)/updated: $(STATUS)
	@echo "Updating package lists..."
	@sudo $(APT) update > /dev/null
	@touch $(STATUS)/updated

# install calf-plugins with apt
$(STATUS)/calf-plugins.installed: $(STATUS)/updated
	@echo "Installing 'Calf Studio Gear'..."
	@sudo $(APT) install -y calf-plugins > /dev/null
	@touch $(STATUS)/calf-plugins.installed

# install Carla with apt
$(STATUS)/carla.installed: $(STATUS)/updated
	@echo "Installing 'Carla'..."
	@sudo $(APT) install -y carla > /dev/null
	@touch $(STATUS)/carla.installed
	
# install dependencies of neural-amp-modeler-lv2
$(STATUS)/neural-amp-modeler-lv2.deps: $(STATUS)/updated
	@echo "Installing 'neural-amp-modeler-lv2' dependencies..."
	@sudo $(APT) install -y $(GIT) > /dev/null
	@sudo $(SNAP) install $(CMAKE) --classic > /dev/null
	@touch $(STATUS)/neural-amp-modeler-lv2.deps

# install dependencies of neural-amp-modeler-ui
$(STATUS)/neural-amp-modeler-ui.deps: $(STATUS)/updated
	@echo "Installing 'neural-amp-modeler-ui' dependencies..."
	@sudo $(APT) install -y $(GIT) libcairo2-dev libx11-dev lv2-dev pkg-config > /dev/null
	@touch $(STATUS)/neural-amp-modeler-ui.deps

# install dependencies of GxPlugins.lv2
$(STATUS)/gxplugins.lv2.deps: $(STATUS)/updated
	@echo "Installing 'GxPlugins.lv2' dependencies..."
	@sudo $(APT) install -y libc6-dev libcairo2-dev libx11-dev x11proto-dev lv2-dev pkg-config > /dev/null
	@touch $(STATUS)/gxplugins.lv2.deps


# build & install neural-amp-modeler-lv2
$(STATUS)/neural-amp-modeler-lv2.installed: $(STATUS)/neural-amp-modeler-lv2.deps
	@echo "Fetching 'neural-amp-modeler-lv2'..."
	@$(GIT) submodule update --init --recursive $(BUILD)/neural-amp-modeler-lv2 > /dev/null
	@echo "Building 'neural-amp-modeler-lv2'..."
	@$(CD) $(BUILD)/neural-amp-modeler-lv2/build ; $(CMAKE) .. -DCMAKE_BUILD_TYPE="Release" -DUSE_NATIVE_ARCH=ON > /dev/null ; $(MAKE) > /dev/null
	@echo "Installing 'neural-amp-modeler-lv2'..."
	@sudo $(CP) -r $(BUILD)/neural-amp-modeler-lv2/build/neural_amp_modeler.lv2 /usr/lib/lv2/ > /dev/null
	@touch $(STATUS)/neural-amp-modeler-lv2.installed

# build & install neural-amp-modeler-ui
$(STATUS)/neural-amp-modeler-ui.installed: $(STATUS)/neural-amp-modeler-ui.deps $(STATUS)/neural-amp-modeler-lv2.installed
	@echo "Fetching 'neural-amp-modeler-ui'..."
	@$(GIT) submodule update --init --recursive $(BUILD)/neural-amp-modeler-ui > /dev/null
	@echo "Building 'neural-amp-modeler-ui'..."
	@$(CD) $(BUILD)/neural-amp-modeler-ui ; $(MAKE) > /dev/null
	@echo "Installing 'neural-amp-modeler-ui'..."
	@$(CD) $(BUILD)/neural-amp-modeler-ui ; sudo $(MAKE) install > /dev/null
	@touch $(STATUS)/neural-amp-modeler-ui.installed


# build & install GxPlugins.lv2
$(STATUS)/gxplugins.lv2.installed: $(STATUS)/gxplugins.lv2.deps
	@echo "Fetching 'GxPlugins.lv2'..."
	@$(GIT) submodule update --init --recursive $(BUILD)/GxPlugins.lv2 > /dev/null
	@echo "Building 'GxPlugins.lv2' (this takes a while)..."
	@$(CD) $(BUILD)/GxPlugins.lv2 ; $(MAKE) > /dev/null
	@echo "Installing 'GxPlugins.lv2'..."
	@$(CD) $(BUILD)/GxPlugins.lv2 ; sudo $(MAKE) install > /dev/null
	@touch $(STATUS)/gxplugins.lv2.installed


# SMS-Essentials:
#  - Neural Amp Modeler with UI installed
#  - Bunch of NAM Models fetched
#  - Bunch of Impuse Responses fetched
#  - GxPlugins installed
#  - Carla installed
#  - Calf Studio Gear installed
#  - PipeWire configured for 128 buffer size
SMS-Essentials: \
			$(STATUS)/neural-amp-modeler-lv2.installed \
			$(STATUS)/neural-amp-modeler-ui.installed \
			$(STATUS)/carla.installed \
			$(STATUS)/nam-models.fetched \
			$(STATUS)/speaker-cabinets-irs.fetched \
			$(STATUS)/gxplugins.lv2.installed \
			$(STATUS)/calf-plugins.installed \
			$(STATUS)/pipewire.configured
	@echo
	@echo "SMS-Essentials Package Installed:"
	@echo "- Neural Amp Modeler with UI installed"
	@echo "- Bunch of NAM Models fetched"
	@echo "- GxPlugins installed"
	@echo "- Carla installed"
	@echo "- Calf Studio Gear installed"
	@echo "- PipeWire configured for 128 buffer size"
	@echo
	@echo "If you wish, you can now copy 'NAM_Models' and 'Speaker-Cabinets-IRs' folders"
	@echo "to anywhere you like, and delete the whole 'SudoMetalStudio' repository."
	@echo 
	@echo "QUICK START: Just plugin you guitar to the first input of your Audio Interface,"
	@echo "cover your ears, and execute 'make SMS-Essentials-Demo'"
	@echo 
	@echo "ROCK ON \,,/__(><)__\,,/"
	@echo



# Create Demo-Preset-1
$(STATUS)/demo-preset-1.deps: $(STATUS)/audio-dev \
			$(STATUS)/neural-amp-modeler-lv2.installed \
			$(STATUS)/neural-amp-modeler-ui.installed \
			$(STATUS)/carla.installed \
			$(STATUS)/nam-models.fetched \
			$(STATUS)/speaker-cabinets-irs.fetched \
			$(STATUS)/gxplugins.lv2.installed \
			$(STATUS)/pipewire.configured
	@echo
	@echo "Creating Carla Preset with"
	@echo "YOUR GUITAR ->"
	@echo "	-> ZamGate"
	@echo "	-> Neural Amp Modeler (Loaded: 'Helga B 6505+ Red ch - MXR Drive V2', but all models selectable)"
	@echo "	-> x42 - IR Convolver Mono => Stereo (Loaded: 'GuitarHack Original Edge')"
	@echo "	-> GxChorus Stereo"
	@echo "	-> GxDigital Delay Stereo (disabled)"
	@echo "	-> GxReverb"
	@echo "YOUR EARS <-"
	@echo
	@$(RM) -rf SMS-Demo-Preset-1
	@$(MKDIR) -p SMS-Demo-Preset-1
	@$(MKDIR) -p SMS-Demo-Preset-1/Carla
	@$(MKDIR) -p SMS-Demo-Preset-1/Carla/"x42 - IR Convolver Mono => Stereo"
	@$(LN) -s ../../../Speaker-Cabinets-IRs/"Original 3 Impulses"/"GuitarHack Original Edge.wav" SMS-Demo-Preset-1/Carla/"x42 - IR Convolver Mono => Stereo"/ > /dev/null
	@$(MKDIR) -p SMS-Demo-Preset-1/Carla/"Neural Amp Modeler"	
	@$(FIND) NAM_models -name \*.nam -exec $(LN) -vs ../../../"{}" SMS-Demo-Preset-1/Carla/"Neural Amp Modeler"/ ';' > /dev/null
	@$(CP) SMS-Demo-Preset-1.carxp SMS-Demo-Preset-1/
	@selectedDevice=$$(cat $(STATUS)/audio-dev); \
	$(SED) -i "s/system:capture_1/$$selectedDevice:capture_AUX0/g" SMS-Demo-Preset-1/SMS-Demo-Preset-1.carxp; \
	$(SED) -i "s/system:capture_2/$$selectedDevice:capture_AUX1/g" SMS-Demo-Preset-1/SMS-Demo-Preset-1.carxp; \
	$(SED) -i "s/system:playback_1/$$selectedDevice:playback_AUX0/g" SMS-Demo-Preset-1/SMS-Demo-Preset-1.carxp; \
	$(SED) -i "s/system:playback_2/$$selectedDevice:playback_AUX1/g" SMS-Demo-Preset-1/SMS-Demo-Preset-1.carxp;
	@touch $(STATUS)/demo-preset-1.deps
	
SMS-Essentials-Demo: $(STATUS)/demo-preset-1.deps
	@carla SMS-Demo-Preset-1/SMS-Demo-Preset-1.carxp > /dev/null &


clean:
	@echo "Sweep...sweeeeep... yea sorry just clean it yourself"

	
.PHONY: clean SMS-Essentials-Demo SMS-Essentials
