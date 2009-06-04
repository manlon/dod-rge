TARGET = sprite
OBJS = main.o

INCDIR = 
CFLAGS = -O2 -G0 -Wall -D_PSP_ -I../../include -I../../include/graphics \
		-L../../lib -L../../reflib
		
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CXXFLAGS)

LIBDIR =
LIBS = -ldod_graphics -ldod_math -ldod_system -lpng -lz -lm -lpspgum -lpspgu -lstdc++
LDFLAGS =

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = sprite

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak


