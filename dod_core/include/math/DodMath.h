#ifndef __DOD_MATH_H__
#define __DOD_MATH_H__

#include "dod_types.h"

namespace Dod
{
namespace DodMath
{
	f32 SinR(f32 rad);
	f32 SinD(f32 deg);
	f32 CosR(f32 rad);
	f32 CosD(f32 deg);
	f32 TanR(f32 rad);
	f32 TanD(f32 deg);

	f32 ArcSinR(f32 fv);
	f32 ArcSinD(f32 fv);
	f32 ArcCosR(f32 fv);
	f32 ArcCosD(f32 fv);
	f32 ArcTanR(f32 fv);
	f32 ArcTanD(f32 fv);

	f32 Sqrt(f32 fv);
	f32 RSqrt(f32 fv);
}
}

#endif
