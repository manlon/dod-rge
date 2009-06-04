/**
 *	@file		DOD_Sprite.cpp
 *
 *	@desc		DOD_Gx中处理2D精灵显示的类的实现文件
 *
 *	@author		Syalon
 *
 *	@history	2009/04/11	初版
 */
 
#include "DOD_Sprite.h"

#include "math/DodMath.h"

namespace Dod
{

DOD_Sprite::DOD_Sprite()
: m_rot_rad(0.0f)
{
	
}

DOD_Sprite::~DOD_Sprite()
{
	
}

void DOD_Sprite::set_vertex_position()
{
	f32	offset_x1, offset_x2, offset_y1, offset_y2;
	
	offset_x1	= -m_ox * m_zoom_x;
	offset_y1	= -m_oy * m_zoom_y;
	offset_x2	= (m_rect.width - m_ox) * m_zoom_x;
	offset_y2	= (m_rect.height - m_oy) * m_zoom_y;
	
	if (m_rot_rad != 0.0f)
	{
		f32 cosv = DodMath::CosR(m_rot_rad);
		f32 sinv = DodMath::SinR(m_rot_rad);
		
		m_vtxs[0].x = offset_x1 * cosv - offset_y1 * sinv + m_x;
		m_vtxs[0].y = offset_x1 * sinv + offset_y1 * cosv + m_y;

		m_vtxs[1].x = offset_x1 * cosv - offset_y2 * sinv + m_x;
		m_vtxs[1].y = offset_x1 * sinv + offset_y2 * cosv + m_y;
		
		m_vtxs[2].x = offset_x2 * cosv - offset_y1 * sinv + m_x;
		m_vtxs[2].y = offset_x2 * sinv + offset_y1 * cosv + m_y;

		m_vtxs[3].x = offset_x2 * cosv - offset_y2 * sinv + m_x;
		m_vtxs[3].y = offset_x2 * sinv + offset_y2 * cosv + m_y;
	}
	else
	{
		m_vtxs[0].x = offset_x1 + m_x; m_vtxs[0].y = offset_y1 + m_y;
		m_vtxs[1].x = offset_x1 + m_x; m_vtxs[1].y = offset_y2 + m_y;
		m_vtxs[2].x = offset_x2 + m_x; m_vtxs[2].y = offset_y1 + m_y;
		m_vtxs[3].x = offset_x2 + m_x; m_vtxs[3].y = offset_y2 + m_y;
	}
}

}
