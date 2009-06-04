/**
 *	@file		DOD_Bitmap.cpp
 *
 *	@desc		DOD_Gx中处理2D部分的位图的类的实现文件
 *
 *	@author		Syalon
 *
 *	@history	2009/04/11	初版
 */
 
#include "DOD_Bitmap.h"

#include "dod_macros.h"

namespace Dod
{
/**
 *	从文件或内存创建位图 返回位图指针
 */
DOD_Bitmap*	DOD_Bitmap::Create(const char* pFilename, DOD_TextureFormat tf, DOD_TextureSource ts)
{
	DOD_Bitmap *pBtm = new DOD_Bitmap();
	
	if (!pBtm)
	{
		DOD_LOG("failed: new DOD_Bitmap().");
		return pBtm;
	}
	
	if (!pBtm->load_core(pFilename, tf, ts))
	{
		SAFE_DELETE(pBtm);
	}
	
	return pBtm;
}
}
