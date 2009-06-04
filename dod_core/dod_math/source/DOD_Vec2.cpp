#include "DOD_Vec2.h"
//#include<math.h>
#include "DodMath.h"

namespace Dod
{

DOD_Vec2::DOD_Vec2()
{
	m_x= m_x^m_x;
	m_y= m_y^m_y;
}

DOD_Vec2::DOD_Vec2( DOD_Vec2& value )
{
	m_x= value.m_x;
	m_y= value.m_y;
}

DOD_Vec2::DOD_Vec2( s32 x, s32 y )
{
	m_x= x;
	m_y= y;
}

DOD_Vec2::~DOD_Vec2()
{
}

DOD_Vec2 DOD_Vec2::operator+( DOD_Vec2 &value )
{
	DOD_Vec2 result;
	result.m_x= m_x + value.m_x;
	result.m_y= m_y + value.m_y;

	return result;
}

DOD_Vec2 DOD_Vec2::operator-( DOD_Vec2 &value )
{
	DOD_Vec2 result;
	result.m_x= m_x - value.m_y;
	result.m_y= m_y - value.m_y;

	return result;
}

s32 DOD_Vec2::operator*( DOD_Vec2 &value )
{
	s32 result;
	result= m_x*value.m_x + m_y*value.m_y;
	
	return result;
}

DOD_Vec2 DOD_Vec2::operator*( s32 value )
{
	DOD_Vec2 result;
	result.m_x= m_x * value;
	result.m_y= m_y * value;

	return result;
}

DOD_Vec2 DOD_Vec2::operator/( s32 value )
{
	DOD_Vec2 result;
	result.m_x= m_x / value;
	result.m_y= m_y / value;

	return result;
}

s32 DOD_Vec2::Len()
{
	s32 result;
	result= m_x*m_x + m_y*m_y;
	//result= sqrt( double(result) );
	result = DodMath::Sqrt(result);

	return result;
}

void DOD_Vec2::Normal()
{
	m_x= m_x / Len();
	m_y= m_y / Len();
}

}
