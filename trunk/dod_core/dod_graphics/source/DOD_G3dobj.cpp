/**
 *	@file		DOD_G3dobj.cpp
 *
 *	@desc		DOD_Gx�д���3D��������ʵ���ļ�
 *
 *	@author		Syalon
 *
 *	@history	2009/04/11	����
 */
 
#include "DOD_G3dobj.h"
#include "DOD_Gx.h"
#include "DOD_ObjManager.h"

namespace Dod
{
/**
 *	����G3D����
 */
void DOD_G3dobj::Update()
{
}

/**
 *	��ȾG3D����
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
