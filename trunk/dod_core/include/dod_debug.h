#ifndef __dod_debug_h__
#define __dod_debug_h__

#include <pspdebug.h>

namespace Dod
{
#ifdef _DEBUG
	#define	Dod_DbgPrintf(...)	pspDebugScreenPrintf(__VA_ARGS__)
#else
	#define Dod_DbgPrintf(...)	((void)0)
#endif

}

#endif
