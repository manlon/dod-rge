/**
 *	@file		DOD_Texture.h
 *
 *	@desc		DOD_Gx中处理纹理的类的定义文件
 *
 *	@author		Syalon
 *
 *	@history	2009/04/11	初版
 */
 
#ifndef __DOD_TEXTURE_H__
#define __DOD_TEXTURE_H__

#include "DOD_Gxtypes.h"

namespace Dod
{
enum DOD_TextureFormat
{	
	DOD_TF_RGBA5650 = 0,
	DOD_TF_RGBA5551,
	DOD_TF_RGBA4444,
	DOD_TF_RGBA8888
};

#define DOD_COLOR_RGB(r, g, b) 				((r) | ((g) << 8) | ((b) << 16) | ((0xff) << 24))
#define DOD_COLOR_RGBA_5650(r, g, b, a) 	(((r) >> 3) | (((g) >> 2) << 5) | (((b) >> 3) << 11))
#define DOD_COLOR_RGBA_5551(r, g, b, a)		(((r) >> 3) | (((g) >> 3) << 5) | (((b) >> 3) << 10) | (((a) >> 7) << 15))
#define DOD_COLOR_RGBA_4444(r, g, b, a)		(((r) >> 4) | (((g) >> 4) << 4) | (((b) >> 4) << 8) | (((a) >> 4) << 12))
#define DOD_COLOR_RGBA_8888(r, g, b, a)  	((r) | ((g) << 8) | ((b) << 16) | ((a) << 24))

enum DOD_TextureSource
{
	DOD_TS_FILE = 0,
	DOD_TS_MEMORY	
};
	
class DOD_Texture
{
protected:
	DOD_Texture();
	virtual ~DOD_Texture();
	
	DOD_Texture(const DOD_Texture &tex);
	DOD_Texture& operator = (const DOD_Texture &tex);
	
public:
	static	DOD_Texture*	Create(const char* pFilename, DOD_TextureFormat tf = DOD_TF_RGBA4444, DOD_TextureSource ts = DOD_TS_FILE);
	virtual void			Destroy();
	
protected:
	virtual bool			load_core(const char* pFilename, DOD_TextureFormat dtf, DOD_TextureSource dts);
	
	bool					load_from_memory(void* data);
	bool					load_png_file(void* data);
	
public:
	u32						m_width;
	u32						m_height;
	u32						m_tex_width;
	u32						m_tex_height;
	u8						m_bpp;			//	byte per pixel
	void*					m_pdata;
	u32						m_id;
	bool					m_swizzle;
	
	DOD_TextureFormat		m_tf_mode;

private:
	
};
}

#endif
