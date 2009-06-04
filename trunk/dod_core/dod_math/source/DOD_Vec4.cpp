#include "DOD_Vec4.h"
//#include<math.h>
#include "DodMath.h"

namespace Dod
{

DOD_Vec4::DOD_Vec4()
{
	m_x= m_x^m_x;
	m_y= m_y^m_y;
	m_z= m_z^m_z;
	m_w= 1;
}

DOD_Vec4::DOD_Vec4( DOD_Vec4& value )
{
	m_x= value.m_x;
	m_y= value.m_y;
	m_z= value.m_z;
	m_w= 1;
}

DOD_Vec4::DOD_Vec4( s32 x, s32 y, s32 z )
{
	m_x= x;
	m_y= y;
	m_z= z;
	m_w= 1;
}

DOD_Vec4::~DOD_Vec4()
{
}


DOD_Vec4 DOD_Vec4::operator+( DOD_Vec4 &value )
{
	DOD_Vec4 result;
	result.m_x= m_x + value.m_x;
	result.m_y= m_y + value.m_y;
	result.m_z= m_z + value.m_z;

	return result;
}

DOD_Vec4 DOD_Vec4::operator-( DOD_Vec4 &value )
{
	DOD_Vec4 result;
	result.m_x= m_x - value.m_y;
	result.m_y= m_y - value.m_y;
	result.m_z= m_y - value.m_z;

	return result;
}

s32 DOD_Vec4::operator*( DOD_Vec4 &value )
{
	s32 result;
	result= m_x*value.m_x + m_y*value.m_y + m_z*value.m_z;
	
	return result;
}

DOD_Vec4 DOD_Vec4::operator*( s32 value )
{
	DOD_Vec4 result;
	result.m_x= m_x * value;
	result.m_y= m_y * value;
	result.m_z= m_z * value;

	return result;
}

DOD_Vec4 DOD_Vec4::operator/( s32 value )
{
	DOD_Vec4 result;
	result.m_x= m_x / value;
	result.m_y= m_y / value;
	result.m_z= m_z / value;

	return result;
}

s32 DOD_Vec4::Len()
{
	s32 result;
	result= m_x*m_x + m_y*m_y + m_z*m_z;
	//result= sqrt( result );
	result = DodMath::Sqrt(result);

	return result;
}

DOD_Vec4 DOD_Vec4::Cross( DOD_Vec4 &value )
{
	DOD_Vec4 result;
	result.m_x= m_y*value.m_z - m_z*value.m_y;
	result.m_y= m_z*value.m_x - m_x*value.m_z;
	result.m_z= m_x*value.m_y - m_y*value.m_x;

	return result;
}

void  DOD_Vec4::Normal()
{
	m_x= m_x / Len();
	m_y= m_y / Len();
	m_z= m_z / Len();
}

void DOD_Vec4::Wto1()
{
	m_x= m_x / m_w;
	m_y= m_y / m_w;
	m_z= m_z / m_w;
	m_w= 1;
}

}

