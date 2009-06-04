/**
 *	@file		DOD_Plane.h
 *
 *	@desc		DOD_Gx中处理2D平面显示的类的定义文件
 *
 *	@author		Syalon
 *
 *	@history	2009/04/11	初版
 */
 
#ifndef __DOD_PLANE_H__
#define __DOD_PLANE_H__

#include "DOD_G2dobj.h"

#include "DOD_Bitmap.h"
#include "DOD_Rect.h"

namespace Dod
{
class DOD_Plane : public DOD_G2dobj
{
public:
	DOD_Plane();
	virtual ~DOD_Plane();
	
public:
	virtual void	Update();
	virtual void	Render();
	
public:
	void			SetBitmap(const DOD_Bitmap* pBtm);
	
	void			SetRect(f32 x, f32 y, f32 width, f32 height);
	void			SetRect(const DOD_Rect &rect);
	
	void			SetFlip(bool flip_x, bool flip_y, bool flip_spot = false);
	void			SetColor(u32 color, s32 idx = -1);
	
	f32				GetZoomX() const { return m_zoom_x; }
	f32				GetZoomY() const { return m_zoom_y; }
	
	virtual	f32		SetZoomX(f32 fv);
	virtual	f32		SetZoomY(f32 fv);
	
protected:
	virtual void	set_texture_attr();
	virtual void	set_texture_uv();
	virtual void	set_vertex_position();
	
protected:
	f32				m_zoom_x;
	f32				m_zoom_y;
	
	DOD_Rect		m_rect;
	
protected:
	const DOD_Bitmap*	m_pTex;
	
	f32				m_tex_width;
	f32				m_tex_height;
	
	bool			m_flip_x;
	bool			m_flip_y;
	bool			m_flip_origin_spot;	
};
}

#endif
