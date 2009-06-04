/**
*	@file		common.cpp
*
*	@desc		DOD sample 通用文件
*
*	@author		Syalon
*
*	@history	2009/04/11	出版
*/

#include <pspkernel.h>
#include <pspdebug.h>
#include <pspctrl.h>
#include <stdlib.h>
#include <string.h>

/* Define the module info section */
#ifdef DOD_SAMPLE_TITLE
PSP_MODULE_INFO(DOD_SAMPLE_TITLE, 0, 1, 1);
#else
PSP_MODULE_INFO("dod common sample title", 0, 1, 1);
#endif

/* Define the main thread's attribute value (optional) */
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);

/* Define printf, just to make typing easier */
#define printf	pspDebugScreenPrintf

volatile int g_done = 0;

/* Exit callback */
int exit_callback(int arg1, int arg2, void *common)
{
	g_done = 1;
	return 0;
}

/* Callback thread */
int CallbackThread(SceSize args, void *argp)
{
	int cbid;

	cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
	sceKernelRegisterExitCallback(cbid);
	sceKernelSleepThreadCB();

	return 0;
}

/* Sets up the callback thread and returns its thread id */
int SetupCallbacks(void)
{
	int thid = 0;

	thid = sceKernelCreateThread("update_thread", CallbackThread,
		0x11, 0xFA0, 0, 0);
	if(thid >= 0)
	{
		sceKernelStartThread(thid, 0, 0);
	}

	return thid;
}
