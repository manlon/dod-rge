#ifndef __DOD_VEC4_H__
#define __DOD_VEC4_H__

#include "dod_types.h"

namespace Dod
{
/*
 *	class name:	DOD_Vec4
 *	function:	use for 4 dimension homogeneous vector operation
 *	author:		Hejiabin
 *	Data:		2009.3.15
 */

class DOD_Vec4
{
public:
	DOD_Vec4();
	DOD_Vec4( DOD_Vec4& value );
	DOD_Vec4( s32 x, s32 y, s32 z );
	~DOD_Vec4();

	DOD_Vec4 operator+( DOD_Vec4 &value );		//add
	DOD_Vec4 operator-( DOD_Vec4 &value );		//sub
	s32 operator*( DOD_Vec4 &value );		//dot product
	DOD_Vec4 operator*( s32 value );		//scalar product
	DOD_Vec4 operator/( s32 value );		//scalar div
	DOD_Vec4 Cross( DOD_Vec4 &value );		//cross product

	s32 Len();					//get vector length
       	void Normal();					//normalize the vector
	void Wto1();					//set w to 1 and adjust x y z	

	s32& X(){ return m_x; }				//access the member
	s32& Y(){ return m_y; }
	s32& Z(){ return m_z; }
	void x( s32 value ){ m_x= value; }
	void y( s32 value ){ m_y= value; }
	void z( s32 value ){ m_z= value; }
	
protected:
	union
	{
		struct
		{
			s32 m_x;
			s32 m_y;
			s32 m_z;
			s32 m_w;
		};
		s32 m_num[4];
	};
};
}

#endif

