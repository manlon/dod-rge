/**
 *	@file		dod_macros.h
 *
 *	@desc		DOD中常用宏定义
 *
 *	@author		Syalon
 *
 *	@history	2009/04/11	初版
 */
 
#ifndef __dod_macros_h__
#define __dod_macros_h__

#include <stdio.h>
#include <stdlib.h>

#ifdef _DEBUG
	#include "system/DodLog.h"
#endif

namespace Dod
{
#define	SAFE_DELETE(ptr)		{if (ptr) { delete ptr; ptr = NULL; }}
#define SAFE_DELETE_ARRAY(ptr)	{if (ptr) { delete [] ptr; ptr = NULL; }}
#define SAFE_FREE(ptr)			{if (ptr) { free(ptr); ptr = NULL; }}
#define	SAFE_CLOSE(handle)		{if (handle) {fclose(handle); handle = 0; }}
#define SAFE_DESTROY(ptr)		{if (ptr) { ptr->Destroy(); ptr = NULL; }}

#ifdef _DEBUG
	#define DOD_LOG(...)	DodLog::Printf(__VA_ARGS__)
#else
	#define DOD_LOG(...)	((void)0)
#endif
}

#endif
