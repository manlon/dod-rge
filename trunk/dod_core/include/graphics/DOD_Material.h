/**
 *	@file		DOD_Material.h
 *
 *	@desc		DOD_Gx�в����ඨ���ļ�
 *
 *	@author		Syalon
 *
 *	@history	2009/04/11	����
 */
 
#ifndef __DOD_MATERIAL_H__
#define __DOD_MATERIAL_H__

#include "DOD_Color.h"

namespace Dod
{
class DOD_Material
{
public:
	DOD_Color	ambient;
	DOD_Color	diffuse;
	DOD_Color	specular;
	DOD_Color	emissive;
	
	f32			power;
};
}

#endif
