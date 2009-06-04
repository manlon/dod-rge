/**
 *	@file		DOD_ResManager.h
 *
 *	@desc		DOD中资源文件管理器的类定义文件
 *
 *	@author		Syalon
 *
 *	@history	2009/04/11	初版
 */
 
#ifndef __DOD_RESOURCES_MANAGER_H__
#define __DOD_RESOURCES_MANAGER_H__

#include "DOD_Gx.h"

namespace Dod
{
class DOD_ResManager
{
private:
	DOD_ResManager(){}
	~DOD_ResManager(){}
	
	DOD_ResManager(const DOD_ResManager&);
	DOD_ResManager& operator = (const DOD_ResManager&) { return *this; }
	
public:
	void* 	LoadResource(const char *pFilename, u32 *pSize);
	void	FreeResource(void *pData);
	
private:
	static DOD_ResManager*	s_pResMgr;
	
	friend void				Dod_CreateResManager();
	friend void				Dod_DestroyResManager();
	friend DOD_ResManager*	Dod_GetResManager();
};

void					Dod_CreateResManager();
void					Dod_DestroyResManager();
inline DOD_ResManager*	Dod_GetResManager() { return DOD_ResManager::s_pResMgr; }
}

#endif
