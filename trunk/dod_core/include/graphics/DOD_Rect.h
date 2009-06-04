#ifndef __DOD_RECT_H__
#define __DOD_RECT_H__

#include "DOD_Gxtypes.h"

namespace Dod
{
class DOD_Rect
{
public:
	f32	x, y, width, height;
	
public:
	DOD_Rect()
	{
		x = y = width = height = 0.0f;
	}
	DOD_Rect(f32 fx, f32 fy, f32 fwidth, f32 fheight)
	{
		x = fx;
		y = fy;
		width = fwidth;
		height = fheight;
	}
	
	~DOD_Rect(){}
	
	DOD_Rect(const DOD_Rect &rect)
	{
		operator = (rect);
	}
	
	DOD_Rect& operator = (const DOD_Rect &rect)
	{
		x = rect.x;
		y = rect.y;
		width = rect.width;
		height = rect.height;
		
		return *this;
	}
};
}

#endif
