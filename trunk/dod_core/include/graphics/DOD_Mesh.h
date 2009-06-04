/**
 *	@file		DOD_Mesh.h
 *
 *	@desc		DOD_Mesh结构定义文件
 *
 *	@author		Syalon
 *
 *	@history	2009/05/23	初版
 */

#ifndef __DOD_MESH_H__
#define __DOD_MESH_H__

#include "DOD_FileFormat.h"

namespace Dod
{

struct DOD_Mesh
{
	dod_dmdl_header		header;
	dod_dmdl_material*	p_material_list;
	dod_dmdl_texture*	p_texture_list;

	DOD_Mesh() : p_material_list(0), p_texture_list(0)
	{}
	~DOD_Mesh(){}
};

}	//	namespace Dod

#endif	//	__DOD_MESH_H__
