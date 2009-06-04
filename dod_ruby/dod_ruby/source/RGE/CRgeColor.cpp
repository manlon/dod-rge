#include "CRgeColor.h"

VALUE rb_cColor;

CRgeColor::CRgeColor() : m_value(0), m_red(RUBY_0), m_green(RUBY_0), m_blue(RUBY_0), m_alpha(RUBY_0)
{
}

VALUE CRgeColor::ColorAllocate(VALUE klass)
{
	return_RgeBase_Make_Class(klass, CRgeColor);

	return Qnil;	//	not reached
}

void CRgeColor::Init()
{
	/**
	 *	@classname
	 *		Color
	 *
	 *	@desc
	 *		RGBA 颜色的类。
	 */
	rb_cColor = rb_define_class_under(rb_mRGE, "Color", rb_cObject);

	// special method
	rb_define_alloc_func(rb_cColor, ColorAllocate);
	rb_define_method(rb_cColor, "initialize", (RbFunc)dm_initialize, -1);

	// class method
	rb_define_singleton_method(rb_cColor, "_load",	(RbFunc)dm_load, 1);

	// instance method
	rb_define_method(rb_cColor, "set",		(RbFunc)dm_set, -1);
	rb_define_method(rb_cColor, "_dump",	(RbFunc)dm_dump, 1);

	// object attribute
	rb_define_method(rb_cColor, "red",		(RbFunc)dm_get_red, 0);
	rb_define_method(rb_cColor, "red=",		(RbFunc)dm_set_red, 1);
	rb_define_method(rb_cColor, "green",	(RbFunc)dm_get_green, 0);
	rb_define_method(rb_cColor, "green=",	(RbFunc)dm_set_green, 1);
	rb_define_method(rb_cColor, "blue",		(RbFunc)dm_get_blue, 0);
	rb_define_method(rb_cColor, "blue=",	(RbFunc)dm_set_blue, 1);
	rb_define_method(rb_cColor, "alpha",	(RbFunc)dm_get_alpha, 0);
	rb_define_method(rb_cColor, "alpha=",	(RbFunc)dm_set_alpha, 1);
}

/*
 *	以下为ruby方法的c实现
 */
VALUE CRgeColor::initialize(int argc, VALUE *argv, VALUE obj)
{
	return obj;
}

VALUE CRgeColor::set(int argc, VALUE *argv, VALUE obj)
{
	return initialize(argc, argv, obj);
}
VALUE CRgeColor::dump(VALUE aDepth)
{
	return Qnil;
}

VALUE CRgeColor::get_red()
{
	return m_red;
}
VALUE CRgeColor::set_red(VALUE red)
{
	m_red = red;
	return Qnil;
}
VALUE CRgeColor::get_green()
{
	return m_green;
}
VALUE CRgeColor::set_green(VALUE green)
{
	m_green = green;
	return Qnil;
}
VALUE CRgeColor::get_blue()
{
	return m_blue;
}
VALUE CRgeColor::set_blue(VALUE blue)
{
	m_blue = blue;
	return Qnil;
}

VALUE CRgeColor::get_alpha()
{
	return m_alpha;
}
VALUE CRgeColor::set_alpha(VALUE alpha)
{
	m_alpha = alpha;
	return Qnil;
}

/*
 *	以下定义ruby方法
 */
VALUE CRgeColor::dm_load(VALUE klass, VALUE str)
{
	return Qnil;
}
VALUE CRgeColor::dm_set(int argc, VALUE *argv, VALUE obj)
{
	CRgeColor	*cobj;
	Data_Get_Struct(obj, CRgeColor, cobj);

	return cobj->set(argc, argv, obj);
}
VALUE CRgeColor::dm_dump(VALUE obj, VALUE aDepth)
{
	CRgeColor	*cobj;
	Data_Get_Struct(obj, CRgeColor, cobj);

	return cobj->dump(aDepth);
}

imp_attr_accessor(CRgeColor, red)
imp_attr_accessor(CRgeColor, green)
imp_attr_accessor(CRgeColor, blue)
imp_attr_accessor(CRgeColor, alpha)
