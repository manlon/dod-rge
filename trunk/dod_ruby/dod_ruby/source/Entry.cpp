/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * main.c - Basic sample to demonstrate some fileio functionality.
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 * Copyright (c) 2005 Jim Paris <jim@jtan.com>
 *
 * $Id: main.c 1175 2005-10-20 15:41:33Z chip $
 */
#include <pspkernel.h>
#include <pspctrl.h>
#include <pspdebug.h>
#include <pspdisplay.h>
#include <psptypes.h>
#include <pspiofilemgr.h>

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/unistd.h>

#include "Rge.h"
#include "ResManager.h"
#include "RgeManager.h"

PSP_MODULE_INFO("Ruby Game Engine For PSP", 0, 1, 0);

PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER);

namespace
{
	const char* gDefaultScriptName = "Scripts.rb";
}

volatile int g_done = 0;

int exit_callback(int arg1, int arg2, void* commons)
{ 
	g_done = 1;
	return 0;
}

int CallbackThread(SceSize args, void *argp)
{
    int cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
    
    sceKernelRegisterExitCallback(cbid);
    sceKernelSleepThreadCB();
    
    return 0;
}

int SetupCallbacks(void)
{
    int thid = sceKernelCreateThread("update_thread", CallbackThread, 0x11, 0xFA0, THREAD_ATTR_USER, 0);
    
    if(thid >= 0)
    {
		sceKernelStartThread(thid, 0, 0);
    }
    return thid;
}

/*
void exceptionHandler(PspDebugRegBlock *regs)
{
    pspDebugScreenInit();
    pspDebugScreenSetBackColor(0x00FF0000);
    pspDebugScreenSetTextColor(0xFFFFFFFF);
    pspDebugScreenClear();
    pspDebugScreenPrintf("Exception Details:\n");
    pspDebugDumpException(regs);
}
__attribute__((constructor)) void stdoutInit() {
    pspKernelSetKernelPC();
    pspDebugInstallStdoutHandler(pspDebugScreenPrintData);
    pspDebugInstallStderrHandler(pspDebugScreenPrintData);
    pspDebugInstallErrorHandler(exceptionHandler);
} 
*/

struct __startup_args
{
	const char *pointer;
	int  size;
};

static VALUE rge_main_in_protect(VALUE args)
{	
	//	获取参数
	struct __startup_args *sargs = (struct __startup_args*)(NUM2UINT(args));
	
	ResManager::Instance()->Init(sargs->pointer);
	
	RgeManager *pRge = GetRGE();
	
	if (!pRge->Start())
		return Qnil;
	
	//	Ruby内部一些IO相关默认方法初始化
	pRge->ReplaceRubyMethod();

	//	初始化RGE内部库
	pRge->InitRGEInternClass();
	
	//	初始化RGE扩展的Ruby内部库
 	pRge->InitRubyInternClassExt();
	
	// ------------------华丽的分割线-------------------------
	const ID    id_eval = rb_intern("eval");
	const VALUE binding = rb_const_get(rb_mKernel, rb_intern("TOPLEVEL_BINDING"));
	const VALUE lineno  = INT2FIX(1);

	VALUE name, code;
	
	name = rb_str_new2("Main");
	{
		u32	size=0;
		char *data = (char*)GetResManager()->Resource_Load(gDefaultScriptName, &size);
		code = rb_str_new2(data);
		GetResManager()->Resource_Free(data);
		
		RgeDbgPrintf("debug: Scripts Length = %ld\n", size);
	}
	rb_funcall(rb_mKernel, id_eval, 4, code, binding, name, lineno);
	
	return Qnil;
}

void __on_failed()
{
	const VALUE message			= rb_funcall(ruby_errinfo, rb_intern("message"), 0);
	const VALUE message_str		= rb_funcall(message, rb_intern("gsub"), 2, rb_str_new2("\n"), rb_str_new2("\r\n"));
	//const VALUE backtrace		= rb_funcall(ruby_errinfo, rb_intern("backtrace"), 0);
	//const VALUE backtrace_str	= rb_str_concat(rb_ary_join(backtrace, rb_str_new2("\r\n")), rb_str_new2("\r\n"));

	const char *clsname			= rb_obj_classname(ruby_errinfo);
	const char *msg				= STR2CSTR(message_str);
	//const char *bktr			= STR2CSTR(backtrace_str);

	char errinfo[256];
	if (rb_obj_is_kind_of(ruby_errinfo, rb_eSyntaxError))
		sprintf(errinfo, "Scripts '%s' %d line Error %s. ", ruby_sourcefile, ruby_sourceline, clsname);
	else
		sprintf(errinfo, "Scripts '%s' %d line Error %s. \n\n%s", ruby_sourcefile, ruby_sourceline, clsname, msg);
	
	RgeDbgPrintf("----- ruby exception message ----- \n");
	RgeDbgPrintf("%s\n", errinfo);
	RgeDbgPrintf("---------------------------------- \n");
}

int main(int argc, char** argv)
{
//	pspKernelSetUserPC();
// 	pspDebugInstallStdoutHandler(pspDebugScreenPrintData);
// 	pspDebugInstallStderrHandler(pspDebugScreenPrintData);
//	pspDebugInstallErrorHandler(eeee);

	pspDebugScreenInit();
	
	RgeDbgPrintf(" psp program start !\n");

	SetupCallbacks();

	//	嵌入Ruby解释器
	{
		//RUBY_INIT_STACK

		ruby_init();
		//ruby_set_argv(argc - 1, argv + 1);
		//rb_set_kcode("utf8");				//	设置编码为UTF8
 		ruby_init_loadpath();
		ruby_script("psprge");
	}

	//	设置参数
	struct __startup_args sargs;

	sargs.pointer = argv[0];
	sargs.size = 0;

	//	保护模式运行
	
	RgeDbgPrintf(" \nrun ruby interpreter under protected mode !\n");
	
	int state = 0, result_code = 0;

	rb_protect(rge_main_in_protect, UINT2NUM((unsigned long)&sargs), &state);

	//	运行结束后的处理
	if (state)
	{
		if (rb_obj_is_kind_of(ruby_errinfo, rb_eSystemExit))
			result_code = FIX2INT(rb_iv_get(ruby_errinfo, "status"));
		else 
		{
			__on_failed();
			result_code = 1;
		}
	}

	//	删除用户添加的字体
//	GetRGE()->RemoveUserFont();
	
	//	结束处理
	ruby_finalize();

	//	release Hge
	//if (GetHGE()) GetHGE()->Release();

	//	delete RgeManager
	RgeManager::Release();

	//	delete ResManager
	ResManager::Release();

	RgeDbgPrintf(" \nruby interpreter finish...\n\n press 'home' key to exit !");

	while (!g_done);
	
	sceKernelExitGame();
	
	return result_code;
}
