TARGET = rge_for_psp

OBJS = source/Entry.o source/RGE/ResManager.o source/RGE/RgeManager.o source/RGE/RubyInternExt.o \
	source/RGE/MRge.o source/RGE/MInput.o source/RGE/MGraphics.o source/RGE/RgeBase.o source/RGE/CRgeColor.o \
	source/RGE/CRgeTone.o source/RGE/CRgePlane.o source/RGE/CRgeSprite.o source/RGE/CRgeBitmap.o

INCDIR = 
CFLAGS = -O2 -G0 -Wall -D_PSP_ -I./source -I./source/RGE -I./source/AuxLib \
		-I./ruby186/include \
		-I../../dod_core/include \
		-I../../dod_core/include/audio \
		-I../../dod_core/include/math \
		-I../../dod_core/include/graphics \
		-I../../dod_core/include/input \
		-L../../dod_core/lib \
		-L../../dod_core/reflib \
		-L./lib
		
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
#ASFLAGS = $(CFLAGS)
ASFLAGS = $(CXXFLAGS)

LIBDIR =
LIBS = -lruby -ldod_input -ldod_graphics -ldod_system -lpng -lz -ldod_math -lpspgum -lpspgu -lm -lstdc++
LDFLAGS =

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = Ruby Game Engine For PSP v1.0

PSPSDK = $(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak

