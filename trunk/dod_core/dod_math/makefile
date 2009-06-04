H_FILE = ../include
H_FILE_MATH = $(H_FILE)/math
PARA = -G0 -Wall -D_PSP_FW_VERSION=150

VPATH = $(H_FILE) : $(H_FILE_MATH)

ALL_MATH_OBJ = source/DodMath.o source/DOD_Vec2.o source/DOD_Vec3.o source/DOD_Vec4.o source/DOD_Mat22.o source/DOD_Mat33.o

dod_math.lib : $(ALL_MATH_OBJ)
	psp-ar r ../lib/libdod_math.a $(ALL_MATH_OBJ)

$(ALL_MATH_OBJ) : %.o : %.cpp
	psp-g++ -I $(H_FILE) -I $(H_FILE_MATH) $(PARA) -c $< -o $@

.PHONY : clean
clean:
	-rm -f source/*.o  #-del *.o
