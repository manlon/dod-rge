/**
 *	@file		DOD_Sprite.h
 *
 *	@desc		DOD_Gx中处理2D精灵显示的类的定义文件
 *
 *	@author		Syalon
 *
 *	@history	2009/04/11	初版
 */
 
#ifndef __DOD_SPRITE_H__
#define __DOD_SPRITE_H__

#include "DOD_Plane.h"

namespace Dod
{
class DOD_Sprite : public DOD_Plane
{
public:
	DOD_Sprite();
	virtual ~DOD_Sprite();
	
public:
	//virtual void	Update();
	//virtual void	Render();
	
protected:
	virtual void	set_vertex_position();
	
protected:
	f32		m_rot_rad;
};
}

#endif
