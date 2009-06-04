TARGET_LIB = ../lib/libdod_audio.a
OBJS = source/test.o

INCDIR = 
CFLAGS = -O2 -G0 -Wall -I./source -I../include -I../include/audio
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CXXFLAGS)

LIBDIR =
LIBS = -lstdc++
LDFLAGS =

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak


