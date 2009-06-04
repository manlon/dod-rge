#include "DOD_ObjManager.h"
#include "DOD_Gx.h"

namespace Dod
{
DOD_ObjManager::DOD_ObjManager()
{
	m_pG3dList = new DODG3DLIST();
	m_pG2dList = new DODG2DLIST();
}

DOD_ObjManager::~DOD_ObjManager()
{
	SAFE_DELETE(m_pG3dList);
	SAFE_DELETE(m_pG2dList);
}
	
/**
 *	���G3D����
 */
void DOD_ObjManager::AddG3dobj(DOD_G3dobj *pObj) const
{
 	m_pG3dList->push_back(pObj);
}

/**
 *	�Ƴ�G3D����
 */
void DOD_ObjManager::RemoveG3dobj(DOD_G3dobj *pObj) const
{
	
}

/**
 *	���G2D����
 */
void DOD_ObjManager::AddG2dobj(DOD_G2dobj *pObj) const
{
 	m_pG2dList->push_back(pObj);
}

/**
 *	�Ƴ�G2D����
 */
void DOD_ObjManager::RemoveG2dobj(DOD_G2dobj *pObj) const
{
	
}
}
