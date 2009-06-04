/**
 *	@file		DOD_SceneManager.h
 *
 *	@desc		DOD_Gx中场景管理器的定义文件
 *
 *	@author		Syalon
 *
 *	@history	2009/04/11	初版
 */
 
#ifndef __DOD_SCENE_MANAGER_H__
#define __DOD_SCENE_MANAGER_H__

#include "DOD_Scene.h"

#include <vector>

namespace Dod
{
class DOD_SceneManager
{
public:
	DOD_SceneManager();
	~DOD_SceneManager();
	
public:
	const DOD_Scene*			GetDefaultScene() const;
	void						AddScene(DOD_Scene* pScene);
	void						Update();
	void						Render();
	
private:
	std::vector<DOD_Scene*>		*m_pSceneList;
};
}

#endif
