/**
 *	@file		DOD_G3dobj.cpp
 *
 *	@desc		DOD_Gx中处理3D对象的类的实现文件
 *
 *	@author		Syalon
 *
 *	@history	2009/04/11	初版
 */
 
#include "DOD_G3dobj.h"
#include "DOD_Gx.h"
#include "DOD_ObjManager.h"

namespace Dod
{
/**
 *	更新G3D对象
 */
void DOD_G3dobj::Update()
{
}

/**
 *	渲染G3D对象
 */
void DOD_G3dobj::Render()
{
}

void DOD_G3dobj::add_to_objmgr()
{
	Dod_GxGetObjMgr()->AddG3dobj(this);
}

void DOD_G3dobj::remove_from_objmgr()
{
	Dod_GxGetObjMgr()->RemoveG3dobj(this);
}
}
