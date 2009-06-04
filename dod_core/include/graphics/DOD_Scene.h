/**
 *	@file		DOD_Scene.h
 *
 *	@desc		DOD_Gx中场景类的定义文件
 *
 *	@author		Syalon
 *
 *	@history	2009/04/11	初版
 */
 
#ifndef __DOD_SCENE_H__
#define __DOD_SCENE_H__

#include "DOD_Gx.h"
#include "DOD_Camera.h"
#include "DOD_Gxobj.h"

namespace Dod
{
class DOD_Scene
{
public:
	DOD_Scene();
	~DOD_Scene();
	
public:
	const DOD_Camera*	GetCamera() const { return m_pCamera; }
	void				SetViewport(u32 x, u32 y, u32 width, u32 height);
	
	void				Render();
	void				Update();
	
private:
	DOD_Camera					*m_pCamera;
		
	struct __viewport
	{
		u32	x, y, width, height;
	}							m_viewport;
};
}

#endif
