/**
 *	@file		DOD_Scene.cpp
 *
 *	@desc		DOD_Gx�г������ʵ���ļ�
 *
 *	@author		Syalon
 *
 *	@history	2009/04/11	����
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
 *	����Scene���ӿ�
 */
void DOD_Scene::SetViewport(u32 x, u32 y, u32 width, u32 height)
{
	m_viewport.x = x;
	m_viewport.y = y;
	m_viewport.width = width;
	m_viewport.height = height;
}

/**
 *	��ȾScene
 */
void DOD_Scene::Render()
{
	const DOD_ObjManager 	*pObjMgr = Dod_GxGetObjMgr();
	
	//	��Ⱦ3D����
	{
		
	}
	
	//	��Ⱦ2D����
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
 *	����Scene
 */
void DOD_Scene::Update()
{
	
}
}
