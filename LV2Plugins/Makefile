DESTDIR=/usr/local/lib/lv2

CC=g++
CC_FLAGS=-fvisibility=hidden -Wl,-Bstatic -Wl,-Bdynamic -Wl,--as-needed -fPIC -shared -pthread `pkg-config --cflags lv2` -lm `pkg-config --libs lv2` 
CP=cp
RM=rm
MD=mkdir -p
CD=cd
XXD=xxd

all: SMSAmateurDelay SMSStereoDelay SMS440Hz SMSNorthernPerkele SMSWhiteNoise

install:
	$(CP) -r *.lv2 $(DESTDIR)/


# Wildcard (un)install is a bit too loose imo.
#install-%:
#	$(CP) -r $(subst install-,,$@).lv2 $(DESTDIR)/
#
#uninstall-%:
#	$(RM) -rf $(DESTDIR)/$(subst uninstall-,,$@).lv2

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