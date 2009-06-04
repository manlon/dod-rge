/**
 *	@file		DOD_Scene.cpp
 *
 *	@desc		DOD_Gx中场景类的实现文件
 *
 *	@author		Syalon
 *
 *	@history	2009/04/11	初版
 */
 
#include "DOD_Scene.h"
#include "DOD_ObjManager.h"

#include <pspgum.h>

#include <vector>

namespace Dod
{
DOD_Scene::DOD_Scene()
{
	m_pCamera = new DOD_Camera();

	m_viewport.x = m_viewport.y = 0;
	m_viewport.width = DOD_SCREEN_WIDTH;
	m_viewport.height = DOD_SCREEN_HEIGHT;
}

DOD_Scene::~DOD_Scene()
{
	SAFE_DELETE(m_pCamera);
}

/**
 *	设置Scene的视口
 */
void DOD_Scene::SetViewport(u32 x, u32 y, u32 width, u32 height)
{
	m_viewport.x = x;
	m_viewport.y = y;
	m_viewport.width = width;
	m_viewport.height = height;
}

/**
 *	渲染Scene
 */
void DOD_Scene::Render()
{
	const DOD_ObjManager 	*pObjMgr = Dod_GxGetObjMgr();
	
	//	渲染3D部分
	{
		
	}
	
	//	渲染2D部分
	{
		sceGumMatrixMode(GU_PROJECTION);
		sceGumLoadIdentity();
		sceGumOrtho(0, DOD_SCREEN_WIDTH, DOD_SCREEN_HEIGHT, 0, 0.5f, 1000.0f);

		sceGumMatrixMode(GU_VIEW);
		{
			ScePspFVector3 pos = {0.0f,0.0f,1.5f};
			
			ScePspFVector3 up = {0.0f,1.0f,0.0f};
			ScePspFVector3 at = {0.0f,0.0f,0.0};
			
			sceGumLoadIdentity();
			sceGumLookAt(&pos, &at, &up);
		}
		
		sceGumMatrixMode(GU_MODEL);
		{
			sceGumLoadIdentity();
		}
		
		DODG2DLIST	*pG2dList = pObjMgr->GetG2dList();
		
		for (DODG2DLIST::iterator it = pG2dList->begin(); it != pG2dList->end(); ++it)
		{
			(*it)->Render();
		}	
	}
}

/**
 *	更新Scene
 */
void DOD_Scene::Update()
{
	
}
}
