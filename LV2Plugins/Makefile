CC=g++
CC_FLAGS=-fvisibility=hidden -fPIC -Wl,-Bstatic -Wl,-Bdynamic -Wl,--as-needed -shared -pthread `pkg-config --cflags lv2` -lm `pkg-config --libs lv2` 
CP=cp
RM=rm

all: LV2Neuro

LV2Neuro:
	$(CC) $(CC_FLAGS) src/LV2Neuro/*.cpp -o LV2Neuro.lv2/LV2Neuro.so

install:
	$(CP) -r *.lv2 /usr/local/lib/lv2/

clean:
	$(RM) -rf *.lv2/*.so