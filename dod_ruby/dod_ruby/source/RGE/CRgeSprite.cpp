#include "CRgeSprite.h"

VALUE rb_cSprite;

CRgeSprite::CRgeSprite()
{
	SafeObjectNew(m_pSprite = new Dod::DOD_Sprite());
}

CRgeSprite::~CRgeSprite()
{
	SAFE_DELETE(m_pSprite);
}

VALUE CRgeSprite::SpriteAllocate(VALUE klass)
{
	return_RgeBase_Make_Class(klass, CRgeSprite);

	return Qnil;	//	not reached
}

void CRgeSprite::Init()
{
	/**
	 *	@classname
	 *		Sprite
	 *
	 *	@desc
	 *		RGE中处理精灵的类。所谓精灵，是为了在游戏画面上显示人物等的基本概念。
	 */
	rb_cSprite = rb_define_class_under(rb_mRGE, "Sprite", rb_cObject);

	// special method
	rb_define_alloc_func(rb_cSprite, SpriteAllocate);
	rb_define_method(rb_cSprite, "initialize", (RbFunc)dm_initialize, -1);

	// instance method
	
	// object attribute
	rb_define_method(rb_cSprite, "bitmap",		(RbFunc)dm_get_bitmap, 0);
	rb_define_method(rb_cSprite, "bitmap=",		(RbFunc)dm_set_bitmap, 1);
//	rb_define_method(rb_cSprite, "visible",		(RbFunc)dm_get_visible, 0);
//	rb_define_method(rb_cSprite, "visible=",	(RbFunc)dm_set_visible, 1);
	rb_define_method(rb_cSprite, "x",		(RbFunc)dm_get_x, 0);
	rb_define_method(rb_cSprite, "x=",		(RbFunc)dm_set_x, 1);
	rb_define_method(rb_cSprite, "y",		(RbFunc)dm_get_y, 0);
	rb_define_method(rb_cSprite, "y=",		(RbFunc)dm_set_y, 1);
	rb_define_method(rb_cSprite, "z",		(RbFunc)dm_get_z, 0);
	rb_define_method(rb_cSprite, "z=",		(RbFunc)dm_set_z, 1);
	rb_define_method(rb_cSprite, "ox",		(RbFunc)dm_get_ox, 0);
	rb_define_method(rb_cSprite, "ox=",		(RbFunc)dm_set_ox, 1);
	rb_define_method(rb_cSprite, "oy",		(RbFunc)dm_get_oy, 0);
	rb_define_method(rb_cSprite, "oy=",		(RbFunc)dm_set_oy, 1);
	rb_define_method(rb_cSprite, "zoom_x",	(RbFunc)dm_get_zoom_x, 0);
	rb_define_method(rb_cSprite, "zoom_x=",	(RbFunc)dm_set_zoom_x, 1);
	rb_define_method(rb_cSprite, "zoom_y",	(RbFunc)dm_get_zoom_y, 0);
	rb_define_method(rb_cSprite, "zoom_y=",	(RbFunc)dm_set_zoom_y, 1);
	
	rb_define_method(rb_cSprite, "color",	(RbFunc)dm_get_color, 0);
	rb_define_method(rb_cSprite, "color=",	(RbFunc)dm_set_color, 1);
	rb_define_method(rb_cSprite, "tone",	(RbFunc)dm_get_tone, 0);
	rb_define_method(rb_cSprite, "tone=",	(RbFunc)dm_set_tone, 1);
}




VALUE CRgeSprite::get_x()
{
	return rb_float_new(m_pSprite->GetX());
}
VALUE CRgeSprite::set_x(VALUE x)
{
	SafeNumericValue(x);
	m_pSprite->SetX(NUM2FLOAT(x));
	return Qnil;
}
VALUE CRgeSprite::get_y()
{
	return rb_float_new(m_pSprite->GetY());
}
VALUE CRgeSprite::set_y(VALUE y)
{
	SafeNumericValue(y);
	m_pSprite->SetY(NUM2FLOAT(y));
	return Qnil;
}

imp_attr_accessor(CRgeSprite, x)
imp_attr_accessor(CRgeSprite, y)
