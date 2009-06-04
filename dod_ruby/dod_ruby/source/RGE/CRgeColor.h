#ifndef __C_RGE_COLOR_H__
#define __C_RGE_COLOR_H__

#include "RgeBase.h"

class CRgeColor : protected RgeBase
{
public:
	CRgeColor();

public:
	static void		Init();
	static VALUE	ColorAllocate(VALUE klass);

public:
	Dod::u32			m_value;

protected:
	VALUE		m_red;
	VALUE		m_green;
	VALUE		m_blue;
	VALUE		m_alpha;

protected:
	virtual VALUE initialize(int argc, VALUE *argv, VALUE obj);

protected:
	virtual VALUE set(int argc, VALUE *argv, VALUE obj);
	virtual VALUE dump(VALUE aDepth);

protected:
	static VALUE dm_load(VALUE klass, VALUE str);
	static VALUE dm_set(int argc, VALUE *argv, VALUE obj);
	static VALUE dm_dump(VALUE obj, VALUE aDepth);

	attr_accessor(red)
	attr_accessor(green)
	attr_accessor(blue)
	attr_accessor(alpha)
};

#endif
