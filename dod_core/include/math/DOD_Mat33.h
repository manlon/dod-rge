#ifndef __DOD_MAT33_H__
#define __DOD_MAT33_H__

#include "dod_types.h"

namespace Dod
{
/*
 *	class name:	DOD_Mat33
 *	function:	use for 3x3 matrix
 *	author:		Hejiabin
 *	Data:		2009.3.24
 */

class DOD_Mat33
{
public:
	DOD_Mat33();
	~DOD_Mat33();
	DOD_Mat33( DOD_Mat33& value );

	DOD_Mat33 operator*( DOD_Mat33& value );
	void Identity();

protected:
	union
	{
		struct
		{
			s32 _00;
			s32 _01;
			s32 _02;
			s32 _10;
			s32 _11;
			s32 _12;
			s32 _20;
			s32 _21;
			s32 _22;
		};
		s32 m_mat2[3][3];
		s32 m_mat1[9];
	};
	
};
}


#endif

