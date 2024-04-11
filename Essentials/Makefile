
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

all: neural-amp-modeler-lv2 neural-amp-modeler-ui NAM-models Speaker-Cabinets-IRs GxPlugins.lv2

update-packages:
	sudo $(APT) update

neural-amp-modeler-lv2: update-packages
	sudo $(APT) install -y $(GIT)
	sudo $(SNAP) install $(CMAKE) --classic
	$(GIT) submodule update --init --recursive neural-amp-modeler-lv2
	$(CD) neural-amp-modeler-lv2/build ; $(CMAKE) .. -DCMAKE_BUILD_TYPE="Release" -DUSE_NATIVE_ARCH=ON ; $(MAKE)
	sudo $(CP) -r neural-amp-modeler-lv2/build/neural_amp_modeler.lv2 /usr/lib/lv2/

neural-amp-modeler-ui: update-packages neural-amp-modeler-lv2
	sudo $(APT) install -y libcairo2-dev libx11-dev lv2-dev pkg-config
	$(GIT) submodule update --init --recursive neural-amp-modeler-ui
	$(CD) neural-amp-modeler-ui ; $(MAKE) ; sudo $(MAKE) install
	
NAM-models:
	$(GIT) submodule update --init --recursive NAM_models

Speaker-Cabinets-IRs:
	$(GIT) submodule update --init --recursive Speaker-Cabinets-IRs

GxPlugins.lv2: update-packages
	sudo $(APT) install -y libc6-dev libcairo2-dev libx11-dev x11proto-dev lv2-dev pkg-config
	$(GIT) submodule update --init --recursive GxPlugins.lv2
	$(CD) GxPlugins.lv2 ; $(MAKE) ; sudo $(MAKE) install

Carla-Metal-Demo: update-packages neural-amp-modeler-ui NAM-models Speaker-Cabinets-IRs GxPlugins.lv2
	sudo $(APT) install -y carla
	$(MKDIR) Carla
	$(MKDIR) Carla/"LV2 Convolution Mono=>Stereo"
	$(LN) -s ../../Speaker-Cabinets-IRs/"Original 3 Impulses"/"GuitarHack Original Edge.wav" Carla/"LV2 Convolution Mono=>Stereo"/
	$(MKDIR) Carla/"Neural Amp Modeler"
	$(LN) -s ../../NAM_models/"Helga B 6505+ Red ch - MXR Drive V2.nam" Carla/"Neural Amp Modeler"/
	carla SMS-Preset.carxp &

clean:
	$(RM) -rf neural-amp-modeler-lv2
	$(RM) -rf neural-amp-modeler-ui
	$(RM) -rf GxPlugins.lv2
	$(RM) -rf Carla

.PHONY: clean update-packages Carla-Metal-Demo