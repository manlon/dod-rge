/**
 *	@file		DOD_Texture.cpp
 *
 *	@desc		DOD_Gx中处理纹理的类的实现文件
 *
 *	@author		Syalon
 *
 *	@history	2009/04/11	初版
 */
 
#include "DOD_Texture.h"

#include "DOD_ResManager.h"

#include "png.h"

#include "dod_debug.h"

namespace Dod
{

namespace
{
	static int Dod_RoundPower2(int width)
	{
		int w = 1;
		while (w < width) w <<= 1;
		return w;
	}
}

DOD_Texture::DOD_Texture()
: m_width(0), m_height(0), m_tex_width(0), m_tex_height(0),
  m_bpp(2), m_pdata(0), m_id(0), m_swizzle(false)
{
	
}

DOD_Texture::~DOD_Texture()
{
	SAFE_FREE(m_pdata);
}

/**
 *	从内存或文件创建纹理 返回纹理对象指针
 */
DOD_Texture* DOD_Texture::Create(const char* pFilename, DOD_TextureFormat tf, DOD_TextureSource ts)
{
	DOD_Texture *pTex = new DOD_Texture();
	
	if (!pTex)
	{
		DOD_LOG("failed: new DOD_Texture().");
		return pTex;
	}
	
	if (!pTex->load_core(pFilename, tf, ts))
	{
		SAFE_DELETE(pTex);
	}
	
	return pTex;
}

/**
 *	销毁纹理对象
 */
void DOD_Texture::Destroy()
{
	delete this;
}

bool DOD_Texture::load_core(const char* pFilename, DOD_TextureFormat tf, DOD_TextureSource ts)
{
	void*	pData = 0;
	bool	ret;
	
	this->m_tf_mode = tf;
	
	if (ts == DOD_TS_FILE)
	{
		u32	size;
		
		pData = Dod_GetResManager()->LoadResource(pFilename, &size);
		
		DOD_LOG("dod_texture loadfile `%s' dataptr = %p datasize = %d.", pFilename, pData, size);
	}
	else
	{
		pData = (void*)pFilename;
	}
	
	ret = load_from_memory(pData);
		
	if (pData != pFilename)
	{
		Dod_GetResManager()->FreeResource(pData);
	}

	return ret;
}

bool DOD_Texture::load_from_memory(void* data)
{
	//	only png - now
	return load_png_file(data);
}

static void png_user_warning_fn(png_structp png_ptr, png_const_charp warning_msg)
{
	DOD_LOG("png warnging # %s.", warning_msg);
}

static int s_offset = 0;

static void png_user_read_fn(png_structp png_ptr, png_bytep data, png_size_t length)
{
	u8* handle = (u8*)png_ptr->io_ptr;

	if (handle == NULL)
	{
		DOD_LOG("png # read error.");
		png_error(png_ptr, "Read Error!");
	}
	
	u8* workptr = handle + s_offset;
	
	s_offset += length;
			
	memcpy(data, workptr, length * sizeof(u8));
}

bool DOD_Texture::load_png_file(void* data)
{
	u32* 	line;
	u32* 	p32;
    u16* 	p16;
    u8*		buffer = NULL;
    
    png_structp	png_ptr;
    png_infop	info_ptr;
    
    unsigned int	sig_read = 0;
    
    png_uint_32 	width, height;
    
    int bit_depth, color_type, interlace_type, x, y;
    
	int texw, texh, bpp, size;
	
	u8	done = 0;
	
	u32 color32, color16;
	
	register u8 r, g, b, a;
	
	s_offset = 0;

	if (data == 0) return false;
    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (png_ptr == NULL)
  		return false;
        
    png_set_error_fn(png_ptr, (png_voidp)NULL, (png_error_ptr)NULL, png_user_warning_fn);
    info_ptr = png_create_info_struct(png_ptr);
    if (info_ptr == NULL)
    {
		png_destroy_read_struct(&png_ptr, png_infopp_NULL, png_infopp_NULL);
		return false;
    }
    
    png_init_io(png_ptr, NULL);
	png_set_read_fn(png_ptr, (png_voidp)data, png_user_read_fn);
    png_set_sig_bytes(png_ptr, sig_read);
    png_read_info(png_ptr, info_ptr);	//	errored ?
    png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type, &interlace_type, int_p_NULL, int_p_NULL);
    png_set_strip_16(png_ptr);    
    png_set_packing(png_ptr);
    
    if (color_type == PNG_COLOR_TYPE_PALETTE)				png_set_palette_to_rgb(png_ptr);
    if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)	png_set_gray_1_2_4_to_8(png_ptr);
    if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))	png_set_tRNS_to_alpha(png_ptr);
    
    png_set_filler(png_ptr, 0xff, PNG_FILLER_AFTER);
    line = (u32*)malloc(width * 4);
    if (!line)
    {
	    png_destroy_read_struct(&png_ptr, png_infopp_NULL, png_infopp_NULL);
	    return false;
    }
    
	texw = Dod_RoundPower2(width);
	texh = Dod_RoundPower2(height);
	
	bpp = 4;
	if(m_tf_mode != GU_PSM_8888)
		bpp = 2;
	
	size = texw * texh * bpp;
	buffer = (u8*)malloc(size);
	//memset(buffer,0,size);
    if (buffer)
    {
		p32 = (u32*) buffer;
		p16 = (u16*) p32;
		for (y = 0; y < (int)height; ++y)
		{
		    png_read_row(png_ptr, (u8*)line, png_bytep_NULL);
		    for (x = 0; x < (int)width; ++x) 
		    {
		        color32 = line[x];
		        //color16;
		        r = color32 & 0xff;
		        g = (color32 >> 8) & 0xff;
		        b = (color32 >> 16) & 0xff;
		        a = (color32 >> 24) & 0xff;
		        switch (m_tf_mode)
		        {
	                case DOD_TF_RGBA5650:
                        color16 = DOD_COLOR_RGBA_5650(r,g,b,a);
                        *(p16+x) = color16;
                        break;
	                case DOD_TF_RGBA5551:
                        color16 = DOD_COLOR_RGBA_5551(r,g,b,a);
                        *(p16+x) = color16;
                        break;
	                case DOD_TF_RGBA4444:
                        color16 = DOD_COLOR_RGBA_4444(r,g,b,a);
                        *(p16+x) = color16;
                        break;
	                case DOD_TF_RGBA8888:
                        color32 = DOD_COLOR_RGBA_8888(r,g,b,a);
                        *(p32+x) = color32;
                        break;
		       }
		    }
		    p32 += texw;
		    p16 += texw;
		}
		done = 1;
	}
    SAFE_FREE(line);
    
    png_read_end(png_ptr, info_ptr);
    png_destroy_read_struct(&png_ptr, &info_ptr, png_infopp_NULL);

	if (done)
	{
		//pimage = (image_p)malloc(sizeof(image_t));
		//memset(pimage,0,sizeof(image_t));
		//pimage->data = (uint8 *)buffer;
		m_pdata	= buffer;
		m_width = width;
		m_height = height;
		m_tex_width = texw;
		m_tex_height = texh;
		m_bpp = bpp;
		//m_display_mode = 
		
		//pimage->dtype = displaymode;
		//pimage->rcentrex = 0;
		//pimage->rcentrey = 0;
		//pimage->mode = GET_PSM_COLOR_MODE(displaymode);
		//pimage->mask = CreateColor(255,255,255,255,displaymode);
		//pimage->texid = image_tid++;
	}

	return true;
}

}
