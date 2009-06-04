/**
 *	@file		DOD_Bitmap.h
 *
 *	@desc		DOD_Gx中处理2D部分的位图的类的定义文件
 *
 *	@author		Syalon
 *
 *	@history	2009/04/11	初版
 */
 
#ifndef __DOD_BITMAP_H__
#define __DOD_BITMAP_H__

#include "DOD_Texture.h"

namespace Dod
{
class DOD_Bitmap : public DOD_Texture
{
protected:
	DOD_Bitmap() {}
	virtual ~DOD_Bitmap() {}
	
	DOD_Bitmap(const DOD_Bitmap&) {}
	DOD_Bitmap& operator = (const DOD_Bitmap&) { return *this; }
	
public:
	static DOD_Bitmap*	Create(const char* pFilename, DOD_TextureFormat tf = DOD_TF_RGBA4444, DOD_TextureSource ts = DOD_TS_FILE);
};
}

#endif
