#ifndef __DOD_MAT22_H__
#define __DOD_MAT22_H__

#include "dod_types.h"

namespace Dod
{
/*
 *	class name:	DOD_Mat22
 *	function:	use for 2x2 matrix
 *	author:		Hejiabin
 *	Data:		2009.3.24
 */

class DOD_Mat22
{
public:
	DOD_Mat22();
	~DOD_Mat22();
	DOD_Mat22( DOD_Mat22& value );

	DOD_Mat22 operator*( DOD_Mat22& value );
	void Identity();

protected:
	union
	{
		struct
		{
			s32 _00;
			s32 _01;
			s32 _10;
			s32 _11;
		};
		s32 m_mat2[2][2];
		s32 m_mat1[4];
	};
	
};
}


#endif

