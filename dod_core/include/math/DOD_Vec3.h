#ifndef __DOD_VEC3_H__
#define __DOD_VEC3_H__

#include "dod_types.h"

namespace Dod
{
/*
 *	class name:	DOD_Vec3
 *	function:	use for 3 dimension vector operation
 *	author:		Hejiabin
 *	Data:		2009.3.14
 */

class DOD_Vec3
{
public:
	DOD_Vec3();
	DOD_Vec3( DOD_Vec3& value );
	DOD_Vec3( s32 x, s32 y, s32 z );
	~DOD_Vec3();

	DOD_Vec3 operator+( DOD_Vec3 &value );	//add
	DOD_Vec3 operator-( DOD_Vec3 &value );	//sub
	s32 operator*( DOD_Vec3 &value );	//dot product
	DOD_Vec3 operator*( s32 value );	//scalar product
	DOD_Vec3 operator/( s32 value );	//scalar div
	DOD_Vec3 Cross( DOD_Vec3 &value );	//cross product

	s32 Len();				//get vector length
       	void Normal();				//become unit vector	

	s32& X(){ return m_x; }			//access the memberi
	s32& Y(){ return m_y; }
	s32& Z(){ return m_z; }
	void x( s32 value ){ m_x= value; }
	void y( s32 value ){ m_y= value; }
	void z( s32 value ){ m_z= value; }
	
protected:
	s32 m_x;
	s32 m_y;
	s32 m_z;
};
}

#endif

