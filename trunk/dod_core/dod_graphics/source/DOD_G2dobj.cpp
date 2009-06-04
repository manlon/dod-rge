/**
 *	@file		DOD_G2dobj.cpp
 *
 *	@desc		DOD_Gx中处理2D对象的类的实现文件
 *
 *	@author		Syalon
 *
 *	@history	2009/04/11	初版
 */
 
#include "DOD_G2dobj.h"
#include "DOD_Gx.h"
#include "DOD_ObjManager.h"

namespace Dod
{
DOD_G2dobj::DOD_G2dobj()
: m_x(0), m_y(0), m_z(0), m_ox(0), m_oy(0)
{
	m_vtxs[0].u = 0.0f; m_vtxs[0].v = 0.0f;
	m_vtxs[1].u = 0.0f; m_vtxs[1].v = 1.0f;
	m_vtxs[2].u = 1.0f; m_vtxs[2].v = 0.0f;
	m_vtxs[3].u = 1.0f; m_vtxs[3].v = 1.0f;
	
	m_vtxs[0].z =
	m_vtxs[1].z =
	m_vtxs[2].z =
	m_vtxs[3].z = 0.5f;
	
	m_vtxs[0].color =
	m_vtxs[1].color =
	m_vtxs[2].color =
	m_vtxs[3].color = 0x0;
	
	add_to_objmgr();
}

DOD_G2dobj::~DOD_G2dobj()
{
	remove_from_objmgr();
}

void DOD_G2dobj::add_to_objmgr()
{
	Dod_GxGetObjMgr()->AddG2dobj(this);
}

void DOD_G2dobj::remove_from_objmgr()
{
	Dod_GxGetObjMgr()->RemoveG2dobj(this);
}

f32 DOD_G2dobj::SetX(f32 fx)
{
	m_x = fx;
	return fx;
}

f32 DOD_G2dobj::SetY(f32 fy)
{
	m_y = fy;
	return fy;
}

f32 DOD_G2dobj::SetZ(f32 fz)
{
	m_z = fz;
	return fz;
}

f32 DOD_G2dobj::SetOX(f32 fox)
{
	m_ox = fox;
	return fox;
}

f32 DOD_G2dobj::SetOY(f32 foy)
{
	m_oy = foy;
	return foy;
}
}
