/**
 *	@file		DOD_Gxobj.h
 *
 *	@desc		DOD_Gx中全部对象的顶层抽象基类定义文件
 *
 *	@author		Syalon
 *
 *	@history	2009/04/11	初版
 */
 
#ifndef __DOD_GX_OBJ_H__
#define __DOD_GX_OBJ_H__

#include "DOD_Gxtypes.h"

namespace Dod
{
class DOD_Gxobj
{
public:
	DOD_Gxobj(){}
	virtual ~DOD_Gxobj(){}

public:
	virtual void	Update() = 0;
	virtual void	Render() = 0;
	
protected:
	virtual void	add_to_objmgr() = 0;
	virtual void 	remove_from_objmgr() = 0;
};
}

#endif
