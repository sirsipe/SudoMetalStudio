DESTDIR=/usr/local/lib/lv2

CC=g++
CC_FLAGS=-fvisibility=hidden -Wl,-Bstatic -Wl,-Bdynamic -Wl,--as-needed -fPIC -shared -pthread `pkg-config --cflags lv2` -lm `pkg-config --libs lv2` 
CP=cp
RM=rm
MD=mkdir -p
all: LV2Neuro SMSAmateurDelay

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

LV2Neuro:
	$(MD) $@.lv2
	$(CC) $(CC_FLAGS) -O3 src/$@/*.cpp -o $@.lv2/$@.so
	$(CP) src/$@/*.ttl $@.lv2/

install-LV2Neuro:
	$(CP) -r $(subst install-,,$@).lv2 $(DESTDIR)/

uninstall-LV2Neuro:
	$(RM) -rf $(DESTDIR)/$(subst uninstall-,,$@).lv2

clean:
	$(RM) -rf *.lv2