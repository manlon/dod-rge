/**
 *	@file		DOD_ResManager.cpp
 *
 *	@desc		DOD中资源文件管理器的类实现文件
 *
 *	@author		Syalon
 *
 *	@history	2009/04/11	初版
 */
 
#include "DOD_ResManager.h"

#include <stdio.h>
#include <stdlib.h>

namespace Dod
{
void Dod_CreateResManager()
{
	if (!DOD_ResManager::s_pResMgr)
		DOD_ResManager::s_pResMgr = new DOD_ResManager();
}

void Dod_DestroyResManager()
{
	SAFE_DELETE(DOD_ResManager::s_pResMgr);
}

DOD_ResManager*	DOD_ResManager::s_pResMgr = 0;

/**
 *	加载指定资源 返回数据指针
 */
void* DOD_ResManager::LoadResource(const char *pFilename, u32 *pSize)
{
	void	*data = 0;
	
	FILE	*fr = NULL;
	
	u32		file_size;

	if (pSize) *pSize = 0;	//	init it !
	
	if (!(fr = fopen(pFilename, "rb")))
		return 0;
	
	fseek(fr, 0, SEEK_END);
	file_size = ftell(fr);
	fseek(fr, 0, SEEK_SET);
	
	if (!(data = malloc(file_size)))
		goto failed_return;
	
	file_size = fread(data, 1, file_size, fr);
	if (file_size == 0)
		goto failed_return;
	
	fclose(fr);
	
	if (pSize) *pSize = file_size;
	
	return data;
	
failed_return:
	SAFE_CLOSE(fr);
	SAFE_FREE(data);
	
	return 0;
}

/**
 *	释放资源
 */
void DOD_ResManager::FreeResource(void *pData)
{
	SAFE_FREE(pData);
}
}
