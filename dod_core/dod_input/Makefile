TARGET_LIB = ../lib/libdod_input.a
OBJS = source/DodInput.o

INCDIR = 
CFLAGS = -O2 -G0 -Wall -I./source -I../include -I../include/input
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CXXFLAGS)

LIBDIR =
LIBS = -lstdc++
LDFLAGS =

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak


