#include "CRgeBitmap.h"

VALUE rb_cBitmap;

CRgeBitmap::CRgeBitmap()
: m_pBitmap(0)
{

}

CRgeBitmap::~CRgeBitmap()
{
	if (m_pBitmap)
	{
		m_pBitmap->Destroy();
		m_pBitmap = 0;
	}
}

VALUE CRgeBitmap::BitmapAllocate(VALUE klass)
{
	return_RgeBase_Make_Class(klass, CRgeBitmap);

	return Qnil;	//	not reached
}

void CRgeBitmap::Init()
{
	/**
	 *	@classname
	 *		Bitmap
	 *
	 *	@desc
	 *		位图的类。所谓位图即表示图像其本身。
	 */
	rb_cBitmap = rb_define_class_under(rb_mRGE, "Bitmap", rb_cObject);

	// special method
	rb_define_alloc_func(rb_cBitmap, BitmapAllocate);
	rb_define_method(rb_cBitmap, "initialize",	(RbFunc)dm_initialize, -1);
}

void CRgeBitmap::mark()
{
	
}

VALUE CRgeBitmap::initialize(int argc, VALUE *argv, VALUE obj)
{
	m_pBitmap = Dod::DOD_Bitmap::Create(0);
	
	return obj;
}
