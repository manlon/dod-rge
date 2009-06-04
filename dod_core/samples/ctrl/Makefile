TARGET = ctrl
OBJS = main.o

INCDIR = 
CFLAGS = -O2 -G0 -Wall -D_PSP_ -I../../include -I../../include/input \
		-L../../lib
		
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CXXFLAGS)

LIBDIR =
LIBS = -lstdc++ -ldod_input
LDFLAGS =

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = ctrl

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak


