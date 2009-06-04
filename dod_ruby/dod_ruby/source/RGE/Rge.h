#ifndef __RGE_H__
#define __RGE_H__

#include <ruby.h>

#include "RgeTypes.h"
#include "RgeDeclare.h"
#include "RgeMacros.h"

typedef VALUE (*RbFunc)(...);

#define	RGE_VERSION				"1.00"
#define	RGE_DEFAULT_TITLE_NAME	"Ruby Game Engine For PSP v"##RGE_VERSION

#define	SafeObjectNew(ptr)	{ if (!(ptr)) rb_raise(rb_eNoMemError, "failed to allocate memory"); }

#define SafeRgeClassValue(obj, klass)\
	if (rb_obj_class(obj) != rb_c##klass){\
		rb_raise(rb_eTypeError, "wrong argument type %s (expected RGE::"#klass")",\
			rb_obj_classname(obj));\
	}

#define SafeAudioValue(aud)		SafeRgeClassValue(aud,	Audio)
#define SafeColorValue(col)		SafeRgeClassValue(col,	Color)
#define SafeToneValue(ton)		SafeRgeClassValue(ton,	Tone)
#define SafeFontValue(fnt)		SafeRgeClassValue(fnt,	Font)
#define SafeBitmapValue(btm)	SafeRgeClassValue(btm,	Bitmap)
#define SafeTableValue(tbl)		SafeRgeClassValue(tbl,	Table)
#define SafeViewportValue(vp)	SafeRgeClassValue(vp,	Viewport)
#define SafeRectValue(rt)		SafeRgeClassValue(rt,	Rect)

#define	SafeFixnumValue(x)\
	if (!FIXNUM_P(x)){\
		rb_raise(rb_eTypeError, "wrong argument type %s (expected Fixnum)",\
			 rb_obj_classname(x));\
	}

#define SafeIntegerValue(i)\
	if (!rb_obj_is_kind_of(i, rb_cInteger)){\
		rb_raise(rb_eTypeError, "wrong argument type %s (expected Integer)",\
			rb_obj_classname(i));\
	}

#define SafeNumericValue(n)\
	if (!rb_obj_is_kind_of(n, rb_cNumeric)){\
		rb_raise(rb_eTypeError, "wrong argument type %s (expected Numeric)",\
			 rb_obj_classname(n));\
	}

#define	RUBY_0				((VALUE)1)			// 1 equal ruby's value 0

#define	Ruby2RbBool(obj)	(RTEST((obj)) ? Qtrue : Qfalse)
#define	C2RbBool(exp)		((exp) ? Qtrue : Qfalse)

#define NUM2FLOAT(n)		Dod::f32(NUM2DBL(n))

#define RGE_SLEEP(milliseconds) do\
{\
	struct timeval st;\
	st.tv_sec = 0;\
	st.tv_usec = milliseconds * 1000;\
	rb_thread_wait_for(st);\
} while (0)

#endif
