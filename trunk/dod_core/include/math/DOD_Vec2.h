#ifndef __DOD_VEC2_H__
#define __DOD_VEC2_H__

#include "dod_types.h"

namespace Dod
{
/*
 *	class name:	DOD_Vec2
 *	function:	use for 2 dimension vector operation
 *	author:		Hejiabin
 *	Data:		2009.3.14
 */

class DOD_Vec2
{
public:
	DOD_Vec2();
	DOD_Vec2( DOD_Vec2& value );
	DOD_Vec2( s32 x, s32 y );
	~DOD_Vec2();

	DOD_Vec2 operator+( DOD_Vec2 &value );	//add
	DOD_Vec2 operator-( DOD_Vec2 &value );	//sub
	s32 operator*( DOD_Vec2 &value );	//dot product
	DOD_Vec2 operator*( s32 value );	//scalar product
	DOD_Vec2 operator/( s32 value );	//scalar div

	s32 Len();				//get vector length
	void Normal();				//become unit vector

	s32& X(){ return m_x; }			//access the memberi
	s32& Y(){ return m_y; }
	void x( s32 value ){ m_x= value; }
	void y( s32 value ){ m_y= value; }

protected:
	s32 m_x;
	s32 m_y;
};
}

#endif
