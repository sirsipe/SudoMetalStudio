
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
	echo '' > $(BUILD)/updated

# install dependencies of neural-amp-modeler-lv2
$(BUILD)/neural-amp-modeler-lv2.deps: $(BUILD)/updated
	sudo $(APT) install -y $(GIT)
	sudo $(SNAP) install $(CMAKE) --classic
	echo '' > $(BUILD)/neural-amp-modeler-lv2.deps

# build & install neural-amp-modeler-lv2
$(BUILD)/neural-amp-modeler-lv2: $(BUILD)/neural-amp-modeler-lv2.deps
	$(GIT) submodule update --init --recursive neural-amp-modeler-lv2
	$(CD) neural-amp-modeler-lv2/build ; $(CMAKE) .. -DCMAKE_BUILD_TYPE="Release" -DUSE_NATIVE_ARCH=ON ; $(MAKE)
	sudo $(CP) -r neural-amp-modeler-lv2/build/neural_amp_modeler.lv2 /usr/lib/lv2/
	echo '' > $(BUILD)/neural-amp-modeler-lv2

# install dependencies of neural-amp-modeler-ui
$(BUILD)/neural-amp-modeler-ui.deps: $(BUILD)/updated
	sudo $(APT) install -y libcairo2-dev libx11-dev lv2-dev pkg-config
	echo '' > $(BUILD)/neural-amp-modeler-ui.deps

# build & install neural-amp-modeler-ui
$(BUILD)/neural-amp-modeler-ui: $(BUILD)/neural-amp-modeler-ui.deps $(BUILD)/neural-amp-modeler-lv2
	$(GIT) submodule update --init --recursive neural-amp-modeler-ui
	$(CD) neural-amp-modeler-ui ; $(MAKE) ; sudo $(MAKE) install
	echo '' > $(BUILD)/neural-amp-modeler-ui

# recipe to ensure NAM-models submodule has been fetched
$(BUILD)/NAM-models.fetched: $(BUILD)
	$(GIT) submodule update --init NAM_models
	echo '' > $(BUILD)/NAM-models.fetched

# recipe to ensure Speaker-Cabinets-IRs submodule has been fetched
$(BUILD)/Speaker-Cabinets-IRs.fetched: $(BUILD)
	$(GIT) submodule update --init Speaker-Cabinets-IRs
	echo '' > $(BUILD)/Speaker-Cabinets-IRs.fetched

# install dependencies of GxPlugins.lv2
$(BUILD)/GxPlugins.lv2.deps: $(BUILD)/updated
	sudo $(APT) install -y libc6-dev libcairo2-dev libx11-dev x11proto-dev lv2-dev pkg-config
	echo '' > $(BUILD)/GxPlugins.lv2.deps

# build & install GxPlugins.lv2
$(BUILD)/GxPlugins.lv2: $(BUILD)/GxPlugins.lv2.deps
	$(GIT) submodule update --init --recursive GxPlugins.lv2
	$(CD) GxPlugins.lv2 ; $(MAKE) ; sudo $(MAKE) install
	echo '' > $(BUILD)/GxPlugins.lv2

# setup pipewire to 128 buffersize. This is needed to achieve reasonable latency.
$(BUILD)/setup-pipewire: $(BUILD)
	pw-metadata -n settings 0 clock.force-quantum 128
	echo '' > $(BUILD)/setup-pipewire

# install Carla with apt
$(BUILD)/Carla.deps: $(BUILD)/updated
	sudo $(APT) install -y carla
	echo '' > $(BUILD)/Carla.deps

# Create Demo-Preset-1
$(BUILD)/SMS-Demo-Preset-1.deps: $(BUILD)/neural-amp-modeler-ui $(BUILD)/NAM-models.fetched $(BUILD)/Speaker-Cabinets-IRs.fetched $(BUILD)/GxPlugins.lv2 $(BUILD)/Carla.deps
	$(MKDIR) -p SMS-Demo-Preset-1
	$(MKDIR) -p SMS-Demo-Preset-1/Carla
	$(MKDIR) -p SMS-Demo-Preset-1/Carla/"x42 - IR Convolver Mono => Stereo"
	$(LN) -s ../../../Speaker-Cabinets-IRs/"Original 3 Impulses"/"GuitarHack Original Edge.wav" SMS-Demo-Preset-1/Carla/"x42 - IR Convolver Mono => Stereo"/
	$(MKDIR) -p SMS-Demo-Preset-1/Carla/"Neural Amp Modeler"	
	find NAM_models -name \*.nam -exec ln -vs ../../../"{}" SMS-Demo-Preset-1/Carla/"Neural Amp Modeler"/ ';'
	$(CP) SMS-Demo-Preset-1.carxp SMS-Demo-Preset-1/
	echo '' > $(BUILD)/SMS-Demo-Preset-1.deps
	
SMS-Demo-Preset-1: $(BUILD)/SMS-Demo-Preset-1.deps $(BUILD)/setup-pipewire
	carla SMS-Demo-Preset-1/SMS-Demo-Preset-1.carxp &


clean:
	$(RM) -rf $(BUILD)
	$(CD) neural-amp-modeler-lv2 ; $(MAKE) clean
	$(CD) neural-amp-modeler-ui ; $(MAKE) clean
	$(CD) GxPlugins.lv2 ; $(MAKE) clean
	$(RM) -rf Speaker-Cabinets-IRs/*
	$(RM) -rf NAM_models/*
	$(RM) -rf SMS-Demo-Preset-1

	
.PHONY: clean SMS-Demo-Preset-1
