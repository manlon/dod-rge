/**
 *	@file		DOD_SceneManager.cpp
 *
 *	@desc		DOD_Gx�г�����������ʵ���ļ�
 *
 *	@author		Syalon
 *
 *	@history	2009/04/11	����
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
 *	��ȡĬ��Sceneָ��
 */
const DOD_Scene* DOD_SceneManager::GetDefaultScene() const
{
	return *m_pSceneList->begin();
}

/**
 *	���һ���µ�Scene
 */
void DOD_SceneManager::AddScene(DOD_Scene* pScene)
{
	m_pSceneList->push_back(pScene);
}

/**
 *	��������Scene
 */
void DOD_SceneManager::Update()
{
	for (std::vector<DOD_Scene*>::iterator it = m_pSceneList->begin(); it != m_pSceneList->end(); ++it)
	{
		(*it)->Update();
	}
}

/**
 *	��Ⱦ����Scene
 */
void DOD_SceneManager::Render()
{
	for (std::vector<DOD_Scene*>::iterator it = m_pSceneList->begin(); it != m_pSceneList->end(); ++it)
	{
		(*it)->Render();
	}
}
}
