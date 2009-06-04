/**
 *	@file		DOD_G2dobj.h
 *
 *	@desc		DOD_Gx中处理2D对象的类的定义文件
 *
 *	@author		Syalon
 *
 *	@history	2009/04/11	初版
 */
 
#ifndef __DOD_G2D_OBJ_H__
#define __DOD_G2D_OBJ_H__

#include "DOD_G3dobj.h"

namespace Dod
{
class DOD_G2dobj : public DOD_G3dobj
{
public:
	DOD_G2dobj();
	virtual ~DOD_G2dobj();

protected:
	virtual void	add_to_objmgr();
	virtual void 	remove_from_objmgr();
	
public:
	f32				GetX() const { return m_x; }
	f32				GetY() const { return m_y; }
	f32				GetZ() const { return m_z; }
	f32				GetOX() const { return m_ox; }
	f32				GetOY() const { return m_oy; }
	
	virtual f32		SetX(f32 fx);
	virtual f32		SetY(f32 fy);
	virtual f32		SetZ(f32 fz);
	virtual f32		SetOX(f32 fox);
	virtual f32		SetOY(f32 foy);
	
protected:
	f32				m_x, m_y, m_z;
	f32				m_ox, m_oy;
	
protected:
	/*
	 *	0	2
	 *	1	3
	 */
	struct dod_vertex_tcp	m_vtxs[4];
};
}

#endif
