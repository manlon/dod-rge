/**
 *	@file		DOD_Plane.cpp
 *
 *	@desc		DOD_Gx中处理2D平面显示的类的实现文件
 *
 *	@author		Syalon
 *
 *	@history	2009/04/11	初版
 */
 
#include "DOD_Plane.h"

#include "dod_macros.h"

#include <stdlib.h>
#include <string.h>

#include <pspgum.h>

namespace Dod
{
DOD_Plane::DOD_Plane()
: m_zoom_x(1.0f), m_zoom_y(1.0f),
  m_pTex(0),
  m_tex_width(1.0f), m_tex_height(1.0f),
  m_flip_x(false), m_flip_y(false), m_flip_origin_spot(false)
{

}

DOD_Plane::~DOD_Plane()
{
	
}

/**
 *	设置平面关联的位图
 */
void DOD_Plane::SetBitmap(const DOD_Bitmap* pTex)
{
	f32 tw, th;

	m_pTex = pTex;
	
	if (pTex)
	{
		tw = pTex->m_tex_width;
		th = pTex->m_tex_height;
	}
	else
	{
		tw = 1.0f;
		th = 1.0f;
	}
	
	if (tw != m_tex_width || th != m_tex_height)
	{
		m_tex_width = tw;
		m_tex_height = th;
		
		if (pTex)
		{
			SetRect(0, 0, pTex->m_width, pTex->m_height);
		}
		else
		{
			f32 u1, v1, u2, v2;
			
			u1 = m_vtxs[0].u * m_tex_width;
			v1 = m_vtxs[0].v * m_tex_height;
			u2 = m_vtxs[2].u * m_tex_width;
			v2 = m_vtxs[2].v * m_tex_height;

			u1 /= tw; v1 /= th;
			u2 /= tw; v2 /= th;
			
			m_vtxs[0].u = u1; m_vtxs[0].v = v1; 
			m_vtxs[1].u = u1; m_vtxs[1].v = v2; 
			m_vtxs[2].u = u2; m_vtxs[2].v = v1; 
			m_vtxs[3].u = u2; m_vtxs[3].v = v2; 
		}
	}
}

/**
 *	设置纹理显示区域矩形
 */
void DOD_Plane::SetRect(f32 x, f32 y, f32 width, f32 height)
{
	f32		u1, v1, u2, v2;	
	bool 	flip_x, flip_y;
	
	//	保存矩形
	{
		m_rect.x = x;
		m_rect.y = y;
		m_rect.width = width;
		m_rect.height = height;
	}
	
	//	根据矩形设置新的纹理坐标
	u1 = m_rect.x / m_tex_width; 
	v1 = m_rect.y / m_tex_height;
	u2 = (m_rect.x + m_rect.width) / m_tex_width; 
	v2 = (m_rect.y + m_rect.height) / m_tex_height;

	m_vtxs[0].u = u1; m_vtxs[0].v = v1; 
	m_vtxs[1].u = u1; m_vtxs[1].v = v2; 
	m_vtxs[2].u = u2; m_vtxs[2].v = v1; 
	m_vtxs[3].u = u2; m_vtxs[3].v = v2; 

	//	重新翻转纹理坐标
	flip_x = m_flip_x;
	flip_y = m_flip_y;
	
	m_flip_x = false;
	m_flip_y = false;
	
	SetFlip(flip_x, flip_y, m_flip_origin_spot);
}
void DOD_Plane::SetRect(const DOD_Rect &rect)
{
	SetRect(rect.x, rect.y, rect.width, rect.height);
}

/**
 *	翻转对象
 */
void DOD_Plane::SetFlip(bool flip_x, bool flip_y, bool flip_spot)
{
	f32 u, v;
	
	//	还原中心点
	if (m_flip_origin_spot && m_flip_x)	m_ox = m_rect.width - m_ox;
	if (m_flip_origin_spot && m_flip_y)	m_oy = m_rect.height - m_oy;
	
	m_flip_origin_spot = flip_spot;

	//	重新设置中心点	
	if (m_flip_origin_spot && m_flip_x)	m_ox = m_rect.width - m_ox;
	if (m_flip_origin_spot && m_flip_y)	m_oy = m_rect.height - m_oy;

	//	水平翻转
	if (m_flip_x != flip_x)
	{
		u = m_vtxs[0].u; m_vtxs[0].u = m_vtxs[2].u; m_vtxs[2].u = u;
		v = m_vtxs[0].v; m_vtxs[0].v = m_vtxs[2].v; m_vtxs[2].v = v;
		u = m_vtxs[3].u; m_vtxs[3].u = m_vtxs[1].u; m_vtxs[1].u = u;
		v = m_vtxs[3].v; m_vtxs[3].v = m_vtxs[1].v; m_vtxs[1].v = v;

		m_flip_x = flip_x;
	}

	//	垂直翻转
	if (m_flip_y != flip_y)
	{
		u = m_vtxs[0].u; m_vtxs[0].u = m_vtxs[1].u; m_vtxs[1].u = u;
		v = m_vtxs[0].v; m_vtxs[0].v = m_vtxs[1].v; m_vtxs[1].v = v;
		u = m_vtxs[2].u; m_vtxs[2].u = m_vtxs[3].u; m_vtxs[3].u = u;
		v = m_vtxs[2].v; m_vtxs[2].v = m_vtxs[3].v; m_vtxs[3].v = v;

		m_flip_y = flip_y;
	}
}

/**
 *	设置顶点色
 */
void DOD_Plane::SetColor(u32 color, s32 idx)
{
	if (idx >= 0 && idx < 4)
		m_vtxs[idx].color = color;
	else
	{
		m_vtxs[0].color =
		m_vtxs[1].color =
		m_vtxs[2].color =
		m_vtxs[3].color = color;
	}
}

f32 DOD_Plane::SetZoomX(f32 fv)
{
	m_zoom_x = fv;
	return fv;
}

f32 DOD_Plane::SetZoomY(f32 fv)
{
	m_zoom_y = fv;
	return fv;
}

void DOD_Plane::Update()
{
	
}

/**
 *	渲染对象
 */
void DOD_Plane::Render()
{
	if (!m_pTex)
		return;
		
	//	设置纹理相关
	set_texture_attr();

	//	设置纹理坐标
	set_texture_uv();

	//	设置顶点坐标
	set_vertex_position();
	
	//	描绘
	sceGumDrawArray(GU_TRIANGLE_STRIP, dod_vertex_tcp_fvf | GU_TRANSFORM_3D, 4, 0, m_vtxs); 
}

void DOD_Plane::set_texture_attr()
{
	sceGuTexMode(m_pTex->m_tf_mode, 0, 0, 0);
	sceGuTexImage(0, m_pTex->m_tex_width, m_pTex->m_tex_height, m_pTex->m_tex_width, m_pTex->m_pdata);
	sceGuTexFunc(GU_TFX_ADD, GU_TCC_RGB);
	//sceGuTexFilter(GU_LINEAR, GU_LINEAR);
}

void DOD_Plane::set_texture_uv()
{
	
}

void DOD_Plane::set_vertex_position()
{
	f32	offset_x1, offset_x2, offset_y1, offset_y2;
	
	offset_x1	= -m_ox * m_zoom_x;
	offset_y1	= -m_oy * m_zoom_y;
	offset_x2	= (m_rect.width - m_ox) * m_zoom_x;
	offset_y2	= (m_rect.height - m_oy) * m_zoom_y;
	
	m_vtxs[0].x = offset_x1 + m_x; m_vtxs[0].y = offset_y1 + m_y;
	m_vtxs[1].x = offset_x1 + m_x; m_vtxs[1].y = offset_y2 + m_y;
	m_vtxs[2].x = offset_x2 + m_x; m_vtxs[2].y = offset_y1 + m_y;
	m_vtxs[3].x = offset_x2 + m_x; m_vtxs[3].y = offset_y2 + m_y;
}
}
