/**
 *	@file		DOD_Bitmap.cpp
 *
 *	@desc		DOD_Gx�д���2D���ֵ�λͼ�����ʵ���ļ�
 *
 *	@author		Syalon
 *
 *	@history	2009/04/11	����
 */
 
#include "DOD_Bitmap.h"

#include "dod_macros.h"

namespace Dod
{
/**
 *	���ļ����ڴ洴��λͼ ����λͼָ��
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
