#include "CRgeTone.h"

VALUE rb_cTone;

VALUE CRgeTone::ToneAllocate(VALUE klass)
{
	return_RgeBase_Make_Class(klass, CRgeTone);

	return Qnil;	//	not reached
}

void CRgeTone::Init()
{
	/**
	 *	@classname
	 *		Tone
	 *
	 *	@desc
	 *		色调的类。
	 */
	rb_cTone = rb_define_class_under(rb_mRGE, "Tone", rb_cObject);

	// special method
	rb_define_alloc_func(rb_cTone, ToneAllocate);
	rb_define_method(rb_cTone, "initialize", (RbFunc)dm_initialize, -1);

	// class method
	rb_define_singleton_method(rb_cTone, "_load",	(RbFunc)dm_load, 1);

	// instance method
	rb_define_method(rb_cTone, "set",		(RbFunc)dm_set, -1);
	rb_define_method(rb_cTone, "_dump",		(RbFunc)dm_dump, 1);

	// object attribute
	rb_define_method(rb_cTone, "red",		(RbFunc)dm_get_red, 0);
	rb_define_method(rb_cTone, "red=",		(RbFunc)dm_set_red, 1);
	rb_define_method(rb_cTone, "green",		(RbFunc)dm_get_green, 0);
	rb_define_method(rb_cTone, "green=",	(RbFunc)dm_set_green, 1);
	rb_define_method(rb_cTone, "blue",		(RbFunc)dm_get_blue, 0);
	rb_define_method(rb_cTone, "blue=",		(RbFunc)dm_set_blue, 1);
	rb_define_method(rb_cTone, "gray",		(RbFunc)dm_get_alpha, 0);
	rb_define_method(rb_cTone, "gray=",		(RbFunc)dm_set_alpha, 1);
}
