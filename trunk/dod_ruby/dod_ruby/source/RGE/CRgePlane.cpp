#include "CRgePlane.h"

VALUE rb_cPlane;

CRgePlane::CRgePlane()
{
	SafeObjectNew(m_pPlane = new Dod::DOD_Plane());
}

CRgePlane::~CRgePlane()
{
	SAFE_DELETE(m_pPlane);
}

VALUE CRgePlane::PlaneAllocate(VALUE klass)
{
	return_RgeBase_Make_Class(klass, CRgePlane);

	return Qnil;	//	not reached
}

void CRgePlane::Init()
{
	/**
	 *	@classname
	 *		Plane
	 *
	 *	@desc
	 *		RGE中处理平面的类。所谓平面，是在整个画面中排列显示位图图形的特殊的精灵，用来显示全景和雾。
	 */
	rb_cPlane = rb_define_class_under(rb_mRGE, "Plane", rb_cObject);

	// special method
	rb_define_alloc_func(rb_cPlane, PlaneAllocate);
	rb_define_method(rb_cPlane, "initialize", (RbFunc)dm_initialize, -1);
	
	// object attribute
	rb_define_method(rb_cPlane, "bitmap",		(RbFunc)dm_get_bitmap, 0);
	rb_define_method(rb_cPlane, "bitmap=",		(RbFunc)dm_set_bitmap, 1);
//	rb_define_method(rb_cPlane, "visible",		(RbFunc)dm_get_visible, 0);
//	rb_define_method(rb_cPlane, "visible=",		(RbFunc)dm_set_visible, 1);
	rb_define_method(rb_cPlane, "z",		(RbFunc)dm_get_z, 0);
	rb_define_method(rb_cPlane, "z=",		(RbFunc)dm_set_z, 1);
	rb_define_method(rb_cPlane, "ox",		(RbFunc)dm_get_ox, 0);
	rb_define_method(rb_cPlane, "ox=",		(RbFunc)dm_set_ox, 1);
	rb_define_method(rb_cPlane, "oy",		(RbFunc)dm_get_oy, 0);
	rb_define_method(rb_cPlane, "oy=",		(RbFunc)dm_set_oy, 1);
	rb_define_method(rb_cPlane, "zoom_x",	(RbFunc)dm_get_zoom_x, 0);
	rb_define_method(rb_cPlane, "zoom_x=",	(RbFunc)dm_set_zoom_x, 1);
	rb_define_method(rb_cPlane, "zoom_y",	(RbFunc)dm_get_zoom_y, 0);
	rb_define_method(rb_cPlane, "zoom_y=",	(RbFunc)dm_set_zoom_y, 1);
	
	rb_define_method(rb_cPlane, "color",	(RbFunc)dm_get_color, 0);
	rb_define_method(rb_cPlane, "color=",	(RbFunc)dm_set_color, 1);
	rb_define_method(rb_cPlane, "tone",		(RbFunc)dm_get_tone, 0);
	rb_define_method(rb_cPlane, "tone=",	(RbFunc)dm_set_tone, 1);
}

void CRgePlane::mark()
{
	//rb_gc_mark(m_viewport);
	rb_gc_mark(m_bitmap);
	rb_gc_mark(m_color);
	rb_gc_mark(m_tone);
}
VALUE CRgePlane::initialize(int argc, VALUE *argv, VALUE obj)
{
	m_bitmap = Qnil;
	m_color = Qnil;
	m_tone = Qnil;
	
	return obj;
}


VALUE CRgePlane::get_z()
{
	return rb_float_new(m_pPlane->GetZ());
}
VALUE CRgePlane::set_z(VALUE z)
{
	SafeNumericValue(z);
	m_pPlane->SetZ(NUM2FLOAT(z));
	return Qnil;
}
VALUE CRgePlane::get_ox()
{
	return rb_float_new(m_pPlane->GetOX());
}
VALUE CRgePlane::set_ox(VALUE ox)
{
	SafeNumericValue(ox);
	m_pPlane->SetOX(NUM2FLOAT(ox));
	return Qnil;
}
VALUE CRgePlane::get_oy()
{
	return rb_float_new(m_pPlane->GetOY());
}
VALUE CRgePlane::set_oy(VALUE oy)
{
	SafeNumericValue(oy);
	m_pPlane->SetOX(NUM2FLOAT(oy));
	return Qnil;
}
VALUE CRgePlane::get_zoom_x()
{
	return rb_float_new(m_pPlane->GetZoomX());
}
VALUE CRgePlane::set_zoom_x(VALUE zoom_x)
{
	SafeNumericValue(zoom_x);
	m_pPlane->SetOX(NUM2FLOAT(zoom_x));
	return Qnil;
}
VALUE CRgePlane::get_zoom_y()
{
	return rb_float_new(m_pPlane->GetZoomY());
}
VALUE CRgePlane::set_zoom_y(VALUE zoom_y)
{
	SafeNumericValue(zoom_y);
	m_pPlane->SetOX(NUM2FLOAT(zoom_y));
	return Qnil;
}

VALUE CRgePlane::get_bitmap()
{
	return m_bitmap;
}
VALUE CRgePlane::set_bitmap(VALUE bitmap)
{
	SafeBitmapValue(bitmap);
	m_bitmap = bitmap;
	return Qnil;
}
VALUE CRgePlane::get_color()
{
	return m_color;
}
VALUE CRgePlane::set_color(VALUE color)
{
	SafeColorValue(color);
	m_color = color;
	return Qnil;
}
VALUE CRgePlane::get_tone()
{
	return m_tone;
}
VALUE CRgePlane::set_tone(VALUE tone)
{
	SafeToneValue(tone);
	m_tone = tone;
	return Qnil;
}

imp_attr_accessor(CRgePlane, z)
imp_attr_accessor(CRgePlane, ox)
imp_attr_accessor(CRgePlane, oy)
imp_attr_accessor(CRgePlane, zoom_x)
imp_attr_accessor(CRgePlane, zoom_y)

imp_attr_accessor(CRgePlane, bitmap)
imp_attr_accessor(CRgePlane, color)
imp_attr_accessor(CRgePlane, tone)
