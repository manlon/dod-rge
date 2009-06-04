/**
 *	@file		DOD_G3dobj.h
 *
 *	@desc		DOD_Gx�д���3D�������Ķ����ļ�
 *
 *	@author		Syalon
 *
 *	@history	2009/04/11	����
 */
 
#ifndef __DOD_G3D_OBJ_H__
#define __DOD_G3D_OBJ_H__

#include "DOD_Gxobj.h"

namespace Dod
{
class DOD_G3dobj : public DOD_Gxobj
{
public:
	DOD_G3dobj(){}
	virtual ~DOD_G3dobj(){}

public:
	virtual void	Update();
	virtual void	Render();
	
protected:
	virtual void	add_to_objmgr();
	virtual void 	remove_from_objmgr();
};
}

#endif
