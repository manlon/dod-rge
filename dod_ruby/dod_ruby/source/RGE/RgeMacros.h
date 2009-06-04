#ifndef __RGE_MACROS_H__
#define __RGE_MACROS_H__

#include <pspdebug.h>
#define	RgeDbgPrintf	pspDebugScreenPrintf

#include <dod_macros.h>
//#include "auxKconv.h"

//#include "RgeFile.h"

//#define __UTF8(str)				auxKconv(L##str).UnicodeToUTF8()
//#define	__UTF8ToUnicode(str)	auxKconv((char*)str).UTF8ToUnicode()

//#define SAFE_DELETE(ptr)		{if (ptr) { delete ptr; ptr = 0; }}
//#define SAFE_DELETE_ARRAY(ptr)	{if (ptr) { delete [] ptr; ptr = 0; }}
//#define SAFE_FREE(ptr)			{if (ptr) { free(ptr); ptr = 0; }}
//#define	SAFE_CLOSE(handle)		{if (handle) {fclose(handle); handle = 0; }}
//#define SAFE_CLOSE(handle)		{if (handle) {Rgefclose(handle); handle = 0; }}

#endif
