/**
 *	@file		DOD_SceneManager.cpp
 *
 *	@desc		DOD_Gx中场景管理器的实现文件
 *
 *	@author		Syalon
 *
 *	@history	2009/04/11	初版
 */
 
#include "DOD_SceneManager.h"

#include "DOD_Gx.h"

namespace Dod
{
DOD_SceneManager::DOD_SceneManager()
{
	m_pSceneList = new std::vector<DOD_Scene*>();
	m_pSceneList->push_back(new DOD_Scene());
}

DOD_SceneManager::~DOD_SceneManager()
{
	delete GetDefaultScene();
	SAFE_DELETE(m_pSceneList);
}

/**
 *	获取默认Scene指针
 */
const DOD_Scene* DOD_SceneManager::GetDefaultScene() const
{
	return *m_pSceneList->begin();
}

/**
 *	添加一个新的Scene
 */
void DOD_SceneManager::AddScene(DOD_Scene* pScene)
{
	m_pSceneList->push_back(pScene);
}

/**
 *	更新所有Scene
 */
void DOD_SceneManager::Update()
{
	for (std::vector<DOD_Scene*>::iterator it = m_pSceneList->begin(); it != m_pSceneList->end(); ++it)
	{
		(*it)->Update();
	}
}

/**
 *	渲染所有Scene
 */
void DOD_SceneManager::Render()
{
	for (std::vector<DOD_Scene*>::iterator it = m_pSceneList->begin(); it != m_pSceneList->end(); ++it)
	{
		(*it)->Render();
	}
}
}
