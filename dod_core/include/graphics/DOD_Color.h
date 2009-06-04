/**
 *	@file		DOD_Color.h
 *
 *	@desc		DOD_Gx中处理颜色的类定义文件
 *
 *	@author		Syalon
 *
 *	@history	2009/04/11	初版
 */
 
#ifndef __DOD_COLOR_H__
#define __DOD_COLOR_H__

#include "dod_types.h"

namespace Dod
{
class DOD_Color
{
public:
	union
	{
		struct
		{
			u8	r, g, b, a;
		};
		u32	value;
	};
	
public:
	DOD_Color()
	{
		r = g = b = a = 0;
	}
	DOD_Color(u8 ur, u8 ug, u8 ub, u8 ua)
	{
		r = ur;
		g = ug;
		b = ub;
		a = ua;
	}
	DOD_Color(u32 uvalue)
	{
		value = uvalue;
	}
	
	~DOD_Color(){}
		
	DOD_Color(const DOD_Color &color)
	{
		operator = (color);
	}
	
	DOD_Color& operator = (const DOD_Color &color)
	{
		r = color.r;
		g = color.g;
		b = color.b;
		a = color.a;
				
		return *this;
	}
};
}

#endif
