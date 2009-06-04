TARGET_LIB = ../lib/libdod_graphics.a
OBJS = source/DOD_Scene.o source/DOD_SceneManager.o source/DOD_ObjManager.o source/DOD_Material.o source/DOD_Light.o source/DOD_G3dobj.o \
		source/DOD_G2dobj.o source/DOD_StaticObj.o source/DOD_GeomObj.o source/DOD_AnimObj.o source/DOD_Camera.o source/DOD_Gx.o \
		source/DOD_ResManager.o source/DOD_Texture.o source/DOD_Bitmap.o source/DOD_Sprite.o source/DOD_Plane.o\
		source/DOD_Test.o

INCDIR = 
CFLAGS = -D_DEBUG -O2 -G0 -Wall -I./source -I../include -I../refinclude -I../include/graphics
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CXXFLAGS)

LIBDIR =
LIBS = -lstdc++
LDFLAGS =

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak