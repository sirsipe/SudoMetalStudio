MYODP_DESTDIR=~/.lv2
DESTDIR=/usr/local/lib/lv2

CC=g++
CC_FLAGS=-fvisibility=hidden -Wl,-Bstatic -Wl,-Bdynamic -Wl,--as-needed -fPIC -shared -pthread `pkg-config --cflags lv2` -lm `pkg-config --libs lv2` 
CP=cp
RM=rm
MD=mkdir -p
CD=cd
XXD=xxd
GREP=grep
XARGS=xargs
SED=sed
MV=mv

all: SMSAmateurDelay SMSStereoDelay SMS440Hz SMSNorthernPerkele SMSWhiteNoise SMSSwitch

install:
	$(CP) -r *.lv2 $(DESTDIR)/


# Wildcard (un)install is a bit too loose imo.
#install-%:
#	$(CP) -r $(subst install-,,$@).lv2 $(DESTDIR)/
#
#uninstall-%:
#	$(RM) -rf $(DESTDIR)/$(subst uninstall-,,$@).lv2

MYODP-Create-:
	@echo 
	@echo "Usage: MYODP-Create-<NameOfYourPlugin>"
	@echo "E.g.,"
	@echo
	@echo "make MYODP-Create-MyAmazingPlugin"
	@echo
	@echo "Use only ascii letters (and numbers) in your plugin name but DO NOT start with a number"
	@echo

MYODP-Create-%:
	$(CP) -r src/Template src/$(subst MYODP-Create-,,$@)
	$(GREP) -RiIl 'REPLACE_ME' src/$(subst MYODP-Create-,,$@)/ | $(XARGS) $(SED) -i 's/REPLACE_ME/$(subst MYODP-Create-,,$@)/g'
	$(MV) src/$(subst MYODP-Create-,,$@)/REPLACE_ME.cpp src/$(subst MYODP-Create-,,$@)/$(subst MYODP-Create-,,$@).cpp
	$(MV) src/$(subst MYODP-Create-,,$@)/REPLACE_ME.h src/$(subst MYODP-Create-,,$@)/$(subst MYODP-Create-,,$@).h
	$(MV) src/$(subst MYODP-Create-,,$@)/REPLACE_ME.ttl src/$(subst MYODP-Create-,,$@)/$(subst MYODP-Create-,,$@).ttl

MYODP-BuildAndInstall-:
	@echo
	@echo "Usage: MYODP-BuildAndInstall-<NameOfYourPlugin>"
	@echo "E.g.,"
	@echo
	@echo "make MYODP-BuildAndInstall-MyAmazingPlugin"
	@echo

MYODP-BuildAndInstall-%:
	$(MD) ~/.lv2/$(subst MYODP-BuildAndInstall-,,$@).lv2
	$(CC) $(CC_FLAGS) -O3 src/$(subst MYODP-BuildAndInstall-,,$@)/*.cpp -o ~/.lv2/$(subst MYODP-BuildAndInstall-,,$@).lv2/$(subst MYODP-BuildAndInstall-,,$@).so
	$(CP) src/$(subst MYODP-BuildAndInstall-,,$@)/*.ttl $(MYODP_DESTDIR)/$(subst MYODP-BuildAndInstall-,,$@).lv2/

MYODP-Uninstall-:
	@echo
	@echo "Usage: MYODP-Uninstall-<NameOfYourPlugin>"
	@echo "E.g.,"
	@echo
	@echo "make MYODP-Uninstall-MyAmazingPlugin"
	@echo

MYODP-Uninstall-%:
	$(RM) -rf $(MYODP_DESTDIR)/$(subst MYODP-Uninstall-,,$@).lv2/

SMSAmateurDelay:
	$(MD) $@.lv2
	$(CC) $(CC_FLAGS) -O3 src/$@/*.cpp -o $@.lv2/$@.so
	$(CP) src/$@/*.ttl $@.lv2/

install-SMSAmateurDelay:
	$(CP) -r $(subst install-,,$@).lv2 $(DESTDIR)/

uninstall-SMSAmateurDelay:
	$(RM) -rf $(DESTDIR)/$(subst uninstall-,,$@).lv2

SMSStereoDelay:
	$(MD) $@.lv2
	$(CC) $(CC_FLAGS) -O3 src/$@/*.cpp -o $@.lv2/$@.so
	$(CP) src/$@/*.ttl $@.lv2/

install-SMSStereoDelay:
	$(CP) -r $(subst install-,,$@).lv2 $(DESTDIR)/

uninstall-SMSStereoDelay:
	$(RM) -rf $(DESTDIR)/$(subst uninstall-,,$@).lv2

SMS440Hz:
	$(MD) $@.lv2
	$(CC) $(CC_FLAGS) -O3 src/$@/*.cpp -o $@.lv2/$@.so
	$(CP) src/$@/*.ttl $@.lv2/

install-SMS440Hz:
	$(CP) -r $(subst install-,,$@).lv2 $(DESTDIR)/

uninstall-SMS440Hz:
	$(RM) -rf $(DESTDIR)/$(subst uninstall-,,$@).lv2

SMSSwitch:
	$(MD) $@.lv2
	$(CC) $(CC_FLAGS) -O3 src/$@/*.cpp -o $@.lv2/$@.so
	$(CP) src/$@/*.ttl $@.lv2/

install-SMSSwitch:
	$(CP) -r $(subst install-,,$@).lv2 $(DESTDIR)/

uninstall-SMSSwitch:
	$(RM) -rf $(DESTDIR)/$(subst uninstall-,,$@).lv2

SMSWhiteNoise:
	$(MD) $@.lv2
	$(CC) $(CC_FLAGS) -O3 src/$@/*.cpp -o $@.lv2/$@.so
	$(CP) src/$@/*.ttl $@.lv2/

install-SMSWhiteNoise:
	$(CP) -r $(subst install-,,$@).lv2 $(DESTDIR)/

uninstall-SMSWhiteNoise:
	$(RM) -rf $(DESTDIR)/$(subst uninstall-,,$@).lv2

SMSNorthernPerkele:
	$(foreach file, $(filter-out $(wildcard src/$@/res/*.h), $(wildcard src/$@/res/*)), $(CD) $(dir $(file)) && $(XXD) -i $(notdir $(file)) $(notdir $(file)).h;)
	$(MD) $@.lv2	
	$(CC) $(CC_FLAGS) -O3 src/$@/*.cpp -o $@.lv2/$@.so -lX11 -lpng
	$(CP) src/$@/*.ttl $@.lv2/

install-SMSNorthernPerkele:
	$(CP) -r $(subst install-,,$@).lv2 $(DESTDIR)/

uninstall-SMSNorthernPerkele:
	$(RM) -rf $(DESTDIR)/$(subst uninstall-,,$@).lv2


#LV2Neuro:
#	$(MD) $@.lv2
#	$(CC) $(CC_FLAGS) -O3 src/$@/*.cpp -o $@.lv2/$@.so
#	$(CP) src/$@/*.ttl $@.lv2/
#
#install-LV2Neuro:
#	$(CP) -r $(subst install-,,$@).lv2 $(DESTDIR)/
#
#uninstall-LV2Neuro:
#	$(RM) -rf $(DESTDIR)/$(subst uninstall-,,$@).lv2
#

clean:
	$(RM) -rf *.lv2
