#ifndef __C_RGE_BITMAP_H__
#define __C_RGE_BITMAP_H__

#include "RgeBase.h"

#include "DOD_Bitmap.h"

class CRgeBitmap : protected RgeBase
{
public:
	CRgeBitmap();
	virtual ~CRgeBitmap();
	
public:
	static void		Init();
	static VALUE	BitmapAllocate(VALUE klass);
	
private:
	virtual void	mark();
	virtual VALUE	initialize(int argc, VALUE *argv, VALUE obj);
	
private:
	Dod::DOD_Bitmap*		m_pBitmap;
};

#endif
