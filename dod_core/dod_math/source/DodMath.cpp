#include "DodMath.h"

namespace Dod
{

#define __dod_asm__ __asm__ __volatile__

/**
 *	f32 DodMath::SinR(f32 rad)
 *
 *		计算rad的正弦值。
 *
 *	__asm : vsin(2 / PI * radians)
 */
f32 DodMath::SinR(f32 rad)
{
	f32 ret;

	__dod_asm__("lv.s S000, %0" : :"m"(rad));	//	S000 = rad
	__dod_asm__("vcst.s S001, 5");				//	S001 = 2 / PI
	__dod_asm__("vmul.s S000, S001, S000");		//	S000 *= S001
	__dod_asm__("vsin.s S000, S000");			//	S000 = sinf(S000)
	__dod_asm__("sv.s S000, %0" : "=m"(ret));	//	ret = S000

	return ret;
}

/**
 *	f32 DodMath::SinD(f32 deg)
 *
 *		计算deg的正弦值。
 *
 *	__asm :	vsin(degrees / 90)
 */
f32 DodMath::SinD(f32 deg)
{
	f32 ret;

	f32 fdiv = 90.0f;

	__dod_asm__("lv.s S000, %0" : :"m"(deg));	//	S000 = deg
	__dod_asm__("lv.s S001, %0" : :"m"(fdiv));	//	S001 = fdiv
	__dod_asm__("vdiv.s S000, S000, S001");		//	S000 /= S001
	__dod_asm__("vsin.s S000, S000");			//	S000 = sinf(S000)
	__dod_asm__("sv.s S000, %0" : "=m"(ret));	//	ret = S000

	return ret;
}

/**
 *	f32 DodMath::CosR(f32 rad)
 *
 *		计算rad的余弦值。
 *
 *	__asm : vcos(2 / PI * radians)
 */
f32 DodMath::CosR(f32 rad)
{
	f32 ret;

	__dod_asm__("lv.s S000, %0" : :"m"(rad));	//	S000 = rad
	__dod_asm__("vcst.s S001, 5");				//	S001 = 2 / PI
	__dod_asm__("vmul.s S000, S001, S000");		//	S000 *= S001
	__dod_asm__("vcos.s S000, S000");			//	S000 = cosf(S000)
	__dod_asm__("sv.s S000, %0" : "=m"(ret));	//	ret = S000

	return ret;
}

/**
 *	f32 DodMath::CosD(f32 deg)
 *
 *		计算deg的余弦值。
 *
 *	__asm :	vcos(degrees / 90)
 */
f32 DodMath::CosD(f32 deg)
{
	f32 ret;

	f32 fdiv = 90.0f;

	__dod_asm__("lv.s S000, %0" : :"m"(deg));	//	S000 = deg
	__dod_asm__("lv.s S001, %0" : :"m"(fdiv));	//	S001 = fdiv
	__dod_asm__("vdiv.s S000, S000, S001");		//	S000 /= S001
	__dod_asm__("vcos.s S000, S000");			//	S000 = cosf(S000)
	__dod_asm__("sv.s S000, %0" : "=m"(ret));	//	ret = S000

	return ret;
}

/**
 *	f32 DodMath::TanR(f32 rad)
 *
 *		计算rad的正切值。
 */
f32 DodMath::TanR(f32 rad)
{
	return DodMath::SinR(rad) / DodMath::CosR(rad);
}

/**
 *	f32 DodMath::TanD(f32 deg)
 *
 *		计算deg的正切值。
 */
f32 DodMath::TanD(f32 deg)
{
	return DodMath::SinD(deg) / DodMath::CosD(deg);
}

/**
 *	f32 DodMath::ArcSinR(f32 fv)
 *
 *		计算fv的反正弦值(弧度)。
 *
 *	__asm : vasin(fv) * (PI / 2)
 */
f32 DodMath::ArcSinR(f32 fv)
{
	f32 ret;

	__dod_asm__("lv.s S000, %0" : :"m"(fv));	//	S000 = fv
	__dod_asm__("vasin.s S000, S000");			//	S000 = asinf(S000)
	__dod_asm__("vcst.s S001, 8");				//	S001 = PI / 2
	__dod_asm__("vmul.s S000, S000, S001");		//	S000 *= S001
	__dod_asm__("sv.s S000, %0" : "=m"(ret));	//	ret = S000

	return ret;
}

/**
 *	f32 DodMath::ArcSinD(f32 fv)
 *
 *		计算fv的反正弦值(角度)。
 *
 *	__asm : vasin(fv) * 90
 */
f32 DodMath::ArcSinD(f32 fv)
{
	f32 ret;

	f32 fmul = 90.0f;

	__dod_asm__("lv.s S000, %0" : :"m"(fv));	//	S000 = fv
	__dod_asm__("vasin.s S000, S000");			//	S000 = asinf(S000)

	__dod_asm__("lv.s S001, %0" : :"m"(fmul));	//	S001 = fmul
	__dod_asm__("vmul.s S000, S001, S000");		//	S000 *= S001

	__dod_asm__("sv.s S000, %0" : "=m"(ret));	//	ret = S000

	return ret;
}

/**
 *	f32 DodMath::ArcCosR(f32 fv)
 *
 *		计算fv的反余弦值(弧度)。
 *
 *	__asm : PI / 2 - vasin(fv) * (PI / 2)
 */
f32 DodMath::ArcCosR(f32 fv)
{
	f32 ret;

	__dod_asm__("lv.s S000, %0" : :"m"(fv));	//	S000 = fv
	__dod_asm__("vasin.s S000, S000");			//	S000 = asinf(S000)
	__dod_asm__("vcst.s S001, 8");				//	S001 = PI / 2
	__dod_asm__("vmul.s S000, S000, S001");		//	S000 *= S001
	__dod_asm__("vsub.s S000, S001, S000");		//	S000 = S001 - S000
	__dod_asm__("sv.s S000, %0" : "=m"(ret));	//	ret = S000

	return ret;
}

/**
 *	f32 DodMath::ArcCosD(f32 fv)
 *
 *		计算fv的反余弦值(角度)。
 */
f32 DodMath::ArcCosD(f32 fv)
{
	return 90.0f - DodMath::ArcSinD(fv);
}

/**
 *	f32 DodMath::ArcTanR(f32 fv)
 *
 *		计算fv的反正切值(弧度)。
 */
f32 DodMath::ArcTanR(f32 fv)
{
	return DodMath::ArcSinR(2.0f * fv / (1.0f + fv * fv)) / 2.0f;
}

/**
 *	f32 DodMath::ArcTanD(f32 fv)
 *
 *		计算fv的反正切值(角度)。
 */
f32 DodMath::ArcTanD(f32 fv)
{
	return DodMath::ArcSinD(2.0f * fv / (1.0f + fv * fv)) / 2.0f;
}

/**
 *	f32 DodMath::Sqrt(f32 fv)
 *
 *		计算fv的平方根。
 */
f32 DodMath::Sqrt(f32 fv)
{
	f32 ret;

	__dod_asm__("lv.s S000, %0" : :"m"(fv));	//	S000 = fv
	__dod_asm__("vsqrt.s S000, S000");			//	S000 = sqrt(S000)
	__dod_asm__("sv.s S000, %0" : "=m"(ret));	//	ret = S000

	return ret;
}

/**
 *	f32 DodMath::RSqrt(f32 fv)
 *
 *		计算fv的平方根的倒数。
 */
f32 DodMath::RSqrt(f32 fv)
{
	f32 ret;

	__dod_asm__("lv.s S000, %0" : :"m"(fv));	//	S000 = fv
	__dod_asm__("vrsq.s S000, S000");			//	S000 = 1.0f / sqrt(S000)
	__dod_asm__("sv.s S000, %0" : "=m"(ret));	//	ret = S000

	return ret;
}

}
