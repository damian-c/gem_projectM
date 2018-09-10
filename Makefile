# change to actual source directories

PD_DIR = /usr/include/pd
GEM_DIR = /usr/include/Gem

# build flags

INCLUDES =  -I.  -I$(GEM_DIR) -I$(PD_DIR)/src
CPPFLAGS  = -fPIC -DPD -O2 -funroll-loops -fomit-frame-pointer  -ffast-math \
    -Wall -W -Wno-unused -Wno-parentheses -Wno-switch \
     -g


UNAME := $(shell uname -s)
ifeq ($(UNAME),Linux)
 CPPFLAGS += -DLINUX
 INCLUDES += `pkg-config --cflags libprojectM`
 LDFLAGS = -rdynamic -shared
 LIBS = `pkg-config --libs libprojectM`
 EXTENSION = pd_linux
endif

SOURCES = gem_projectM.cpp

all: $(SOURCES:.cpp=.$(EXTENSION)) $(SOURCES_OPT:.cpp=.$(EXTENSION))

%.$(EXTENSION): %.o
	gcc $(LDFLAGS) -o $*.$(EXTENSION) $*.o $(LIBS)

.cpp.o:
	g++ $(CPPFLAGS) $(INCLUDES) -o $*.o -c $*.cpp

.c.o:
	gcc $(CPPFLAGS) $(INCLUDES) -o $*.o -c $*.c

clean:
	rm -f gem_projectM*.o
	rm -f gem_projectM*.$(EXTENSION)

distro: clean all
	rm *.o
