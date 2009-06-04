#ifndef __C_RGE_PLANE_H__
#define __C_RGE_PLANE_H__

#include "RgeBase.h"

#include "DOD_Plane.h"

class CRgePlane : protected RgeBase
{
public:
	CRgePlane();
	virtual ~CRgePlane();
	
public:
	static void		Init();
	static VALUE	PlaneAllocate(VALUE klass);
	
protected:
	virtual void	mark();
	virtual VALUE	initialize(int argc, VALUE *argv, VALUE obj);
	
protected:
	VALUE			m_bitmap;		// mark
	VALUE			m_color;		// mark
	VALUE			m_tone;			// mark
	
protected:
	attr_accessor(z)
	attr_accessor(ox)
	attr_accessor(oy)
	attr_accessor(zoom_x);
	attr_accessor(zoom_y);
	
	attr_accessor(bitmap)
	attr_accessor(color)
	attr_accessor(tone)
	
private:
	Dod::DOD_Plane*		m_pPlane;
};

#endif
