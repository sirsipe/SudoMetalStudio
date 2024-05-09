
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

all: SMS-Essentials-Demo

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
    echo -n "$$selected_device" > $(STATUS)/audio-dev ; \
	pw-dump | jq --arg device "$$selected_device" '.[] | select(.type == "PipeWire:Interface:Node") | .info.props | select(."node.description" == $$device and ."api.alsa.pcm.stream" == "capture" ) | ."audio.position"' | cut -d ',' -f1 | tr -d '"\n' | awk '{print "capture_" $$0}' > $(STATUS)/audio-dev-in1 ; \
	pw-dump | jq --arg device "$$selected_device" '.[] | select(.type == "PipeWire:Interface:Node") | .info.props | select(."node.description" == $$device and ."api.alsa.pcm.stream" == "capture" ) | ."audio.position"' | cut -d ',' -f2 | tr -d '"\n' | awk '{print "capture_" $$0}' > $(STATUS)/audio-dev-in2 ; \
	pw-dump | jq --arg device "$$selected_device" '.[] | select(.type == "PipeWire:Interface:Node") | .info.props | select(."node.description" == $$device and ."api.alsa.pcm.stream" == "playback" ) | ."audio.position"' | cut -d ',' -f1 | tr -d '"\n' | awk '{print "playback_" $$0}' > $(STATUS)/audio-dev-out1 ; \
	pw-dump | jq --arg device "$$selected_device" '.[] | select(.type == "PipeWire:Interface:Node") | .info.props | select(."node.description" == $$device and ."api.alsa.pcm.stream" == "playback" ) | ."audio.position"' | cut -d ',' -f2 | tr -d '"\n' | awk '{print "playback_" $$0}' > $(STATUS)/audio-dev-out2

# recipe to ensure NAM-models submodule has been fetched
$(STATUS)/nam-models-fetched: $(STATUS)
	@echo
	@echo "Fetching 'NAM_models'..."
	@echo
	@$(GIT) submodule update --init NAM_models
	@touch $(STATUS)/nam-models-fetched

# recipe to ensure Speaker-Cabinets-IRs submodule has been fetched
$(STATUS)/irs-fetched:
	@echo
	@echo "Fetching 'Speaker-Cabinets-IRs'..."
	@echo
	@$(GIT) submodule update --init Speaker-Cabinets-IRs
	@touch $(STATUS)/irs-fetched

# Configure pipewire to 128 buffersize. This is needed to achieve reasonable latency.
$(STATUS)/pipewire-configured: $(STATUS)
	@echo
	@echo "Configuring PipeWire..."
	@echo
	@pw-metadata -n settings 0 clock.quantum 128
	@pw-metadata -n settings 0 clock.rate 48000
	@systemctl --user restart pipewire.service
	@touch $(STATUS)/pipewire-configured

# apt-updated is used to ensure 'sudo apt update' has been 
# executed before installing any packages with apt 
$(STATUS)/apt-updated: $(STATUS)
	@echo
	@echo "Updating package lists..."
	@echo
	@sudo $(APT) update
	@touch $(STATUS)/apt-updated

# install dependencies of neural-amp-modeler-lv2
$(STATUS)/nam-deps: $(STATUS)/apt-updated
	@echo
	@echo "Installing 'neural-amp-modeler-lv2' dependencies..."
	@echo
	@sudo $(APT) install -y $(GIT)
	@sudo $(SNAP) install $(CMAKE) --classic
	@touch $(STATUS)/nam-deps

# install dependencies of neural-amp-modeler-ui
$(STATUS)/nam-ui-deps: $(STATUS)/apt-updated
	@echo
	@echo "Installing 'neural-amp-modeler-ui' dependencies..."
	@echo
	@sudo $(APT) install -y $(GIT) libcairo2-dev libx11-dev lv2-dev pkg-config
	@touch $(STATUS)/nam-ui-deps

# install dependencies of GxPlugins.lv2
$(STATUS)/gxplugins-deps: $(STATUS)/apt-updated
	@echo
	@echo "Installing 'GxPlugins.lv2' dependencies..."
	@echo
	@sudo $(APT) install -y libc6-dev libcairo2-dev libx11-dev x11proto-dev lv2-dev pkg-config
	@touch $(STATUS)/gxplugins-deps


# build & install neural-amp-modeler-lv2
$(STATUS)/nam-installed: $(STATUS)/nam-deps
	@echo
	@echo "Fetching 'neural-amp-modeler-lv2'..."
	@echo
	@$(GIT) submodule update --init --recursive $(BUILD)/neural-amp-modeler-lv2
	@echo
	@echo "Building 'neural-amp-modeler-lv2'..."
	@echo
	@$(CD) $(BUILD)/neural-amp-modeler-lv2/build ; $(CMAKE) .. -DCMAKE_BUILD_TYPE="Release" -DUSE_NATIVE_ARCH=ON ; $(MAKE)
	@echo
	@echo "Installing 'neural-amp-modeler-lv2'..."
	@echo
	@sudo $(CP) -r $(BUILD)/neural-amp-modeler-lv2/build/neural_amp_modeler.lv2 /usr/lib/lv2/
	@touch $(STATUS)/nam-installed

# build & install neural-amp-modeler-ui
$(STATUS)/nam-ui-installed: $(STATUS)/nam-ui-deps $(STATUS)/nam-installed
	@echo
	@echo "Fetching 'neural-amp-modeler-ui'..."
	@echo
	@$(GIT) submodule update --init --recursive $(BUILD)/neural-amp-modeler-ui
	@echo
	@echo "Building 'neural-amp-modeler-ui'..."
	@echo
	@$(CD) $(BUILD)/neural-amp-modeler-ui ; $(MAKE)
	@echo
	@echo "Installing 'neural-amp-modeler-ui'..."
	@echo
	@$(CD) $(BUILD)/neural-amp-modeler-ui ; sudo $(MAKE) install
	@touch $(STATUS)/nam-ui-installed


# build & install GxPlugins.lv2
gxplugins: $(STATUS)/gxplugins-deps
	@echo
	@echo "Fetching 'GxPlugins.lv2'..."
	@echo
	@$(GIT) submodule update --init --recursive $(BUILD)/GxPlugins.lv2
	@echo
	@echo "Building 'GxPlugins.lv2' (this takes a while)..."
	@echo
	@$(CD) $(BUILD)/GxPlugins.lv2 ; $(MAKE)
	@echo
	@echo "Installing 'GxPlugins.lv2'..."
	@echo
	@$(CD) $(BUILD)/GxPlugins.lv2 ; sudo $(MAKE) install

# SMS-Essentials:
#  - Neural Amp Modeler with UI installed
#  - Bunch of NAM Models fetched
#  - Bunch of Impuse Responses fetched
#  - PipeWire configured for 128@48000
SMS-Essentials: \
			$(STATUS)/nam-installed \
			$(STATUS)/nam-ui-installed \
			$(STATUS)/nam-models-fetched \
			$(STATUS)/irs-fetched \
			$(STATUS)/pipewire-configured
	@echo
	@echo "SMS-Essentials Package Installed:"
	@echo "- Neural Amp Modeler with UI installed"
	@echo "- Bunch of NAM Models fetched"
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
$(STATUS)/preset-1-deps: $(STATUS)/audio-dev \
			$(STATUS)/nam-installed \
			$(STATUS)/nam-ui-installed \
			$(STATUS)/nam-models-fetched \
			$(STATUS)/irs-fetched \
			$(STATUS)/pipewire-configured
	@echo
	@echo "Creating Carla Preset with"
	@echo "YOUR GUITAR ->"
	@echo "	-> ZamGate"
	@echo "	-> Neural Amp Modeler (Loaded: 'Helga B 6505+ Red ch - MXR Drive V2', but all models selectable)"
	@echo "	-> x42 - IR Convolver Mono => Stereo (Loaded: 'GuitarHack Original Edge')"
	@echo "YOUR EARS <-"
	@echo
	@$(RM) -rf SMS-Demo-Preset-1
	@$(MKDIR) -p SMS-Demo-Preset-1
	@$(MKDIR) -p SMS-Demo-Preset-1/Carla
	@$(MKDIR) -p SMS-Demo-Preset-1/Carla/"x42 - IR Convolver Mono => Stereo"
	@$(LN) -s ../../../Speaker-Cabinets-IRs/"Original 3 Impulses"/"GuitarHack Original Edge.wav" SMS-Demo-Preset-1/Carla/"x42 - IR Convolver Mono => Stereo"/
	@$(MKDIR) -p SMS-Demo-Preset-1/Carla/"Neural Amp Modeler"	
	@$(FIND) NAM_models -name \*.nam -exec $(LN) -vs ../../../"{}" SMS-Demo-Preset-1/Carla/"Neural Amp Modeler"/ ';'
	@$(CP) SMS-Demo-Preset-1.carxp SMS-Demo-Preset-1/
	@selectedDevice=$$(cat $(STATUS)/audio-dev); \
	in1=$$(cat $(STATUS)/audio-dev-in1); \
	in2=$$(cat $(STATUS)/audio-dev-in2); \
	out1=$$(cat $(STATUS)/audio-dev-out1); \
	out2=$$(cat $(STATUS)/audio-dev-out2); \
	$(SED) -i "s/{CAPTURE_INPUT_1}/$$selectedDevice:$$in1/g" SMS-Demo-Preset-1/SMS-Demo-Preset-1.carxp; \
	$(SED) -i "s/{CAPTURE_INPUT_2}/$$selectedDevice:$$in2/g" SMS-Demo-Preset-1/SMS-Demo-Preset-1.carxp; \
	$(SED) -i "s/{PLAYBACK_OUTPUT_1}/$$selectedDevice:$$out1/g" SMS-Demo-Preset-1/SMS-Demo-Preset-1.carxp; \
	$(SED) -i "s/{PLAYBACK_OUTPUT_2}/$$selectedDevice:$$out2/g" SMS-Demo-Preset-1/SMS-Demo-Preset-1.carxp;
	@touch $(STATUS)/preset-1-deps
	
SMS-Essentials-Demo: $(STATUS)/preset-1-deps
	@carla SMS-Demo-Preset-1/SMS-Demo-Preset-1.carxp &


clean:
	@echo "Sweep...sweeeeep... yea sorry just clean it yourself"

	
.PHONY: clean SMS-Essentials-Demo SMS-Essentials gxplugins
