
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

all: SMS-Demo-Preset-1

# Build folder
$(BUILD):
	$(MKDIR) -p $(BUILD)

# updated is used to ensure 'sudo apt update' has been 
# executed before installing any packages with apt 
$(BUILD)/updated: $(BUILD)
	sudo $(APT) update
	touch $(BUILD)/updated

# install dependencies of neural-amp-modeler-lv2
$(BUILD)/neural-amp-modeler-lv2.deps: $(BUILD)/updated
	sudo $(APT) install -y $(GIT)
	sudo $(SNAP) install $(CMAKE) --classic
	touch $(BUILD)/neural-amp-modeler-lv2.deps

# build & install neural-amp-modeler-lv2
$(BUILD)/neural-amp-modeler-lv2.created: $(BUILD)/neural-amp-modeler-lv2.deps
	$(GIT) submodule update --init --recursive $(BUILD)/neural-amp-modeler-lv2
	$(CD) $(BUILD)/neural-amp-modeler-lv2/build ; $(CMAKE) .. -DCMAKE_BUILD_TYPE="Release" -DUSE_NATIVE_ARCH=ON ; $(MAKE)
	sudo $(CP) -r $(BUILD)/neural-amp-modeler-lv2/build/neural_amp_modeler.lv2 /usr/lib/lv2/
	touch $(BUILD)/neural-amp-modeler-lv2.created

# install dependencies of neural-amp-modeler-ui
$(BUILD)/neural-amp-modeler-ui.deps: $(BUILD)/updated
	sudo $(APT) install -y libcairo2-dev libx11-dev lv2-dev pkg-config
	touch $(BUILD)/neural-amp-modeler-ui.deps

# build & install neural-amp-modeler-ui
$(BUILD)/neural-amp-modeler-ui.created: $(BUILD)/neural-amp-modeler-ui.deps $(BUILD)/neural-amp-modeler-lv2.created
	$(GIT) submodule update --init --recursive $(BUILD)/neural-amp-modeler-ui
	$(CD) $(BUILD)/neural-amp-modeler-ui ; $(MAKE) ; sudo $(MAKE) install
	touch $(BUILD)/neural-amp-modeler-ui.created

# recipe to ensure NAM-models submodule has been fetched
$(BUILD)/NAM-models.fetched: $(BUILD)
	$(GIT) submodule update --init NAM_models
	touch $(BUILD)/NAM-models.fetched

# recipe to ensure Speaker-Cabinets-IRs submodule has been fetched
$(BUILD)/Speaker-Cabinets-IRs.fetched: $(BUILD)
	$(GIT) submodule update --init Speaker-Cabinets-IRs
	touch $(BUILD)/Speaker-Cabinets-IRs.fetched

# install dependencies of GxPlugins.lv2
$(BUILD)/GxPlugins.lv2.deps: $(BUILD)/updated
	sudo $(APT) install -y libc6-dev libcairo2-dev libx11-dev x11proto-dev lv2-dev pkg-config
	touch $(BUILD)/GxPlugins.lv2.deps

# build & install GxPlugins.lv2
$(BUILD)/GxPlugins.lv2.created: $(BUILD)/GxPlugins.lv2.deps
	$(GIT) submodule update --init --recursive $(BUILD)/GxPlugins.lv2
	$(CD) $(BUILD)/GxPlugins.lv2 ; $(MAKE) ; sudo $(MAKE) install
	touch $(BUILD)/GxPlugins.lv2.created

# setup pipewire to 128 buffersize. This is needed to achieve reasonable latency.
$(BUILD)/setup-pipewire: $(BUILD)
	pw-metadata -n settings 0 clock.force-quantum 128
	touch $(BUILD)/setup-pipewire

# install calf-plugins with apt
$(BUILD)/calf-plugins.installed: $(BUILD)/updated
	sudo $(APT) install -y calf-plugins
	touch $(BUILD)/calf-plugins.installed

# install Carla with apt
$(BUILD)/Carla.installed: $(BUILD)/updated
	sudo $(APT) install -y carla
	touch $(BUILD)/Carla.installed

# SMS-Essentials:
#  - Neural Amp Modeler with UI installed
#  - Bunch of NAM Models fetched
#  - Bunch of Impuse Responses fetched
#  - GxPlugins installed
#  - Calf Studio Gear installed
#  - PipeWire configured for 128 buffer size
SMS-Essentials: $(BUILD)/calf-plugins.installed $(BUILD)/neural-amp-modeler-ui.created $(BUILD)/GxPlugins.lv2.created $(BUILD)/Carla.installed $(BUILD)/NAM-models.fetched $(BUILD)/Speaker-Cabinets-IRs.fetched $(BUILD)/setup-pipewire
	@echo
	@echo "SMS-Essentials Package Installed:"
	@echo "- Neural Amp Modeler with UI installed"
	@echo "- Bunch of NAM Models fetched"
	@echo "- GxPlugins installed"
	@echo "- Calf Studio Gear installed"
	@echo "- PipeWire configured for 128 buffer size"
	@echo
	@echo "ROCK ON \,,/__(><)__\,,/"
	@echo

# Create Demo-Preset-1
$(BUILD)/SMS-Demo-Preset-1.deps: SMS-Essentials
	$(RM) -rf SMS-Demo-Preset-1
	$(MKDIR) -p SMS-Demo-Preset-1
	$(MKDIR) -p SMS-Demo-Preset-1/Carla
	$(MKDIR) -p SMS-Demo-Preset-1/Carla/"x42 - IR Convolver Mono => Stereo"
	$(LN) -s ../../../Speaker-Cabinets-IRs/"Original 3 Impulses"/"GuitarHack Original Edge.wav" SMS-Demo-Preset-1/Carla/"x42 - IR Convolver Mono => Stereo"/
	$(MKDIR) -p SMS-Demo-Preset-1/Carla/"Neural Amp Modeler"	
	find NAM_models -name \*.nam -exec ln -vs ../../../"{}" SMS-Demo-Preset-1/Carla/"Neural Amp Modeler"/ ';'
	$(CP) SMS-Demo-Preset-1.carxp SMS-Demo-Preset-1/
	touch $(BUILD)/SMS-Demo-Preset-1.deps
	
SMS-Essentials-Demo:  $(BUILD)/SMS-Demo-Preset-1.deps
	carla SMS-Demo-Preset-1/SMS-Demo-Preset-1.carxp &


clean:
	@echo "Sweep...sweeeeep... yea sorry just clean it yourself"

	
.PHONY: clean SMS-Essentials-Demo SMS-Essentials
